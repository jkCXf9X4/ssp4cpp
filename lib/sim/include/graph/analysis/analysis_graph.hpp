#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "tarjan.hpp"

#include "analysis_connection.hpp"
#include "analysis_model.hpp"
#include "analysis_connector.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::sim::analysis::graph
{

    class AnalysisGraph : public common::str::IString
    {
    public:
        common::Logger log = common::Logger("AnalysisGraph", common::LogLevel::debug);

        std::map<std::string, std::unique_ptr<AnalysisModel>> models;
        std::map<std::string, std::unique_ptr<AnalysisConnector>> connectors;
        std::map<std::string, std::unique_ptr<AnalysisConnection>> connections;

        std::vector<AnalysisModel *> nodes;

        AnalysisGraph() = default;

        AnalysisGraph(std::map<std::string, std::unique_ptr<AnalysisModel>> models_,
                      std::map<std::string, std::unique_ptr<AnalysisConnector>> connectors_,
                      std::map<std::string, std::unique_ptr<AnalysisConnection>> connections_)
            : models(std::move(models_)),
              connectors(std::move(connectors_)),
              connections(std::move(connections_))

        {
            auto m = common::map_ns::map_unique_to_ref(models);
            nodes = common::map_ns::map_to_value_vector_copy(m);
        }

        std::vector<AnalysisModel *> get_start_nodes() const
        {
            auto start_nodes = common::graph::Node::get_ancestors(nodes);
            return start_nodes;
        }

        friend std::ostream &operator<<(std::ostream &os, const AnalysisGraph &obj)
        {
            auto strong_system_graph = common::graph::strongly_connected_components(common::graph::Node::cast_to_parent_ptrs(obj.nodes));
            
            os << "Simulation Graph DOT:\n" 
            << common::graph::Node::to_dot(obj.nodes) << std::endl
            << common::graph::ssc_to_string(strong_system_graph) << std::endl
            << "Start nodes:" << std::endl;
            
            for (auto &model : obj.get_start_nodes())
            {
                os << "Model: " << *model << std::endl;
            }
            return os;
        }

    };

}