#pragma once

#include "sim_graph.hpp"
#include "analysis_graph.hpp"

namespace ssp4cpp::sim::sim_graph
{

  class SimGraphBuilder
  {
  public:
    unique_ptr<SimGraph> system;

    SimGraphBuilder() {}

    unique_ptr<SimGraph> create_graph(analysis_graph::AnalysisSystem &as,
                                      sim::FmuHandler &fmus,
                                      sim::VariableHandler &variables)
    {
      map<string, Model> models;
      for (auto &model : as.models)
      {
      }

      return std::move(system);
    }
  };
}
