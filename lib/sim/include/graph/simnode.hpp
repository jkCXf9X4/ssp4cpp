#pragma once

#include "common_node.hpp"
#include "common_string.hpp"

#include "fmu.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{
    class SimNode : public ssp4cpp::common::graph::Node
    {

    public:
        uint64_t start_time = 0;
        uint64_t end_time = 0;
        uint64_t delayed_time = 0;
        uint64_t delay = 0;

        bool init = false;

        common::Logger log = common::Logger("SimNode", common::LogLevel::ext_trace);

        SimNode() : Node() {}

        SimNode(const std::string &name) : ssp4cpp::common::graph::Node(name) {}

        virtual void init()
        {

        }

        /** Invoke this node for the given timestep. Override in derived classes. */
        virtual uint64_t invoke(uint64_t timestep)
        {
            start_time = end_time;
            end_time = start_time + timestep;
            delayed_time = end_time - delay;

            log.trace("[{}] SimNode start_time: {} end_time: {}, delayed_time {}", __func__, start_time, end_time, delayed_time);
            return delayed_time;
        }
    };

    class Model : public SimNode
    {
    public:
        ssp4cpp::Fmu *fmu;
        unique_ptr<fmi4cpp::fmi2::cs_fmu> cs_fmu;
        unique_ptr<fmi4cpp::fmi2::cs_slave> model;

        Model() {}

        Model(std::string name, ssp4cpp::Fmu *fmu) : SimNode(name)
        {
            this->fmu = fmu;

            auto fmu_t = fmi4cpp::fmi2::fmu(fmu->original_file);
            cs_fmu = fmu_t.as_cs_fmu();
        }

        ~Model()
        {
        }

        void init()
        {
            log.trace("[{}] Model init ", __func__);

            model = cs_fmu->new_instance();

            model->setup_experiment();
            model->enter_initialization_mode();
            model->exit_initialization_mode();
        }

        uint64_t invoke(uint64_t timestep) override
        {

            log.trace("[{}] Model {} ", __func__, timestep);
            // if (model->step(timestep))
            // {
            //     log.error("Error! step() returned with status: {}", std::to_string((int)model->last_status()));
            // }
            return SimNode::invoke(timestep);
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

    // template class to enable constexpression invoke
    class Connector : public SimNode
    {
    public:
        string component_name;
        string connector_name;

        Model *model_node;
        ssp4cpp::ssp1::ssd::Connector *connector;

        Connector()
        {
        }

        Connector(
            Model *model,
            ssp4cpp::ssp1::ssd::Connector *connector)
        {
            this->component_name = model->name;
            this->connector_name = connector->name;
            this->connector = connector;

            this->name = Connector::create_name(component_name, connector_name);
        }

        uint64_t invoke(uint64_t timestep) override
        {

            log.trace("[{}] Connector {} ", __func__, timestep);

            return SimNode::invoke(timestep);
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