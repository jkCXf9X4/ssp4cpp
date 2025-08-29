

#include "common_log.hpp"

#include "fmu.hpp"

#include "FMI2_modelDescription.hpp"
#include "FMI2_modelDescription_XML.hpp"

#include "xml_deserialize.hpp"

#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

namespace ssp4cpp
{
    using namespace common;

    Fmu::Fmu(const path &file) : Archive(file, "fmi_")
    {
        log = Logger("Fmu", LogLevel::debug);
        md = parse_file<fmi2::md::fmi2ModelDescription>((dir / "modelDescription.xml").string(), "fmiModelDescription");
    }

    std::string Fmu::to_string()
    {
        return common::str::stream_to_str(*this);
    }

}