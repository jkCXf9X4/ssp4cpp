#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "node_base.hpp"
#include "node_connector.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{
    // intra model connections
    class ModelVariableNode : public NodeBase
    {
    public:
        string component;
        string variable_name;

        ModelVariableNode() {}

        ModelVariableNode(string component, string variable_name)
        {
            this->component = component;
            this->variable_name = variable_name;
            update_name();
        }

        void update_name()
        {
            this->name = ConnectorNode::create_name(component, variable_name);
        }

        std::string get_connector_name()
        {
            return ConnectorNode::create_name(component, variable_name);
        }

        friend ostream &operator<<(ostream &os, const ModelVariableNode &obj)
        {
            os << "ModelVariable { \n"
               << "name: " << obj.name << endl
               << "component: " << obj.component << endl
               << "variable_name: " << obj.variable_name << endl
               << " }" << endl;

            return os;
        }
    };

}