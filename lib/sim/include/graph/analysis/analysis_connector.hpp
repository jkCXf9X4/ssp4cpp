#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "common_log.hpp"

#include "data_type.hpp"
// #include "analysis_model.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::sim::analysis::graph
{

    class AnalysisModel;

    // template class to enable constexpression invoke
    class AnalysisConnector : public ssp4cpp::common::graph::Node
    {
        uint64_t delay = 0;

    public:
        common::Logger log = common::Logger("AnalysisConnector", common::LogLevel::debug);

        string component_name;
        string connector_name;

        ssp4cpp::fmi2::md::Causality causality;

        uint64_t value_reference;

        utils::DataType type;
        std::size_t size;

        AnalysisModel *model;

        AnalysisConnector()
        {
        }

        AnalysisConnector(std::string component_name,
                          std::string connector_name,
                          uint64_t value_reference,
                          sim::utils::DataType type)
        {
            this->component_name = component_name;
            this->connector_name = connector_name;
            update_name();

            this->value_reference = value_reference;
            this->type = type;
            this->size = utils::get_data_type_size(type);
        }

        virtual ~AnalysisConnector()
        {
            log.ext_trace("[{}] Destroying AnalysisConnector", __func__);
        }

        void update_name()
        {
            this->name = AnalysisConnector::create_name(component_name, connector_name);
        }

        static std::string create_name(string component_name, string connector_name)
        {
            return component_name + "." + connector_name;
        }

        friend ostream &operator<<(ostream &os, const AnalysisConnector &obj)
        {
            os << "Connector { \n"
               << "name: " << obj.name << endl
               << "vr: " << obj.value_reference << endl
               << "type: " << obj.type << endl
               << "causality: " << obj.causality << endl
               << " }" << endl;

            return os;
        }

        /** @brief Convert to string for debugging purposes. */
        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }
    };

}