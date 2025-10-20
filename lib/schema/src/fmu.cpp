

#include "utils/log.hpp"

#include "fmu.hpp"

#include "FMI2_modelDescription.hpp"
#include "FMI2_modelDescription_XML.hpp"

#include "xml_deserialize.hpp"

#include <filesystem>
#include <iostream>


namespace ssp4cpp
{
    Fmu::Fmu(const std::filesystem::path &file) : Archive(file, "fmi_")
    {
        log = common::Logger("ssp4cpp.fmu", common::LogLevel::debug);

        md = common::xml::parse_file<fmi2::md::fmi2ModelDescription>((dir / "modelDescription.xml").string(), "fmiModelDescription");
    }

}