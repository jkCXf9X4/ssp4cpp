# Cyber-Physical Systems Simulator
## Goals:
- Evaluate how to simulate cyber physical systems (CPS) in a credible manner
- Evaluate how to simulate cps in an effective manner
  - Could include, but not limited to, parallelization, variable step sizes, other efficiency methods

## Requirements:
- Simulation credibility - simulation should, depending on intended use, be able to produce results that are credible and usable
  - Reproduce system behaviors in a realistic manner 
- Simulation determinism - simulation should always produce identical results for identical input
  - Information propagation between modes to be done in a deterministic way
- Enable physical, logical, sw models to be co-simulated


## Info
### Models
- Physical models: lives in the medium to long time domain. Information propagation between models often slow
- Logical models: lives in the short time domain. Information propagation between models often very quick
- Sw models: Lives in both short and long time domain. Information between models often very quick

## Efficiency
- models to be simulated as efficiently as possible, enable parallelization to a large extent


## Method

Design a experimental simulation engine for testing and evaluation of methods
It should be constrained to handle co-simulation and leveraging the capabilities defined in the FMI and SSP standard.


### Limitations
- Should not include model exchange, no solvers are needed
- Should not provide options for any alterations to models FMI/SSP. Only load and execute 
