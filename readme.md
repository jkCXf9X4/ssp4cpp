# SSP4CPP

SSP4CPP is a small C++23 library for reading and analyzing System Structure and Parameterization (SSP) archives. The project provides code for loading `.ssp` files, parsing their `ssd` contents and building internal graphs that can be used for simulation or further analysis.

The implementation is work in progress and currently supports a subset of the SSP 1.0 specification.

See the [SSP standard](https://ssp-standard.org) for more information about the file format.

## Features
- Extracts SSP archives to a temporary directory
- Parses `SystemStructure.ssd` into C++ objects
- Example applications for basic simulation

## Getting started
1. Clone the repository and initialise submodules
   ```bash
   git submodule update --init --recursive
   ```
2. Configure the build using the provided CMake preset (requires [vcpkg](https://github.com/microsoft/vcpkg))
   ```bash
   cmake --preset=vcpkg
   ```
3. Build the project
   ```bash
   cmake --build build
   ```

## Running examples
After building you can run the ssp simulation engine:
```bash
./build/app/sim/sim_app
```

## Running tests
```bash
cmake --build build && ./build/tests/test_1
```
```bash
cmake -B build -S . -DSSP4CPP_BUILD_TEST=ON
cmake --build build
cmake -B build -S . -DSSP4CPP_BUILD_TEST=OFF
```

## Running python
Make sure to use the same version of python as you build for

```bash
python3 -m venv .venv
. ./.venv/bin/activate
pip install -r requirements.txt
pip install -e build/lib/python
```

## License
This project is released under the MIT license. See [LICENCE](LICENCE) for details.

## Credits
The project is heavily inspired by [FMI4cpp](https://github.com/NTNU-IHB/FMI4cpp). Credit where credit is due.
