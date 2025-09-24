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
    // Kind of unnecessary but doesn't hurt ether
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

        virtual void print(std::ostream &os) const
        {
            auto strong_system_graph = common::graph::strongly_connected_components(common::graph::Node::cast_to_parent_ptrs(nodes));
            
            os << "Simulation Graph DOT:\n" 
            << common::graph::Node::to_dot(nodes) << "\n"
            << common::graph::ssc_to_string(strong_system_graph)
            << "\nStart nodes:\n";
            
            for (auto &model : get_start_nodes())
            {
                os << "Model: " << *model << "\n";
            }
        }

    };

}