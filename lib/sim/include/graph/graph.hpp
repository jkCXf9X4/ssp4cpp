#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "simnode.hpp"
#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::graph
{
    using namespace std;

    inline auto log = common::Logger("sim::graph", common::LogLevel::ext_trace);

    using SimNode = sim::graph::SimNode;

    map<string, Model *> get_new_models(map<string, Fmu *> &fmu_map)
    {
        log.ext_trace("[{}] init", __func__);
        map<string, Model *> models;
        for (auto &[str, fmu] : fmu_map)
        {
            auto m = new Model(str, fmu);
            log.trace("[{}] New Model: {}", __func__, m->name);

            models[m->name] = m;
        }
        log.ext_trace("[{}] exit", __func__);
        return models;
    }

    map<string, Connector *> get_new_connectors(ssp4cpp::Ssp &ssp, map<string, Model *> models)
    {
        log.ext_trace("[{}] init", __func__);
        map<string, Connector *> items;
        if (ssp.ssd.System.Elements.has_value())
        {
            auto connectors = ssp1::ext::elements::get_connectors(
                ssp.ssd.System.Elements.value(),
                {ssp4cpp::fmi2::md::Causality::input, ssp4cpp::fmi2::md::Causality::output});

            for (auto &[index, connector, component] : connectors)
            {
                auto c = new Connector(models[component->name.value()], connector);
                log.trace("[{}] New Connector: {}", __func__, c->name);
                items[c->name] = c;
            }
        }
        log.ext_trace("[{}] exit, Total connectors created: {}", __func__, items.size());
        return items;
    }

    map<string, Connection *> get_new_connections(ssp4cpp::Ssp &ssp)
    {
        log.ext_trace("[{}] init", __func__);
        map<string, Connection *> items;
        for (auto &connection : ssp.ssd.System.Connections.value().Connections)
        {
            auto c = new Connection(&connection);
            log.trace("[{}] New Connection: {}", __func__, c->name);
            items[c->name] = c;
        }
        log.ext_trace("[{}] exit, Total connections created: {}", __func__, items.size());
        return items;
    }

    map<string, ModelVariable *> get_new_model_variables(map<string, Fmu *> &fmu_map)
    {
        log.ext_trace("[{}] init", __func__);
        map<string, ModelVariable *> items;
        for (auto [name, fmu] : fmu_map)
        {
            for (auto &variable : fmu->md.ModelVariables.ScalarVariable)
            {
                auto mv = new ModelVariable(name, variable.name);
                log.trace("[{}] New ModelVariable: {}", __func__, mv->name);
                items[mv->name] = mv;
            }
        }

        log.ext_trace("[{}] exit, Total model variables created: {}", __func__, items.size());
        return items;
    }

    vector<SimNode *> remove_dangling(vector<SimNode *> nodes)
    {
        vector<SimNode *> out;
        for (auto &n : nodes)
        {
            if (n->is_orphan())
            {
                log.ext_trace("[{}] Deleting {}", __func__, n->name);
                delete n;
            }
            else
            {
                out.push_back(n);
            }
        }
        return out;
    }



}
