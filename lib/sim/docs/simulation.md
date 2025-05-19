


Hybrid simulation


Physical/SW models: Logical execution time (LET) -> take a known timestep
Logical/electronics: Zero execution time (ZET) -> assume zero execution time 

Bounded Logical Execution time (BLET) - A mix of Bounded and Logical execution time where the designer sets a range of permissible timesteps.
- Enable implementing tool to decide what is reasonable when it comes to invocation schemas


time driving components to run jacobian style if possible, 
- how can we split the models by evaluating the delay between models, 
  - This would lead to correct behavior while still enabling high degree of parallelization 
  - This is kind of what Brown does but how can we do it without tlm?
  - Use the interpolation possibility in fmi, intermediate update
    - Does anyone support this? 
- Each connection would need to have a delay specified to know how it relates to models around it
- Each model could specify the information delay that is connected to its execution...
  - Models that take a fixed time, running 30hz, and would by determinism not be available until 1/30 seconds later
    - THis would enable a higher degree of separation!


How to fit the modes together
- The time driving components must have execution for each step
- The ZET components do not need to execute if there is no new input
- grouping of small independent component graphs for execution?

Evaluate how the graph should be split up in each timestep?
- Would ZET components need a invocation scheme for reasonable update frequency?
  - Could be the other way around, if the bounded time is low enough the component could be set to as a ZET component with the update frequency within the bound
  - If no new information is available then it would be possible to skip until new information is available

- a information graph where all information propagation is shown
- map the possible timesteps
- evaluate which components are ZET
- Allow iterative loops for ZET components if they are designed as more "functional", not possible for LET
- find a common timestep for the driving components (LET)
- evaluate what chains can be simulated independently
  



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