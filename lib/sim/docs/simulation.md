



Physical/SW models: Logical execution time (LET) -> take a known timestep
Logical/electronics: Zero execution time (ZET) -> assume zero execution time 

To use a version of Bounded execution time where the designer sets a range of permissible timesteps.
- Enable implementing tool to decide what is reasonable when it comes to invocation schemas
- For ~ZET components it would be possible to set up a graph
- ZET components would need a invocation scheme for reasonable update frequency 
  - Could be the other way around, if the bounded time is low enough the component could be set to as a ZET component with the update frequency within the bound

grouping of ZET components for graph execution?

time driving components to run jacobian style, 
- how can we split the models by evaluating the delay between models, this would lead to correct behavior while still enabling high degree of parallelization 

This is kind of what Brown does but how can we do it without tlm?
- Each connection would need to have a delay specified to know how it relates to models around it
- Each model would preferable specify the infomation delay that is connected to it
  - This would also enable a higher degree of separation

How to fit the modes together
- The time driving components must have execution for each step
- The ZET components do not need to execute if there is no new input

Evaluate how the graph should be split up in each timestep?

- a information graph where all information propagation is shown
- map the possible timesteps
- evaluate which components are ZET
- Allow iterative loops for ZET components, not for LET
- find a common timestep for the driving components (LET)
- evaluate what chains can be simulated independently
- 


A(BLET)
B(ZET)
C(BLET)
D(ZET)

A -> B 
B -> C 
B -> D
C -> D

The execution order should 
A -> B -> C -> D

But if we add 
D -> B

The execution order should 
A -> iterate(B -> D) -> C -> D



A logical/sw/physical model could decide the available range of execution 