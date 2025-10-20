

#include "ssp.hpp"

#include "xml_deserialize.hpp"

#include "SSP1_SystemStructureDescription_XML.hpp"

#include <filesystem>

namespace ssp4cpp
{
    Ssp::Ssp(const std::filesystem::path &file) : Archive(file, "ssp_")
    {
        log = utils::Logger("ssp4cpp.ssp", utils::LogLevel::debug);

        this->ssd = utils::xml::parse_file<ssp1::ssd::SystemStructureDescription>((dir / "SystemStructure.ssd").string(), "ssd:SystemStructureDescription");
        log.info("SSP Imported, {}", ssd->name);

    }
}
