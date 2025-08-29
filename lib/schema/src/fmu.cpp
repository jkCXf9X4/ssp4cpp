

#include "common_log.hpp"

#include "fmu.hpp"

#include "FMI2_modelDescription.hpp"
#include "FMI2_modelDescription_XML.hpp"

#include "xml_deserialize.hpp"

#include <filesystem>
#include <iostream>


namespace ssp4cpp
{
    namespace fs = std::filesystem;

    Fmu::Fmu(const path &file) : Archive(file, "fmi_")
    {
        log = Logger("Fmu", LogLevel::debug);
        md = common::xml::parse_file<fmi2::md::fmi2ModelDescription>((dir / "modelDescription.xml").string(), "fmiModelDescription");
    }

    std::string Fmu::to_string()
    {
        return common::str::stream_to_str(*this);
    }

}