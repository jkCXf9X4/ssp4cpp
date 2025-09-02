classDiagram

class Simulator {
  +ssp: std::unique_ptr<Ssp>
  +sim: std::unique_ptr<Simulation>
  +Simulator(ssp_path, props_path)
  +init()
  +simulate()
}

class Simulation {
  +ssp: Ssp*
  +fmu_handler: std::unique_ptr<handler::FmuHandler>
  +recorder: std::unique_ptr<utils::DataRecorder>
  +sim_graph: std::unique_ptr<graph::Graph>
  +Simulation(ssp)
  +init()
  +simulate()
}


  class FmuHandler {
    +ssp: Ssp*
    +fmu_map: std::map<string, std::unique_ptr<Fmu>>
    +fmu_info_map: std::map<string, std::unique_ptr<FmuInfo>>
    +FmuHandler(ssp)
    +init()
  }

  class FmuInfo {
    +system_name: std::string
    +model_name: std::string
    +fmu: ssp4cpp::Fmu*
    +model_description: ssp4cpp::fmi2::md::fmi2ModelDescription*
    +fmi4cpp_fmu: std::unique_ptr<fmi4cpp::fmi2::fmu>
    +cs_fmu: std::unique_ptr<fmi4cpp::fmi2::cs_fmu>
    +model: std::unique_ptr<fmi4cpp::fmi2::cs_slave>
    +FmuInfo(name, fmu)
  }



  class Graph {
    +models: std::map<string, std::unique_ptr<InvocableNode>>
    +nodes: std::vector<InvocableNode*>
    +executor: std::unique_ptr<ExecutionBase>
    +Graph(models)
    +init()
    +invoke(step_data)
  }

  class GraphBuilder {
    +analysis_graph: analysis::graph::AnalysisGraph*
    +recorder: utils::DataRecorder*
    +GraphBuilder(ag, recorder)
    +build(): std::unique_ptr<Graph>
  }

  class FmuModel {
    +name: std::string
    +fmu: handler::FmuInfo*
    +input_area: std::unique_ptr<utils::RingStorage>
    +output_area: std::unique_ptr<utils::RingStorage>
    +recorder: utils::DataRecorder*
    +connections: std::vector<ConnectionInfo>
    +FmuModel(name, fmu)
    +init()
    +invoke(step_data)
  }

  class AsyncNode {
    +worker: std::thread
    +invocable_obj: std::unique_ptr<Invocable>
    +AsyncNode(name, m)
    +init()
    +invoke(step_data)
  }

  class Invocable {
    <<Interface>>
    +init()
    +invoke(data)
  }

  class InvocableNode {
    <<Interface>>
  }


    class ExecutionBase {
      <<Abstract>>
      +models: std::vector<InvocableNode*>
      +ExecutionBase(models)
      +init()
      +invoke(step_data)
    }

    class Jacobi {
      +Jacobi(models)
      +invoke(step_data)
    }

    class Seidel {
      +Seidel(models)
      +invoke(step_data)
    }




    class AnalysisGraph {
        +models: std::map<string, std::unique_ptr<AnalysisModel>>
        +connectors: std::map<string, std::unique_ptr<AnalysisConnector>>
        +connections: std::map<string, std::unique_ptr<AnalysisConnection>>
        +AnalysisGraph(models, connectors, connections)
    }

    class AnalysisGraphBuilder {
        +ssp: ssp4cpp::Ssp*
        +fmu_handler: handler::FmuHandler*
        +AnalysisGraphBuilder(ssp, fmu_handler)
        +build(): std::unique_ptr<AnalysisGraph>
    }


  class DataRecorder {
    +file: std::ofstream
    +trackers: std::vector<Tracker>
    +DataRecorder(filename)
    +add_storage(storage)
    +start_recording()
    +stop_recording()
  }

  class RingStorage {
    +data: std::unique_ptr<DataStorage>
    +capacity: size_t
    +RingStorage(capacity, name)
    +add(name, type)
    +push(time)
  }

  class DataStorage {
    +data: std::unique_ptr<std::byte[]>
    +positions: std::vector<std::size_t>
    +types: std::vector<utils::DataType>
    +names: std::vector<std::string>
    +DataStorage(areas)
    +add(name, type)
    +allocate()
  }


Simulator *-- Simulation

Simulation *-- FmuHandler
Simulation *-- DataRecorder
Simulation *-- Graph
Simulation -->  GraphBuilder
Simulation -->  AnalysisGraphBuilder
AnalysisGraph --> GraphBuilder

FmuHandler *-- "many" FmuInfo

GraphBuilder --> Graph
InvocableNode --> Graph
Graph *-- AsyncNode
Jacobi --> ExecutionBase 
Seidel -->ExecutionBase  
ExecutionBase --> Graph 

Invocable ..> InvocableNode
InvocableNode --> AsyncNode
Invocable --> FmuModel
FmuInfo --> FmuModel
FmuModel --> RingStorage
AsyncNode *-- FmuModel

AnalysisGraphBuilder --> AnalysisGraph

DataRecorder *-- "many" RingStorage
RingStorage *-- DataStorage
