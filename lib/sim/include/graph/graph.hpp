#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "tarjan.hpp"

#include "SSP1_SystemStructureDescription.hpp"

#include "fmu.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::analysis_graph
{
    class SimNode : public ssp4cpp::common::graph::Node
    {

    public:
        uint64_t delay = 0;

        common::Logger log = common::Logger("Analysis Node", common::LogLevel::ext_trace);

        SimNode() : Node() {}

        SimNode(const std::string &name) : ssp4cpp::common::graph::Node(name) {}
    };

    class Model : public SimNode
    {
    public:
        string fmu_name;

        map<string, Connector*> input_connector;
        map<string, Connector*> output_connector;

        Model() {}

        Model(std::string name, std::string fmu_name)
        {
            this->name = name;
            this->fmu_name = fmu_name;
        }

        friend ostream &operator<<(ostream &os, const Model &obj)
        {
            os << "Model { \n"
               << "Name: " << obj.name << endl
               << "Fmu: " << obj.fmu_name << endl
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

    class Connection : public SimNode
    {
    public:
        string start_component;
        string start_connector;
        string end_component;
        string end_connector;

        Connection() {}

        Connection(ssp4cpp::ssp1::ssd::Connection *connection)
        {
            start_component = connection->startElement.value();
            start_connector = connection->startConnector;
            end_component = connection->endElement.value();
            end_connector = connection->endConnector;

            update_name();
        }

        void update_name()
        {
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
            update_name();
        }

        void update_name()
        {
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

    class AnalysisGraph
    {
    public:
        common::Logger log = common::Logger("AnalysisGraph", common::LogLevel::ext_trace);

        map<string, Model *> models;
        vector<Model *> nodes;

        AnalysisGraph() = default;

        AnalysisGraph(map<string,Model *> models)
        {
            this->models = models;
            nodes = common::map_ns::map_to_value_vector_copy(models);

        }

        vector<Model *> get_start_nodes()
        {
            auto start_nodes = common::graph::Node::get_ancestors(nodes);
            return start_nodes;
        }

        void print_analysis()
        {
            log.info("analysis_graph DOT: \n{}", SimNode::to_dot(nodes));

            auto strong_system_graph = common::graph::strongly_connected_components(SimNode::cast_to_parent_ptrs(nodes));
            log.info("{}", common::graph::ssc_to_string(strong_system_graph));
        }
    };

}