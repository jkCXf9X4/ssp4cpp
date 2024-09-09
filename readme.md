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

'''
cmake --preset=vcpkg

cmake --build build

cmake --build build &> build.log && ./build/test/ssp4cpp_test
'''


# Credits

Heavily inspired by FMI4cpp https://github.com/NTNU-IHB/FMI4cpp, credit where credit is due