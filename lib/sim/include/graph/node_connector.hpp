#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "node_base.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{
    // template class to enable constexpression invoke
    class Connector : public NodeBase
    {
    public:
        string component_name;
        string connector_name;

        Connector()
        {
        }

        Connector(std::string component_name, std::string connector_name)
        {
            this->component_name = connector_name;
            this->connector_name = connector_name;
            update_name();
        }

        void update_name()
        {
            this->name = Connector::create_name(component_name, connector_name);
        }

        static std::string create_name(string component_name, string connector_name)
        {
            return component_name + "." + connector_name;
        }

        friend ostream &operator<<(ostream &os, const Connector &obj)
        {
            os << "Connector { \n"
               << "name: " << obj.name << endl
               << " }" << endl;

            return os;
        }
    };

}