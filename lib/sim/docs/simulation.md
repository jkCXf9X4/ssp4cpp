

# Hybrid simulation
How to simulate hybrid simulations

## Models
Provide three data points for models and connections to enable conclusions regarding how to simulate models 

Timestep(t): the amount of time that the model will simulate and move into the future
Delay(d): The time the information take to propagate from input to output, relevant for models and connections
Frequency(f): Periodically run a model

NOTE: If delay is larger than timestep then the information should not be available until the delay is completed 
NOTE: If delay is shorter than timestep then the information could in theory be available before the model is completed. This will incur a non realistic behavior since the information will be available t-d to late in the simulation



### Logical execution time (LET)
Often physical models like hydraulics, fuel, multi body physics and so on

always needs to provide a timestep - will always drive time
might or might not represent a delay - some models may represent a physical delay of information
often not reasonable to provide a frequency - reality does not generally run periodically


### Zero execution time (ZET):
Often Logical/electric models like sensors, embedded devices

timestep is always zero
delay is always zero
Can run with or without a frequency


#### Identifying ZET

Options:
- See if only direct feedthrough is connected
- Evaluate dynamic response time, short could be categorized as ZET
  - Om det inte finns någon dynamik så blir det ett ZET
  - Men om det är dynamik så vill man ha ett mått på detta hur mycket LET det är 
    - Case study över detta!
- if the bounded time is low enough the component could be set to as a ZET component with the update frequency within the bound
- Explicit marker in eg FMI/Model descriptions


### Sometimes LET, sometimes ZET
Areas that may relate to one or the other, simulated software often fall in this category

Sw might or might not provide a timestep - sw may drive time of simulation
Sw might or might not represent a delay - sw can be slow and may represent a delay of information propagation
Sw should almost always should provide a frequency - its reasonable that sw run periodically


### Event 

Use existing clocks / events mechanisms

## How to simulate

Goal:
- Minimizing errors, maximize credibility
- Maximize the parallelization opportunities to enable faster simulations
- Maximizing model timesteps to minimize the simulation engine overhead

## Thesis: Information propagation information to enable parallelization

- Execution graph is constructed from information propagation
- Delays, that are physically or logically motivated, of information can enable splitting the execution graph into parts that can be executed in parallel
  - This would lead to correct behavior while still enabling high degree of parallelization 
  - This is kind of what Brown does but how can we do it without tlm?
- Use the interpolation possibility in fmi, intermediate update
  - Does anyone support this? 


### Prerequisites 
  - Each connection would have a delay specified to know how it relates to models around it
  - Each model could specify the information delay that is connected to its execution...

### Limitations
Splitting the models might be hard when taking delays into account for larger subsystems, if the hydraulics system is one unit using delays might be complex, the quickest dynamic of the system will dictate the model delay


### Simulation 

Split the models into chunks that are equal to the delay between them
this would enable running that chunks gauss-jacobi and the chunk itself gauss-seidel

NOTE:
- The LET components must have execution for each step
- The ZET components do not need to execute if there is no new input


Overview
- a information graph where all information propagation is shown
- map the possible timesteps
- evaluate which components are ZET
- Allow iterative loops for ZET components if they are designed as more "functional", not possible for LET
- find a common timestep for the driving components (LET)
- grouping of independent component graphs
- Execute the graphs in parallel


### Notes

- Grouping models into larger units would enable increased parallelization between groups with a larger
  - grouping models -> need to simulate cross vice? 


