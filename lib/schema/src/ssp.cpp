

#include "ssp.hpp"

#include "xml_deserialize.hpp"

#include "SSP1_SystemStructureDescription_XML.hpp"

#include <filesystem>

namespace ssp4cpp
{
    Ssp::Ssp(const std::filesystem::path &file) : Archive(file, "ssp_")
    {
        log = common::Logger("ssp4cpp.ssp", common::LogLevel::debug);

        this->ssd = common::xml::parse_file<ssp1::ssd::SystemStructureDescription>((dir / "SystemStructure.ssd").string(), "ssd:SystemStructureDescription");
        log.info("SSP Imported, {}", ssd->name);

    }
}
