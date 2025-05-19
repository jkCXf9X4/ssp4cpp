#pragma once

#include "fmu.hpp"
#include "common_node.hpp"
#include "common_string.hpp"

#include <string>

namespace ssp4cpp::sim::graph
{

    class Model : public ssp4cpp::common::graph::Node
    {
        private:
        ssp4cpp::Fmu fmu;
        uint64_t time;

    public:
        Model(){}

        Model(std::string name, ssp4cpp::Fmu fmu) :Node(name)
        {
            this->fmu = fmu;
        }

        friend ostream &operator<<(ostream &os, const Model &obj)
        {
            os << "Model { \n"
               << "name: " << obj.name << endl
               << "Fmu: " << obj.fmu.md.modelName << endl
               << " }" << endl;

            return os;
        }

        void invoke(uint64_t timestep)
        {

        }

    };

    class Connector : public ssp4cpp::common::graph::Node
    {
        // get/set function pointer
        Model * model;
        std::string variable_name;
        std::string connector_type;

        Connector()
        {

        }

        friend ostream &operator<<(ostream &os, const Connector &obj)
        {
            os << "Connector { \n"
               << "variable_name: " << obj.variable_name << endl
               << "connector_type: " << obj.connector_type << endl
               << " }" << endl;

            return os;
        }

        // get set function 

    };
}