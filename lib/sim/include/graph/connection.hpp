#pragma once

#include "fmu.hpp"
#include "common_node.hpp"
#include "common_string.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{
    class SimNode : public ssp4cpp::common::graph::Node
    {
    };

    class Model : public SimNode
    {
    private:
        ssp4cpp::Fmu *fmu;
        uint64_t time = 0;
        uint64_t delay = 0;

    public:
        Model() {}

        Model(std::string name, ssp4cpp::Fmu *fmu) : SimNode(name)
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

    class Connector : public SimNode
    {
    public:
        string component_name;
        string connector_name;

        ssp4cpp::ssp1::ssd::Connector *connector;

        Connector()
        {
        }

        Connector(
            string component_name,
            ssp4cpp::ssp1::ssd::Connector *connector)
        {
            this->component_name = component_name;
            this->connector_name = connector->name;
            this->connector = connector;

            this->name = Connector::create_name(component_name, connector_name);
        }

        friend ostream &operator<<(ostream &os, const Connector &obj)
        {
            os << "Connector { \n"
               << "variable_name: " << obj.name << endl
               << "connector_type: " << obj.connector << endl
               << " }" << endl;

            return os;
        }

        static std::string create_name(string component_name, string connector_name)
        {
            return component_name + "." + connector_name;
        }

    };

    class Connection : public SimNode
    {
    public:
        uint64_t delay = 0;

        string start_component;
        string start_connector;
        string end_component;
        string end_connector;

        ssp4cpp::ssp1::ssd::Connection *connection;

        Connection() {}

        Connection(ssp4cpp::ssp1::ssd::Connection *connection)
        {
            this->connection = connection;
            start_component = connection->startElement.value();
            start_connector = connection->startConnector;
            end_component = connection->endElement.value();
            end_connector = connection->endConnector;
            
            this->name = Connection::create_name(start_component, start_connector, end_component, end_connector);
        }

        static std::string create_name(string &start_com, string &start_con, string &end_com, string &end_con)
        {
            return start_com + "." + start_con + "->" +  end_com + "." + end_con;
        }
    };
}