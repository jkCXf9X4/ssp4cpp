#pragma once

#include "fmu.hpp"
#include "common_node.hpp"
#include "common_string.hpp"

#include <string>

namespace ssp4cpp::sim::graph
{

    class FmuNode : public ssp4cpp::common::graph::Node
    {
    public:
        // ssp4cpp::Fmu fmu;
        std::string name;

        
        FmuNode(std::string name)
        {
            this->name = name;
            // this->fmu = fmu
        }

        friend ostream &operator<<(ostream &os, const FmuNode &obj)
        {
            os << "FmuNode { \n"
               << "name: " << obj.name << endl
               << " }" << endl;

            return os;
        }

    };

    class Connector : public ssp4cpp::common::graph::Node
    {
        std::string name;
        std::string type;
        // Connector() {}

        friend ostream &operator<<(ostream &os, const Connector &obj)
        {
            os << "Connector { \n"
               << "name: " << obj.name << endl
               << " }" << endl;

            return os;
        }

    };
}