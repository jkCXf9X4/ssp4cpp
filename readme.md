# SSP4CPP

SSP4CPP is a C++23 library for reading and analyzing System Structure and Parameterization (SSP) archives. The project provides code for loading `.ssp` files and parsing system structure information (`ssd`).

In addition it also parses FMI2 FMU's and the model description for ease of handling

See the [SSP standard](https://ssp-standard.org) and [FMI standard](https://fmi-standard.org) for more information about the file formats.


## Project Structure

The project is organized into the following directories:

- `3rdParty`: Contains third-party libraries and dependencies.
- `lib`: Contains the core SSP4CPP library code.
- `resources`: Contains toml representations of the bindings to be used as basis for generating the c++ bindings 
- `xml_parser`: Contains a Python script for generating C++ classes from XML schema definitions.

## Library Architecture

- `schema`: Contains the C++ classes that represent the SSP schema. These classes are generated from the SSP XML schema definitions using the `xml_parser` tool. The code is manually generated, inspect the git diff before committing the new representation  

The `schema` component contains the C++ classes that represent the SSP schema. These classes are generated from the SSP XML schema definitions using the `xml_parser` tool. The generated classes provide a type-safe way to access the data in an SSP file.

It also has some utility functions to extract and work with the SSP, named as extensions. Located within files ending with "_Ext" 

## Tools - XML Parser

The `xml_parser` directory contains a Python script for generating C++ classes from XML schema definitions. This is used to create the C++ classes that represent the SSP schema. The script uses the `lxml` library to parse the XML schema and generate the C++ code.

### Generate bindings

```bash
python3 -m venv venv
. ./venv/bin/activate

./xml_parser/xml_parser.md

```

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

4. Release/debug
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

Possible dependencies
sudo apt install ninja-build

## Contributing
Contributions are welcome! Please open an issue or submit a pull request if you have any improvements or suggestions.

## License
This project is released under the MIT license. See [LICENCE](LICENCE) for details.

## Credits
The project is heavily inspired by [FMI4cpp](https://github.com/NTNU-IHB/FMI4cpp). Credit where credit is due.