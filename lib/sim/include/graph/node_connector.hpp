#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "common_log.hpp"

#include "node_base.hpp"
#include "fmu_handler.hpp"
#include "data_handler.hpp"
#include "data_type.hpp"
#include "data_type.hpp"
#include "model_utils.hpp"
#include "data_storage.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{

    // This class can be optimized allot
    class Connectors
    {
    public:
        map<string, ConnectorNode *> input_connectors;
        map<string, ConnectorNode *> output_connectors;

        utils::DataStorage<ConnectorNode> input_data;
        utils::DataStorage<ConnectorNode> output_data;

        Connectors() {}

        void allocate()
        {
            for (auto [_, con]: input_connectors)
            {
                input_data.add(*con);
            }
            for (auto [_, con]: output_connectors)
            {
                output_data.add(*con);
            }
            input_data.allocate();
            output_data.allocate();
        }

        void write_to_model(uint64_t time)
        {
            int index = 0;
            for (auto &[_, c] : input_connectors)
            {
                void *data = c->data_handler->getData(time, c->data_reference);

                utils::write_to_model_(c->type, *c->fmu->model, c->value_reference, data);
                // storage for export
                memcpy(input_data.locations[index], data, input_data.sizes[index]);
                index += 1;
            }
        }

        void read_from_model(uint64_t time)
        {
            int pos = 0;
            for (auto &[_, c] : output_connectors)
            {
                auto d = output_data.locations[pos];
                utils::read_from_model_(c->type, *c->fmu->model, c->value_reference, d);

                c->data_handler->setData(time, c->data_reference, d);
                pos += 1;
            }
        }

    };

    // template class to enable constexpression invoke
    class ConnectorNode : public NodeBase
    {
    public:
        common::Logger log = common::Logger("ConnectorNode", common::LogLevel::debug);

        string component_name;
        string connector_name;

        handler::FmuInfo *fmu;
        handler::DataHandler *data_handler;

        uint64_t data_reference;
        uint64_t value_reference;

        handler::DataType type;

        ConnectorNode()
        {
        }

        ConnectorNode(std::string component_name,
                      std::string connector_name,
                      handler::FmuInfo *fmu,
                      handler::DataHandler *data_handler,
                      handler::DataType type)
        {
            this->component_name = component_name;
            this->connector_name = connector_name;
            update_name();

            this->fmu = fmu;
            this->data_handler = data_handler;

            auto md = this->fmu->model_description;
            value_reference = md->get_variable_by_name(this->connector_name).value_reference;

            this->type = type;
        }

        virtual ~ConnectorNode()
        {
            log.ext_trace("[{}] Destroying ConnectorNode", __func__);
        }

        // only execute on outputs
        // the data_reference should be passed to the input
        uint64_t create_data_storage()
        {
            // add check if already called, potential memory leak
            data_reference = data_handler->initData(type, this->name);
            return data_reference;
        }

        void update_name()
        {
            this->name = ConnectorNode::create_name(component_name, connector_name);
        }

        static std::string create_name(string component_name, string connector_name)
        {
            return component_name + "." + connector_name;
        }

        friend ostream &operator<<(ostream &os, const ConnectorNode &obj)
        {
            os << "Connector { \n"
               << "name: " << obj.name << endl
               << " }" << endl;

            return os;
        }
    };

}