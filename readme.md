# SSP4CPP

Simple library for parsing System Structure and Parameterization (SSP) files

https://ssp-standard.org

Features:
 - Open zip to temporary directory
 - load ssd file and parse content to internal structure


## Note

SSP version 1.0: Not everything is implemented, mainly some basics for start of testing

Tested on:
 - Ubuntu 22.


# Build

Uses vcpkg for dependencies

```
git submodule init && git submodule update

cmake --preset=vcpkg

cmake --build build

cmake --build build && ./build/app/graph_analysis/ssp4cpp_graph
cmake --build build &> build.log && ./build/app/graph_analysis/ssp4cpp_graph
```


# Credits

Heavily inspired by FMI4cpp https://github.com/NTNU-IHB/FMI4cpp, credit where credit is due


create venv

python3 -m venv .venv
source ./.venv/bin/activate