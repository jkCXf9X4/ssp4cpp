#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "tarjan.hpp"

#include "node_connection.hpp"
#include "node_model.hpp"
#include "node_connector.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::sim::analysis::graph
{

    class AnalysisGraph
    {
    public:
        common::Logger log = common::Logger("Graph", common::LogLevel::debug);

        map<string, unique_ptr<ModelNode>> models;
        map<string, unique_ptr<ConnectorNode>> connectors;
        map<string, unique_ptr<ConnectionNode>> connections;

        vector<ModelNode *> nodes;

        AnalysisGraph() = default;

        AnalysisGraph(map<string, unique_ptr<ModelNode>> models_,
                      map<string, unique_ptr<ConnectorNode>> connectors_,
                      map<string, unique_ptr<ConnectionNode>> connections_)
            : models(std::move(models_)),
              connectors(std::move(connectors_)),
              connections(std::move(connections_))

        {
            auto m = map_ns::map_unique_to_ref(models);
            nodes = common::map_ns::map_to_value_vector_copy(m);
        }

        vector<ModelNode *> get_start_nodes()
        {
            auto start_nodes = common::graph::Node::get_ancestors(nodes);
            return start_nodes;
        }

        void print_analysis()
        {
            log.info("analysis_graph DOT: \n{}", common::graph::Node::to_dot(nodes));

            auto strong_system_graph = common::graph::strongly_connected_components(common::graph::Node::cast_to_parent_ptrs(nodes));
            log.info("{}", common::graph::ssc_to_string(strong_system_graph));

            log.info("Start nodes:");
            for (auto &model : get_start_nodes())
            {
                log.info("Model: {}", model->to_string());
            }
        }
    };

}