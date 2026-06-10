
#include "ssp4cpp/ssp.hpp"
#include "ssp4cpp/fmu.hpp"

#include "xml_deserialize.hpp"

#include "SSP1_SystemStructureCommon_XML.hpp"
#include "SSP1_SystemStructureDescription_XML.hpp"
#include "SSP1_SystemStructureParameterMapping_XML.hpp"
#include "SSP1_SystemStructureParameterValues_XML.hpp"

#include <filesystem>

namespace ssp4cpp
{
    Ssp::Ssp(const std::filesystem::path &file, std::string ssd_name) : Archive(file, "ssp_")
    {
        log = ssp4cpp::utils::log::make_logger("ssp4cpp.ssp." + file.stem().string());

        this->ssd = utils::xml::parse_file<ssp1::ssd::SystemStructureDescription>((dir / ssd_name).string(), "ssd:SystemStructureDescription");
        LOG_INFO(log, "SSP Imported, name: {name} ssd: {ssd}", this->ssd->name, ssd_name);
    }

    ssp1::ssv::ParameterSet Ssp::load_ssv(const std::string &relative_path) const
    {
        auto full_path = (dir / relative_path).string();
        LOG_TRACE_L1(log, "[{func}] Loading SSV: {path}", __func__, full_path);
        return *utils::xml::parse_file<ssp1::ssv::ParameterSet>(full_path, "ssv:ParameterSet");
    }

    ssp1::ssm::ParameterMapping Ssp::load_ssm(const std::string &relative_path) const
    {
        auto full_path = (dir / relative_path).string();
        LOG_TRACE_L1(log, "[{func}] Loading SSM: {path}", __func__, full_path);
        return *utils::xml::parse_file<ssp1::ssm::ParameterMapping>(full_path, "ssm:ParameterMapping");
    }
}
