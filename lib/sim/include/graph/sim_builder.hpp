#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "fmu_handler.hpp"

#include "node_connection.hpp"
#include "node_model.hpp"
#include "node_connector.hpp"
#include "node_internal.hpp"

#include "analysis_graph.hpp"

#include "fmu.hpp"
#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::graph
{
    using namespace std;

    // // This class can be optimized allot
    // class Connectors
    // {
    // public:

    //     utils::DataStorage input_data(1);
    //     utils::DataStorage output_data(15);

    //     Connectors() {}

    //     void allocate()
    //     {
    //         for (auto [_, con]: input_connectors)
    //         {
    //             input_data.add(*con);
    //         }
    //         for (auto [_, con]: output_connectors)
    //         {
    //             output_data.add(*con);
    //         }
    //         input_data.allocate();
    //         output_data.allocate();
    //     }

    //     void write_to_model(uint64_t time)
    //     {
    //         int index = 0;
    //         for (auto &[_, c] : input_connectors)
    //         {
    //             void *data = c->data_handler->getData(time, c->data_reference);

    //             utils::write_to_model_(c->type, *c->fmu->model, c->value_reference, data);
    //             // storage for export
    //             memcpy(input_data.locations[index], data, input_data.sizes[index]);
    //             index += 1;
    //         }
    //     }

    //     void read_from_model(uint64_t time)
    //     {
    //         int pos = 0;
    //         for (auto &[_, c] : output_connectors)
    //         {
    //             auto d = output_data.locations[pos];
    //             utils::read_from_model_(c->type, *c->fmu->model, c->value_reference, d);

    //             c->data_handler->setData(time, c->data_reference, d);
    //             pos += 1;
    //         }
    //     }

    // };
    using AnalysisGraph = analysis::graph::AnalysisGraph;

    class SimGraphBuilder
    {
    public:
        static inline auto log = common::Logger("sim::graph::GraphBuilder", common::LogLevel::info);

        
        handler::FmuHandler *fmu_handler;


        SimGraphBuilder(handler::FmuHandler *fmu_handler, AnalysisGraph &ag)
        {
            this->fmu_handler = fmu_handler;
        }

        map<string, unique_ptr<ModelNode>> create_models(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, unique_ptr<ModelNode>> models;
            for (auto &[ssp_resource_name, local_resource_name] : ssp::ext::get_resources(ssp))
            {
                auto fmu = (fmu_handler->fmus[ssp_resource_name]).get();
                auto m = make_unique<ModelNode>(ssp_resource_name, local_resource_name, fmu);
                log.trace("[{}] New Model: {}", __func__, m->name);
                models[m->name] = std::move(m);
            }
            log.ext_trace("[{}] exit", __func__);
            return std::move(models);
        }


        unique_ptr<Graph> build()
        {
            log.ext_trace("[{}] init", __func__);
            auto models = create_models(*ssp);

            auto fmu_connections = ssp1::ext::elements::get_fmu_connections(ssp->ssd);

            log.debug("[{}] Connecting FMUs", __func__);
            for (auto &[source, target] : fmu_connections)
            {
                log.debug("[{}] Connecting: {} -> {}", __func__, source, target);
                models[source]->add_child(models[target].get());
            }


            log.ext_trace("[{}] exit", __func__);
            return make_unique<Graph>(std::move(models), std::move(connectors), std::move(connections));
        }
    };

}

//     for (auto [fmu_name, fmu] : fmu_map)
//     {
//         log.debug("[{}] Connecting internal dependencies, FMU:{}", __func__, fmu_name);

//         auto outputs = fmu->md.ModelStructure.Outputs;
//         if (outputs.has_value())
//         {

//             auto dependencies = ssp4cpp::fmi2::ext::dependency::get_dependencies_variables(
//                 outputs.value().Unknowns,
//                 fmu->md.ModelVariables,
//                 ssp4cpp::fmi2::md::DependenciesKind::dependent);

//             for (auto &[source, target, kind] : dependencies)
//             {
//                 auto source_id = Connector::create_name(fmu_name, source->name);
//                 auto target_id = Connector::create_name(fmu_name, target->name);
//                 SimNode *source_node;
//                 SimNode *target_node;

//                 // The connections can be from connectors or variables, maybe...
//                 if (connectors.contains(source_id))
//                 {
//                     source_node = connectors[source_id];
//                     log.debug("[{}] Source C {}", __func__, connectors[source_id]->name);
//                 }
//                 else
//                 {
//                     source_node = variables[source_id];
//                     log.debug("[{}] Source V {}", __func__, variables[source_id]->name);
//                 }

//                 if (connectors.contains(target_id))
//                 {
//                     target_node = connectors[target_id];
//                     log.debug("[{}] Target C {}", __func__, connectors[target_id]->name);
//                 }
//                 else
//                 {
//                     target_node = variables[target_id];
//                     log.debug("[{}] Target V {}", __func__, variables[target_id]->name);
//                 }
//                 log.debug("[{}] Connecting {} -> {}", __func__, source_node->name, target_node->name);
//                 source_node->add_child(target_node);
//             }
//         }
//     }
