

#include "cutecpp/log.hpp"

#include "ssp4cpp/fmu.hpp"
#include "ssp4cpp/schema/fmi2/FMI2_modelDescription.hpp"

#include "FMI2_modelDescription_XML.hpp"
#include "xml_deserialize.hpp"

#include <filesystem>
#include <iostream>


namespace ssp4cpp
{
    Fmu::Fmu(const std::filesystem::path &file) : Archive(file, "fmi_")
    {
        log = Logger("ssp4cpp.fmu", LogLevel::debug);

        md = utils::xml::parse_file<fmi2::md::fmi2ModelDescription>((dir / "modelDescription.xml").string(), "fmiModelDescription");
    }

}
