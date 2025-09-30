
# Profiling

## Build profiling
https://github.com/nico/ninjatracing
Use ninjatracing to convert 


```
build/.ninja_log into 

ninjatracing build/.ninja_log > build/trace.json
```


## Runtime

```
sudo sysctl kernel.perf_event_paranoid=1


perf record -F 99 -g -o build/perf.data ./build/app/sim/sim_app ./resources/embrace/embrace.json


perf report --dsos=sim_app  -i ./build/perf.data

```

self.OMS.setCommandLineOption("--emitEvents=false")

what does this oms flag do?