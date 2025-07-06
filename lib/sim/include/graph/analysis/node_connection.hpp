#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "common_log.hpp"

#include "node_base.hpp"
#include "node_connector.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::analysis::graph
{
 
    class ConnectionNode : public NodeBase
    {
    public:
        common::Logger log = common::Logger("ConnectionNode", common::LogLevel::debug);
        string start_component;
        string start_connector;
        string end_component;
        string end_connector;

        ConnectionNode() {}

        ConnectionNode(ssp4cpp::ssp1::ssd::Connection *connection)
        {
            start_component = connection->startElement.value();
            start_connector = connection->startConnector;
            end_component = connection->endElement.value();
            end_connector = connection->endConnector;

            update_name();
        }

        ~ConnectionNode()
        {
            log.ext_trace("[{}] Destroying ConnectionNode", __func__);
        }

        void update_name()
        {
            this->name = ConnectionNode::create_name(start_component, start_connector, end_component, end_connector);
        }

        static std::string create_name(string &start_com, string &start_con, string &end_com, string &end_con)
        {
            return start_com + "." + start_con + "->" + end_com + "." + end_con;
        }

        std::string get_source_connector_name()
        {
            return ConnectorNode::create_name(start_component, start_connector);
        }

        std::string get_target_connector_name()
        {
            return ConnectorNode::create_name(end_component, end_connector);
        }

        friend ostream &operator<<(ostream &os, const ConnectionNode &obj)
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

}