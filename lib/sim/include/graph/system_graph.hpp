#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"
#include "tarjan.hpp"

#include "simnode.hpp"
#include "graph.hpp"
#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::graph
{
    using namespace std;

    using SimNode = sim::graph::SimNode;

    class SystemGraph
    {
    public:
        common::Logger log = common::Logger("sim::SystemGraph", common::LogLevel::ext_trace);

        std::map<std::string, std::unique_ptr<ssp4cpp::Fmu>> fmus;
        std::map<std::string, ssp4cpp::Fmu *> fmus_ref;

        ssp4cpp::Ssp *ssp;

        vector<SimNode *> analysis_graph;

        SystemGraph() {}

        SystemGraph(ssp4cpp::Ssp *ssp)
        {
            this->ssp = ssp;
            fmus = ssp4cpp::ssp::ext::create_fmu_map(*this->ssp);
            fmus_ref = map_ns::map_unique_to_ref(fmus);

            analysis_graph = create_analysis_graph();

            // make analysis

            // create execution graph
        }
        
        void print_dot()
        {
            log.info("analysis_graph DOT: \n{}", SimNode::to_dot(analysis_graph));
        }

        void print_tarjan()
        {
            auto strong_system_graph = common::graph::strongly_connected_components(SimNode::cast_to_parent_ptrs(analysis_graph));
            log.info("{}", common::graph::ssc_to_string(strong_system_graph));
        }

        vector<SimNode *> create_system_graph()
        {
            log.ext_trace("[{}] init", __func__);
            auto models = get_new_models(fmus_ref);

            auto fmu_connections = ssp1::ext::elements::get_fmu_connections(ssp->ssd);

            for (auto &[source, target] : fmu_connections)
            {

                log.debug("[{}] Connecting: {} -> {}", __func__, source, target);
                models[source]->add_child(models[target]);
            }
            vector<SimNode *> output;
            for (auto &[_, model] : models)
                output.push_back(model);
            auto o = remove_dangling(output);

            log.ext_trace("[{}] exit", __func__);
            return o;
        }

        vector<SimNode *> create_analysis_graph()
        {
            log.ext_trace("[{}] init", __func__);
            auto models = get_new_models(fmus_ref);
            auto connectors = get_new_connectors(*ssp, models);
            auto connections = get_new_connections(*ssp);

            log.debug("[{}] Start Connecting", __func__);
            for (auto &[name, c] : connections)
            {
                log.debug("[{}] Connecting {}", __func__, c->name);

                auto source_model = models[c->start_component];
                auto target_model = models[c->end_component];

                auto source_connector = connectors[c->get_source_connector_name()];
                auto target_connector = connectors[c->get_target_connector_name()];

                source_model->add_child(source_connector);
                source_connector->add_child(c);
                c->add_child(target_connector);
                target_connector->add_child(target_model);
            }

            vector<SimNode *> output;
            for (auto &[_, model] : models)
                output.push_back(model);
            for (auto &[_, connector] : connectors)
                output.push_back(connector);
            for (auto &[_, connection] : connections)
                output.push_back(connection);
            auto o = remove_dangling(output);

            log.ext_trace("[{}] exit", __func__);
            return o;
        }

        vector<SimNode *> create_feedthrough_graph()
        {
            log.ext_trace("[{}] init", __func__);
            auto models = get_new_models(fmus_ref);
            auto connectors = get_new_connectors(*ssp, models);
            auto connections = get_new_connections(*ssp);

            auto variables = get_new_model_variables(fmus_ref);

            log.debug("[{}] Connecting fmus", __func__);
            for (auto &[name, c] : connections)
            {
                log.debug("[{}] Connecting {}", __func__, c->name);

                auto source_connector = connectors[c->get_source_connector_name()];
                auto target_connector = connectors[c->get_target_connector_name()];

                source_connector->add_child(c);
                c->add_child(target_connector);
            }

            log.new_line();

            for (auto [fmu_name, fmu] : fmus_ref)
            {
                log.debug("[{}] Connecting internal dependencies, FMU:{}", __func__, fmu_name);

                auto outputs = fmu->md.ModelStructure.Outputs;
                if (outputs.has_value())
                {

                    auto dependencies = ssp4cpp::fmi2::ext::dependency::get_dependencies_variables(
                        outputs.value().Unknowns,
                        fmu->md.ModelVariables,
                        ssp4cpp::fmi2::md::DependenciesKind::dependent);

                    for (auto &[source, target, kind] : dependencies)
                    {
                        auto source_id = Connector::create_name(fmu_name, source->name);
                        auto target_id = Connector::create_name(fmu_name, target->name);
                        SimNode *source_node;
                        SimNode *target_node;

                        // The connections can be from connectors or variables, maybe...
                        if (connectors.contains(source_id))
                        {
                            source_node = connectors[source_id];
                            log.debug("[{}] Source C {}", __func__, connectors[source_id]->name);
                        }
                        else
                        {
                            source_node = variables[source_id];
                            log.debug("[{}] Source V {}", __func__, variables[source_id]->name);
                        }

                        if (connectors.contains(target_id))
                        {
                            target_node = connectors[target_id];
                            log.debug("[{}] Target C {}", __func__, connectors[target_id]->name);
                        }
                        else
                        {
                            target_node = variables[target_id];
                            log.debug("[{}] Target V {}", __func__, variables[target_id]->name);
                        }
                        log.debug("[{}] Connecting {} -> {}", __func__, source_node->name, target_node->name);
                        source_node->add_child(target_node);
                    }
                }
            }

            vector<SimNode *> output;
            for (auto &[_, model] : models)
                output.push_back(model);
            for (auto &[_, connector] : connectors)
                output.push_back(connector);
            for (auto &[_, connection] : connections)
                output.push_back(connection);
            for (auto &[_, variable] : variables)
                output.push_back(variable);
            auto o = remove_dangling(output);

            log.ext_trace("[{}] exit", __func__);
            return o;
        }
    };
}