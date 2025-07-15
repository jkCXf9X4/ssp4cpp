
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
    
    SspInfo  --* FmuInfo


    class AnalysisGraph {
        vector~ConnectionNode~ connectors 
        vector~ConnectorNode~ connections 
        vector~ModelNode~ models 
        +AnalysisGraph(connectors, connections, models)
    
    }


    class AnalysisGraphBuilder {
        +build()  AnalysisGraph
    }
    AnalysisGraphBuilder ..> AnalysisGraph : creates
    SspInfo  --> AnalysisGraphBuilder : «input» 


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
    SimModelNode --* DataRecorder

    class Graph {
        vector~SimModelNode~ models 
    }
    Graph  --* SimModelNode

    class SimGraphBuilder {
        +build() : Graph
    }


    AnalysisGraph   -->  SimGraphBuilder : «input» 
    SimGraphBuilder ..> Graph : creates

    class Simulation {
        +execute()
    }
    ssp4cpp_Ssp --> Simulation : «input»  

    Simulation --* SspInfo : creates
    Simulation --* AnalysisGraphBuilder : uses 
    Simulation --* SimGraphBuilder : uses
    Simulation --* Graph : uses

    class Simulator {
        +execute()
    }

    Simulator --* Simulation 
    Simulator --* ssp4cpp_Ssp : creates

    class cli_interface {
        path ssp_path 
    }

    cli_interface --> Simulator : «input» 