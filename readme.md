# SSP4CPP

SSP4CPP is a C++23 library for reading and analyzing System Structure and Parameterization (SSP) archives. The project provides code for loading `.ssp` files, parsing their `ssd` contents and building internal graphs that can be used for simulation or further analysis.

See the [SSP standard](https://ssp-standard.org) for more information about the file format.


## Project Structure

The project is organized into the following directories:

- `3rdParty`: Contains third-party libraries and dependencies.
- `app`: Contains example applications that demonstrate the use of the SSP4CPP library.
- `lib`: Contains the core SSP4CPP library code.
- `resources`: Contains SSP files and other resources used by the examples and tests.
- `tests`: Contains unit tests for the SSP4CPP library.
- `xml_parser`: Contains a Python script for generating C++ classes from XML schema definitions.

## Library Architecture

The SSP4CPP library is divided into three main components:

- `common`: Contains common data structures and utilities used by the other components.
- `schema`: Contains the C++ classes that represent the SSP schema. These classes are generated from the SSP XML schema definitions using the `xml_parser` tool.
- `sim`: Contains the simulation engine, which is responsible for loading and executing SSP files.
- `python`: THe python bindings for the simulation library

### Common

The `common` component provides a set of utility classes and functions that are used throughout the library.

### Schema

The `schema` component contains the C++ classes that represent the SSP schema. These classes are generated from the SSP XML schema definitions using the `xml_parser` tool. The generated classes provide a type-safe way to access the data in an SSP file.

It also has some utility functions, named as extensions. Located within files ending with "_Ext" 

### Sim

The `sim` component contains the simulation engine, which is responsible for loading and executing SSP files. The simulation engine uses the `schema` component to parse the SSP file and build a system structure graph.

The goal is to create a small experimental simulation engine to develop and test simulation strategies.

## Tools

### XML Parser

The `xml_parser` directory contains a Python script for generating C++ classes from XML schema definitions. This is used to create the C++ classes that represent the SSP schema. The script uses the `lxml` library to parse the XML schema and generate the C++ code.

## Getting started
1.  Clone the repository and initialize submodules:
    ```bash
    git clone git@github.com:jkCXf9X4/ssp4cpp.git
    git submodule update --init --recursive 
    or
    git clone --recursive git@github.com:jkCXf9X4/ssp4cpp.git
    ```

2.  Configure the build using the provided CMake preset (requires [vcpkg](https://github.com/microsoft/vcpkg)):
    ```bash
    cmake --preset=vcpkg
    ```

3.  Build the project:
    ```bash
    cmake --build build
    ```

Possible dependencies
sudo apt install ninja-build

## Running examples
After building, you can run the SSP simulation engine:
```bash
./build/app/sim/sim_app
```
This will run a simple simulation using one of the example ssps.

## Running tests
To run the tests, you first need to enable the `SSP4CPP_BUILD_TEST` option in CMake:
```bash
cmake -B build -S . -DSSP4CPP_BUILD_TEST=ON
cmake --build build && ./build/tests/test_1
```
ctest --test-dir build/tests currently malfunctions...

## Running python
Make sure to use the same version of python as you build for. First build the python bindings
```bash
cmake -B build -S . -DSSP4CPP_BUILD_PYTHON=ON
cmake --build build

python3 -m venv .venv
. ./.venv/bin/activate
pip install -r requirements.txt
pip install -e build/lib/python
```


## Contributing
Contributions are welcome! Please open an issue or submit a pull request if you have any improvements or suggestions.

## License
This project is released under the MIT license. See [LICENCE](LICENCE) for details.

## Credits
The project is heavily inspired by [FMI4cpp](https://github.com/NTNU-IHB/FMI4cpp). Credit where credit is due.