
git submodule add https://github.com/modelica/fmi-standard/tree/main /3rdParty/FMI3


tested with 
- GCC 13.1
- Ubuntu 22


https://github.com/nico/ninjatracing
Use ninjatracing to convert 

build/.ninja_log into 

ninjatracing build/.ninja_log > build/trace.json



sudo sysctl kernel.perf_event_paranoid=1


perf record ./build/app/sim/sim_app -o ./build/perf.data
perf report

perf top ./build/app/sim/sim_app