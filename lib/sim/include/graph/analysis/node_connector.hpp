#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "common_log.hpp"

#include "node_base.hpp"
#include "data_type.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::analysis::graph
{

    // template class to enable constexpression invoke
    class ConnectorNode : public NodeBase
    {
    public:
        common::Logger log = common::Logger("ConnectorNode", common::LogLevel::debug);

        string component_name;
        string connector_name;

        uint64_t value_reference;

        utils::DataType type;

        ConnectorNode()
        {
        }

        ConnectorNode(std::string component_name,
                      std::string connector_name,
                      uint64_t value_reference,
                      handler::DataType type)
        {
            this->component_name = component_name;
            this->connector_name = connector_name;
            update_name();

            this->value_reference = value_reference;
            this->type = type;
        }

        virtual ~ConnectorNode()
        {
            log.ext_trace("[{}] Destroying ConnectorNode", __func__);
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
               << "vr: " << obj.value_reference << endl
               << "type: " << obj.type << endl
               << " }" << endl;

            return os;
        }
    };

}