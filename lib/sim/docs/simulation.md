

# Related work

Automatic parallelization and scheduling approaches for co-simulation of numerical models on multi-core processors (Saidi)
https://scholar.google.fr/scholar?oi=bibs&hl=en&cites=11753292007289493711

Towards the Verification of Hybrid Co-simulation Algorithms(Thule)
Requirements for hybrid cosimulation standards (Broman)
- samma tankar!


# Hybrid simulation
How to simulate hybrid co-simulations in a credible and effective way

Logical execution time (LET) -> take a known timestep
Zero execution time (ZET) -> assume zero execution time 

## Models
Provide three data points for models and connections to enable conclusions regarding how to simulate models 

LET/ZET: Long/short execution time
Delay(d): Physical or logical motivated time the information takes to propagate from input to output, relevant for models and connections
Frequency(f): Physical or logical motivated periodicity of execution
frequency should be specified if two models should use the same clock, named clock?


NOTE: If delay is larger than timestep then the information should not be available until the delay is completed 
NOTE: If delay is shorter than timestep then the information could in theory be available before the model is completed. This will incur a non realistic behavior since the information will be available t-d to late in the simulation


### LET
Models containing dynamic attributes, time derivatives != 0
Often physical models like hydraulics, fuel, multi body physics, computers and so on

Each timestep must be simulated once for correct execution ( not considering rollback) 


### ZET
Models characterized by algebraic attributes, time derivatives == 0
Does not simulate the step but only the current time, the model is not a function of time. 
Often Logical/electric models like sensors, embedded devices, valves 

Note: may or may not be stateless, it could have internal states that are dependent on execution order but these are not time dependent
It can use time as input just not have a delay

#### NOTES ZET
Same timestep could be simulated multiple times, each execution approximates a timestep of zero
Considering a software model that will send a msg at 0.99s
- if executing at first at 0.5s
- next time at 1s, the message is sent. But due to a loop the model will be executed again. this time the msg should not be sent


### Examples 

Everything is relative, a comparison from a systems perspective

PCB(logical gates): ZET, ~no delay, not executed periodically
Sensor: ZET, ~no delay, executed periodically 
SW: LET/ZET, ~no delay/short/long delay, executed periodically 
Hydraulic system: LET, long delay, not executed periodically
Advanced computer: LET, short delay and may be executed periodically 


#### Identifying ZET

Options:
- See if only direct feedthrough is connected
- Evaluate dynamic response time, short could be categorized as ZET
  - Om det inte finns någon dynamik så blir det ett ZET
  - Men om det är dynamik så vill man ha ett mått på detta hur mycket LET det är 
    - Case study över detta!
- if the bounded time is low enough the component could be set to as a ZET component with the update frequency within the bound
- Explicit marker in eg FMI/Model descriptions


### Event 

Use existing clocks / events mechanisms

## How to simulate

Goal:
- Minimizing errors, ensure credibility
- Maximize the parallelization opportunities to enable faster simulations
- Maximizing model timesteps to minimize the simulation engine overhead

## Thesis: Information propagation over time to enable parallelization

- Delays, that are physically or logically motivated, of information can enable splitting the execution graph into parts that can be executed in parallel
  - This would lead to correct behavior while still enabling high degree of parallelization 
  - This is kind of what Brown does but how can we do it without tlm?

- Use the interpolation possibility in fmi, intermediate update
  - Does anyone support this? 
  - Possible to run the model multiple times locally to emulate this... The same interpolation table could potentially be used


### Prerequisites 
  - Each connection would have a delay specified to know how it relates to models around it
  - Each model could specify the information delay that is connected to its execution...

### Limitations
Splitting the models might be hard when taking delays into account for larger subsystems, if the hydraulics system is one unit using delays might be complex, the quickest dynamic of the system will dictate the model delay


## Thesis: Information independence to enable parallelization
- Execution graph is constructed from information propagation

- If models have no information dependency between them then parallelization is possible


### Simulation 

Split the models into chunks that are equal to the delay between them
this would enable running that chunks gauss-jacobi and the chunk itself gauss-seidel

- Grouping models into larger units would enable increased parallelization between groups with a larger
  - grouping models -> need to simulate cross vice? 

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

Just because there is a delay does not mean that the timestep should be of this size, a model can be executed multiple times and the information should then be delayed in the integrating tool 
- Think more on this

splitting the graph is probably an empirical problem. generate -> test -> adapt. Repeat all (generate -> test) or (test -> adapt) 


## test system

digraph Test1 {
    // rankdir=LR;
    node [shape=record];

    // d: seconds   ·  optional<f>: Hz

    m1     [label="{Model_1|LET|d = 0.005}"];
    m2     [label="{Model_2|LET|d = 0.005}"];
    m3     [label="{Model_3|LET|d = 0.005}"];
    m4     [label="{Model_4|LET|d = 0.005}"];
    m5     [label="{Model_5|LET|d = 0.005}"];

    // Guidance & control
    m1 -> m2           [label="d = 0.002"];
    m2 -> m3           [label="d = 0.002"];
    m3 -> m4           [label="d = 0.002"];
    m4 -> m5           [label="d = 0.002"];
}