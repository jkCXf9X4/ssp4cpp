#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "common_log.hpp"

#include "FMI2_Enums.hpp"
#include "FMI2_Enums_Ext.hpp"
#include "SSP1_SystemStructureParameter_Ext.hpp"

#include "sim.hpp"

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

        std::string component_name;
        std::string connector_name;

        Causality causality;

        uint64_t value_reference;

        DataType type;
        std::size_t size;

        // for start value / parameter
        std::unique_ptr<ssp1::ext::ssv::Parameter> initial_value;

        AnalysisModel *model;

        AnalysisConnector()
        {
        }

        AnalysisConnector(std::string component_name,
                          std::string connector_name,
                          uint64_t value_reference,
                          DataType type)
        {
            this->component_name = component_name;
            this->connector_name = connector_name;
            update_name();

            this->value_reference = value_reference;
            this->type = type;
            this->size = fmi2::ext::enums::get_data_type_size(type);
        }

        virtual ~AnalysisConnector()
        {
            log.ext_trace("[{}] Destroying AnalysisConnector", __func__);
        }

        void update_name()
        {
            this->name = AnalysisConnector::create_name(component_name, connector_name);
        }

        static std::string create_name(std::string component_name, std::string connector_name)
        {
            return component_name + "." + connector_name;
        }

        virtual void print(std::ostream &os) const
        {
            os << "Connector { \n"
               << "name: " << name << std::endl
               << "vr: " << value_reference << std::endl
               << "type: " << type << std::endl
               << "causality: " << causality << std::endl
               << " }" << std::endl;
        }
    };

}