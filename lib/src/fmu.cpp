

#include "ssp4cpp/utils/log.hpp"

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
        log = ssp4cpp::utils::log::make_logger("ssp4cpp.fmu." + file.stem().string());

        auto path = (dir / "modelDescription.xml").string();

        LOG_DEBUG(log, "FMU parsing file: {}", path);
        md = utils::xml::parse_file<fmi2::md::fmi2ModelDescription>(path, "fmiModelDescription");
    }

}
