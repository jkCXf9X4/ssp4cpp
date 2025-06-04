#pragma once

#include "common_node.hpp"
#include "common_string.hpp"

#include "fmu.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{
    class SimNode : public ssp4cpp::common::graph::Node
    {

    public:
        uint64_t time = 0;
        uint64_t delay = 0;
        /** Invoke this node for the given timestep. Override in derived classes. */
        virtual void invoke(uint64_t timestep)
        {
            // default no-op
        }
    };

    class Model : public SimNode
    {
    private:
        ssp4cpp::Fmu *fmu;

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
            return start_com + "." + start_con + "->" + end_com + "." + end_con;
        }

        std::string get_source_connector_name()
        {
            return Connector::create_name(start_component, start_connector);
        }

        std::string get_target_connector_name()
        {
            return Connector::create_name(end_component, end_connector);
        }

        friend ostream &operator<<(ostream &os, const Connection &obj)
        {
            os << "Connection { \n"
               << "name: " << obj.name << endl
               << "start_component: " << obj.start_component << endl
               << "start_connector: " << obj.start_connector << endl
               << "end_component: " << obj.end_component << endl
               << "end_connector: " << obj.end_connector << endl
               << " }" << endl;

            return os;
        }
    };

    // intra model connections
    class ModelVariable : public SimNode
    {
    public:
        string component;
        string variable_name;

        ModelVariable() {}

        ModelVariable(string component, string variable_name)
        {
            this->component = component;
            this->variable_name = variable_name;

            this->name = Connector::create_name(component, variable_name);
        }

        std::string get_connector_name()
        {
            return Connector::create_name(component, variable_name);
        }

        friend ostream &operator<<(ostream &os, const ModelVariable &obj)
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