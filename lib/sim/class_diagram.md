classDiagram
    class Simulator {
        +Ssp ssp
        +map~string, Fmu~ fmus
        +Simulation sim
        +Simulator(ssp_path, props_path)
        +init()
        +simulate()
    }

    class Simulation {
        +FmuHandler fmu_handler
        +DataRecorder recorder
        +Graph sim_graph
        +Ssp ssp
        +map~string, Fmu~ fmus
        +Simulation(ssp, fmus)
        +init()
        +simulate()
    }
    Simulator o-- Simulation

    class FmuHandler {
        +map~string, FmuInfo~ fmus
        +Ssp ssp
        +FmuHandler(str_fmu, ssp)
        +init()
    }
    Simulation o-- FmuHandler

    class FmuInfo {
        +string system_name
        +string model_name
        +Fmu fmu
        +fmi4cpp_fmu
        +cs_fmu
        +model
        +model_description
        +FmuInfo(name, fmu)
    }
    FmuHandler o-- FmuInfo

    class AnalysisGraphBuilder {
        +Ssp ssp
        +FmuHandler fmu_handler
        +AnalysisGraphBuilder(ssp, fmu_handler)
        +build() AnalysisGraph
    }
    Simulation ..> AnalysisGraphBuilder

    class AnalysisGraph {
        +map~string, AnalysisModel~ models
        +map~string, AnalysisConnector~ connectors
        +map~string, AnalysisConnection~ connections
        +vector~AnalysisModel~ nodes
    }
    AnalysisGraphBuilder ..> AnalysisGraph


    class GraphBuilder {
        +AnalysisGraph analysis_graph
        +DataRecorder recorder
        +GraphBuilder(ag, recorder)
        +build() Graph
    }
    AnalysisGraph ..> GraphBuilder
    Simulation ..> GraphBuilder

    class Graph {
        +map~string, Model~ models
        +vector~Model~ nodes
        +ExecutionBase executor
        +invoke(start_time, end_time, timestep)
    }
    GraphBuilder ..> Graph
    Simulation o-- Graph

    class Model {
        +FmuInfo fmu
        +RingStorage input_area
        +RingStorage output_area
        +DataRecorder recorder
        +map~string, ConnectorInfo~ inputs
        +map~string, ConnectorInfo~ outputs
        +vector~ConnectionInfo~ connections
        +invoke(start_time, end_time, timestep, valid_input_time)
    }
    Graph o-- Model
    Model o-- FmuInfo


    class ExecutionBase {
        <<interface>>
        +vector~Model~ models
        +invoke(start_time, end_time, timestep)
    }
    Graph o-- ExecutionBase

    class Seidel {
        +Model start_node
        +invoke(start_time, end_time, timestep)
    }
    ExecutionBase <|-- Seidel

    class Jacobi {
        +bool parallelize
        +invoke(start_time, end_time, timestep)
    }
    ExecutionBase <|-- Jacobi

    class DataRecorder {
        +ofstream file
        +vector~Tracker~ trackers
        +start_recording()
        +stop_recording()
    }
    Simulation o-- DataRecorder
    DataRecorder o-- Model

    class RingStorage {
        +DataStorage data
        +push(time)
        +get_valid_item(time, index) byte*
    }
    Model o-- RingStorage

    class DataStorage {
        +byte[] data
        +add(name, type)
        +allocate()
    }
    RingStorage o-- DataStorage