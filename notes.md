
git submodule add https://github.com/modelica/fmi-standard/tree/main /3rdParty/FMI3


tested with 
- GCC 13.1
- Ubuntu 22


https://github.com/nico/ninjatracing
Use ninjatracing to convert 

build/.ninja_log into 

ninjatracing build/.ninja_log > build/trace.json



sudo sysctl kernel.perf_event_paranoid=1


perf record ./build/app/sim/sim_app
perf report


perf report --dsos=sim_app 



        "start_time":0.0,
        "end_time":1000,
        "timestep": 0.1,
        "tolerance": 1e-4,


[Simulation][info] [simulate] Total walltime: 19.482770378 Model walltime: 18.173207303

with flto
[Simulation][info] [simulate] Total walltime: 17.962280479 Model walltime: 16.796389171


self.OMS.setCommandLineOption("--emitEvents=false")

what does this oms flag do?