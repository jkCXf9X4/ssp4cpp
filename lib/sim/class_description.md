classDiagram

class Simulator {
    Coordinates loading of SSP archives and drives the simulation lifecycle.
}

class Simulation {
    Owns runtime components required to execute a simulation step-by-step.
}

class FmuHandler {
    Loads FMU archives and prepares instances for execution.
}

class FmuInfo {
    Stores metadata and prepared runtime objects for a single FMU.
}

class Graph {
    Organizes invocable nodes and orchestrates their execution order.
}

class GraphBuilder {
    Constructs execution graphs from analysis results and recorder hooks.
}

class FmuModel {
    Wraps an FMU instance with buffers, connections, and invocation logic.
}

class AsyncNode {
    Runs an invocable object on a dedicated worker thread.
}

class Invocable {
    Interface for objects that expose init and invoke entry points.
}

class InvocableNode {
    Interface marker for graph nodes that can be scheduled.
}

class ExecutionBase {
    Abstract executor that coordinates invocation of graph nodes.
}

class Jacobi {
    Execution strategy invoking nodes in parallel-style rounds.
}

class Seidel {
    Execution strategy invoking nodes sequentially with feedback.
}

class AnalysisGraph {
    Represents FMU models, connectors, and their relationships for analysis.
}

class AnalysisGraphBuilder {
    Transforms SSP definitions into analysis graphs.
}

class DataRecorder {
    Collects and persists signal data during simulation runs.
}

class RingStorage {
    Provides ring-buffer style storage for simulation signal values.
}

class DataStorage {
    Allocates contiguous memory areas and metadata for stored signals.
}

Simulator *-- Simulation

Simulation *-- FmuHandler
Simulation *-- DataRecorder
Simulation *-- Graph
Simulation *--  GraphBuilder
Simulation *--  AnalysisGraphBuilder
AnalysisGraph --> GraphBuilder

FmuHandler *-- "many" FmuInfo

GraphBuilder --> Graph
InvocableNode ..> Graph
Graph *-- AsyncNode
ExecutionBase ..> Jacobi 
ExecutionBase ..> Seidel 
Seidel --> Graph 
Jacobi --> Graph 

Invocable ..> InvocableNode
InvocableNode ..> AsyncNode
Invocable ..> FmuModel
FmuInfo --> FmuModel
FmuModel --> RingStorage
AsyncNode *-- FmuModel

AnalysisGraphBuilder --> AnalysisGraph

RingStorage --> DataRecorder
RingStorage *-- DataStorage

