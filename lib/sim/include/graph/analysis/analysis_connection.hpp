#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "common_log.hpp"

#include "analysis_connector.hpp"
#include "analysis_model.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::sim::analysis::graph
{

    class AnalysisConnection : public ssp4cpp::common::graph::Node
    {
        uint64_t delay = 0;

    public:
        common::Logger log = common::Logger("AnalysisConnection", common::LogLevel::debug);
        string source_component_name;
        string source_connector_name;
        string target_component_name;
        string target_connector_name;

        AnalysisConnector *source_connector;
        AnalysisConnector *target_connector;

        AnalysisModel *source_model;
        AnalysisModel *target_model;

        AnalysisConnection()
        {
        }

        AnalysisConnection(ssp4cpp::ssp1::ssd::Connection *connection)
        {
            source_component_name = connection->startElement.value();
            source_connector_name = connection->startConnector;
            target_component_name = connection->endElement.value();
            target_connector_name = connection->endConnector;

            update_name();
        }

        ~AnalysisConnection()
        {
            log.ext_trace("[{}] Destroying AnalysisConnection", __func__);
        }

        void update_name()
        {
            this->name = AnalysisConnection::create_name(source_component_name, source_connector_name, target_component_name, target_connector_name);
        }

        static std::string create_name(string &start_com, string &start_con, string &end_com, string &end_con)
        {
            return start_com + "." + start_con + "->" + end_com + "." + end_con;
        }

        std::string get_source_connector_name()
        {
            return AnalysisConnector::create_name(source_component_name, source_connector_name);
        }

        std::string get_target_connector_name()
        {
            return AnalysisConnector::create_name(target_component_name, target_connector_name);
        }

        friend ostream &operator<<(ostream &os, const AnalysisConnection &obj)
        {
            os << "Connection { \n"
               << "name: " << obj.name << endl
               << "source_component_name: " << obj.source_component_name << endl
               << "source_connector_name: " << obj.source_connector_name << endl
               << "target_component_name: " << obj.target_component_name << endl
               << "target_connector_name: " << obj.target_connector_name << endl
               << " }" << endl;

            return os;
        }
    };

}