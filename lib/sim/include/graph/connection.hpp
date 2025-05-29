#pragma once

#include "fmu.hpp"
#include "common_node.hpp"
#include "common_string.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{

    class Model : public ssp4cpp::common::graph::Node
    {
    private:
        ssp4cpp::Fmu* fmu;
        uint64_t time = 0;

    public:
        Model() {}

        Model(std::string name, ssp4cpp::Fmu* fmu) : Node(name)
        {
            this->fmu = fmu;
        }

        ~Model()
        {

        }

        friend ostream &operator<<(ostream &os, const Model &obj)
        {
            os << "Model { \n"
               << "name: " << obj.name << endl
               << "Fmu: " << obj.fmu->md.modelName << endl
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
        Node *model;
        std::string connector_type;

        Connector()
        {
        }

        Connector(string name, Node* model) : Node(name)
        {
            this->model = model;
        }

        friend ostream &operator<<(ostream &os, const Connector &obj)
        {
            os << "Connector { \n"
               << "variable_name: " << obj.name << endl
               << "connector_type: " << obj.connector_type << endl
               << " }" << endl;

            return os;
        }

        // get set function
    };

    class Connection : public ssp4cpp::common::graph::Node
    {
        uint64_t delay;

        Connection() {}
    };
}