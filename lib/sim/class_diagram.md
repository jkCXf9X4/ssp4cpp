
classDiagram
    
    class ssp4cpp_Fmu {
    }
    class ssp4cpp_Ssp {
    }
    
    class FmuInfo {
        ssp4cpp_Fmu fmu
        fmi4cpp fmi4cpp_fmu
    }
    FmuInfo  --* ssp4cpp_Fmu

    class SspInfo {
        ssp4cpp_Ssp ssp
        vector~FmuInfo~ fmus
    }
    SspInfo  --* ssp4cpp_Ssp
    SspInfo  --* FmuInfo

    class ConnectionNode {
    }
    class ConnectorNode {
    }
    class ModelNode {
    }
    class AnalysisGraph {
        vector~ConnectionNode~ connectors 
        vector~ConnectorNode~ connections 
        vector~ModelNode~ models 
        +AnalysisGraph(connectors, connections, models)
    
    }
    AnalysisGraph  --* ConnectorNode
    AnalysisGraph  --* ConnectionNode
    AnalysisGraph  --* ModelNode

    class AnalysisGraphBuilder {
        SspInfo ssp
        +AnalysisGraphBuilder(SspInfo)
        +build() : 
    }
    AnalysisGraphBuilder ..> AnalysisGraph : creates
    AnalysisGraphBuilder  --* SspInfo

    class RingStorage {
        +push() int
        +get_valid_area(time) int64_t
        +get_pos(index) uint64_t
        +get_pos_rev(index) uint64_t
    }
    class DataStorage {
        +add(name, type) uint64_t
        +allocate()
        +get_locaction(area, index) byte*
    }
    class DataRecorder {
        +file
        +record(time, reference, type, data)
    }

    class SimModelNode {
        FmuInfo fmu
        DataStorage inputs
        RingStorage outputs
        
        fib and override input and output
        record input and output
        +invoke(time) uint64_t
    }
    SimModelNode  --* FmuInfo
    SimModelNode  --* RingStorage
    SimModelNode  --* DataStorage

    class Graph {
        vector~SimModelNode~ models 
    }
    Graph  --* SimModelNode

    class SimGraphBuilder {
        +build() Graph
    }
    SspInfo  --> SimGraphBuilder : «input» 

    SimGraphBuilder  --> AnalysisGraphBuilder : uses
    SimGraphBuilder  --* AnalysisGraph
    SimGraphBuilder  --* SimModelNode
    SimGraphBuilder ..> Graph : creates

    class Simulation {
        SspInfo ssp : creates/own
        DataRecorder recorder : creates/own
        Graph sim_graph : creates/own
        +execute()
    }
    ssp4cpp_Ssp --> Simulation : «input»  

    Simulation  --* SspInfo
    Simulation  --* DataRecorder
    Simulation --* SimGraphBuilder : uses
    Simulation  --* Graph

    class Simulator {
        path ssp_path :  «input»  
        ssp4cpp_Ssp ssp : creates/own
        Simulation sim : creates/own
        +execute()
    }

    Simulator --* Simulation
    Simulator --* ssp4cpp_Ssp

