

Analyze internal connections, this can be used for:


in Jacobi
- The data should be set in a specific order if there are direct feed thru inside the FMUs

- In these cases the set_real has secondary effects and the outputs should be set directly

- This isn't really pure Jacobi but some kind of hybrid


Move the set inputs / retrieve outputs outside the fmu_model to enable this


Check out 

- https://bauklimatik-dresden.de/mastersim/help/MasterSim_manual_en.html

1.9.3. Newton

iteration loop:
  in first iteration, compute Newton matrix via difference-quotient approximation

  loop over all slaves:
    set all input values
    tell slave to take a step

  loop over all slaves:
    retrieve all output values

  solve equation system
  compute modifications of variables

  perform convergence check

CAn this be used for co-simulation?