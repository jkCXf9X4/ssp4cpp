

Simulator 
- handles top resources, shared across simulations
  - ssp, ssp4cpp::fmu, config files
  - starting and stopping simulations

Simulation
- handles resources related to single simulation
  - analysis graph, simulation graph, fmi4c co-simulation resources




Data handler
-  manages the data that is passed between the models
-  

FMU handler 
- owns the fmu resource
- manages initialization and teardown


Variable handler
- abstracts away the different variable types
