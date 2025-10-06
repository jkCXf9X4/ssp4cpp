#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "common_definitions.hpp"

#include "FMI2_Enums_Ext.hpp"

#include "data_ring_storage.hpp"
#include "data_recorder.hpp"
#include "invocable.hpp"
#include "config.hpp"

#include "fmu_handler.hpp"

#include <string>
#include <vector>
#include <functional>

namespace ssp4cpp::sim::graph
{

    class ConnectorInfo : public common::str::IString
    {
    public:
        common::Logger log = common::Logger("ConnectorInfo", common::LogLevel::info);
        static inline common::Logger s_log = common::Logger("ConnectorInfo_s", common::LogLevel::debug);

        utils::DataType type;
        size_t size;
        std::string name; // for debug

        uint32_t index;
        uint64_t value_ref;

        handler::FmuInfo *fmu;
        utils::RingStorage *storage;

        std::unique_ptr<std::byte[]> initial_value;

        bool forward_derivatives = false;
        int forward_derivatives_order = 0;

        virtual void print(std::ostream &os) const
        {
            os << "ConnectorInfo { "
               << "name: " << name
               << ", type: " << type
               << ", size: " << size
               << ", index: " << index
               << ", value_ref: " << value_ref
               << ", forward_derivatives: " << forward_derivatives_order
               << " }";
        }

        static void set_start_values(std::map<std::string, ConnectorInfo> &connectors)
        {
            for (auto &[name, connector] : connectors)
            {
                if (connector.initial_value)
                {
                    auto data_ptr = (void *)connector.initial_value.get();

                    auto data_type_str = fmi2::ext::enums::data_type_to_string(connector.type, data_ptr);
                    s_log.debug("[{}] Set initial value for {}, {} : {}",
                                __func__, name, connector.type.to_string(), data_type_str);

                    utils::write_to_model_(connector.type, *connector.fmu->model, connector.value_ref, data_ptr);
                }
            }
        }

        static void set_initial_input_area(ssp4cpp::sim::utils::RingStorage *input_area, std::map<std::string, ConnectorInfo> &inputs)
        {
            s_log.trace("[{}] Set input start area", __func__);
            auto area = input_area->push(0); //

            for (auto &[name, input] : inputs)
            {
                if (input.initial_value)
                {
                    auto data_ptr = (void *)input.initial_value.get();
                    auto item = input_area->get_item(area, input.index);

                    auto data_type_str = fmi2::ext::enums::data_type_to_string(input.type, data_ptr);
                    s_log.debug("[{}] Set initial input value for {}, {} : {}",
                                __func__, name, input.type.to_string(), data_type_str);

                    // set input area to reflect the data to ensure that next iteration correct data will be used
                    if (input.type == DataType::string)
                    {
                        // Move the internal string rep, not the std::string itself
                        *(std::string *)item = *(std::string *)data_ptr;
                    }
                    else
                    {
                        memcpy(item, data_ptr, input.size);
                    }
                }
            }
            input_area->flag_new_data(area);

            s_log.ext_trace("[{}] Input area after initialization: {}", __func__, input_area->data->export_area(area));
        }


        static inline void write_data_to_model(std::map<std::string, ConnectorInfo> &inputs, ssp4cpp::sim::utils::RingStorage *storage, int area)
        {
            IF_LOG({
                s_log.debug("[{}] Write data to model, time: {}", __func__, storage->data->timestamps[area]);
            });

            for (auto &[_, input] : inputs)
            {
                auto input_item = storage->get_item(area, input.index);

                IF_LOG({
                    auto data_type_str = fmi2::ext::enums::data_type_to_string(input.type, input_item);
                    s_log.debug("[{}] Copying input to model. {}, data: {}", __func__, input.to_string(), data_type_str);
                });

                utils::write_to_model_(input.type, *input.fmu->model, input.value_ref, (void *)input_item);
            }
        }

        static inline void read_values_from_model(std::map<std::string, ConnectorInfo> &outputs, ssp4cpp::sim::utils::RingStorage *storage, int area)
        {
            IF_LOG({
                s_log.debug("[{}] Init, area {}, time {}", __func__, area, storage->data->timestamps[area]);
            });

            for (auto &[_, output] : outputs)
            {
                auto item = storage->get_item(area, output.index);
                IF_LOG({
                    s_log.ext_trace("[{}] Copying ref {} ({}) to index {} ", __func__, output.value_ref, output.type.to_string(), output.index, (int64_t)item);
                });

                utils::read_from_model_(output.type, *output.fmu->model, output.value_ref, (void *)item);

                IF_LOG({
                    auto data_type_str = fmi2::ext::enums::data_type_to_string(output.type, item);
                    s_log.debug("[{}] Copying output from model. {}, data: {}", __func__, output.to_string(), data_type_str);
                });
            }
            IF_LOG({
                s_log.ext_trace("[{}] Completed copy from model", __func__);
            });
        }


        static inline void apply_input_derivatives(std::map<std::string, ConnectorInfo> &inputs, std::size_t area)
        {
            IF_LOG({
                s_log.trace("[{}] Init area {} ", __func__, area);
            });

            for (auto &[_, connector] : inputs)
            {
                if (!connector.forward_derivatives)
                {
                    continue;
                }

                for (int order = 1; order <= connector.forward_derivatives_order; ++order)
                {
                    auto der_ptr =  connector.storage->get_derivative(area, connector.index, order);
                    if (der_ptr == nullptr)
                    {
                        continue;
                    }

                    double value = *reinterpret_cast<double *>(der_ptr);
                    if (!connector.fmu->model->set_real_input_derivative(connector.value_ref, order, value))
                    {
                        s_log.warning("[{}] Failed to set input derivative order {} for {} (status {})",
                                    __func__,
                                    order,
                                    connector.name,
                                    static_cast<int>(connector.fmu->model->last_status()));
                    }
                }
            }
            
        }


        static inline void fetch_output_derivatives(std::map<std::string, ConnectorInfo> &outputs, std::size_t area)
        {
            IF_LOG({
                s_log.trace("[{}] Init area {} ", __func__, area);
            });

            for (auto &[_, connector] : outputs)
            {
                // dont run at time 0.0
                if (!connector.forward_derivatives)
                {
                    continue;
                }

                for (int order = 1; order <= connector.forward_derivatives_order; ++order)
                {
                    IF_LOG({
                        s_log.trace("[{}] get_derivative position for vr:{} name: {} order: {}", __func__, connector.value_ref, connector.name, order);
                    });

                    auto der_ptr = connector.storage->get_derivative(area, connector.index, order);
                    if (der_ptr == nullptr)
                    {
                        s_log.warning("[{}] Failed to find derivate item for {}", __func__, connector.name);
                        continue;
                    }
                    IF_LOG({
                        s_log.ext_trace("[{}] get_derivative for {} ", __func__, connector.name);
                    });

                    double value = 0.0;
                    if (!connector.fmu->model->get_real_output_derivative(connector.value_ref, order, value))
                    {
                        s_log.warning("[{}] Failed to get output derivative order {} for {} (status {})",
                                    __func__,
                                    order,
                                    connector.name,
                                    static_cast<int>(connector.fmu->model->last_status()));
                        continue;
                    }
                    IF_LOG({
                        s_log.trace("[{}] storing derivate for {} ", __func__, connector.name);
                    });

                    *reinterpret_cast<double *>(der_ptr) = value;
                }
            }
           
        }
    };
}
