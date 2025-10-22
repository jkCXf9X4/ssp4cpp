

#include "ssp4cpp/ssp.hpp"

#include "xml_deserialize.hpp"

#include "SSP1_SystemStructureCommon_XML.hpp"
#include "SSP1_SystemStructureDescription_XML.hpp"
#include "SSP1_SystemStructureParameterMapping_XML.hpp"
#include "SSP1_SystemStructureParameterValues_XML.hpp"

#include <filesystem>

namespace ssp4cpp
{
    Ssp::Ssp(const std::filesystem::path &file) : Archive(file, "ssp_")
    {
        log = Logger("ssp4cpp.ssp", LogLevel::debug);

        this->ssd = utils::xml::parse_file<ssp1::ssd::SystemStructureDescription>((dir / "SystemStructure.ssd").string(), "ssd:SystemStructureDescription");
        log(info)("SSP Imported, {}", ssd->name);

        this->resources = get_resources(*this->ssd);
        this->parameter_bindings = get_parameter_bindings(this->dir, *this->ssd);
    }

    std::vector<ssp1::ssd::TComponent *> Ssp::get_resources(const ssp1::ssd::SystemStructureDescription &ssd) const
    {
        auto resources = std::vector<ssp1::ssd::TComponent *>();

        if (ssd.System.Elements.has_value())
        {
            for (auto &comp : ssd.System.Elements.value().Components)
            {
                // Make sure that the object is cast as a non const
                resources.push_back(const_cast<ssp1::ssd::TComponent *>(&comp));
            }
        }
        return resources;
    }

    std::vector<ParameterBindings> Ssp::get_parameter_bindings(std::filesystem::path &dir, ssp1::ssd::SystemStructureDescription &ssd)
    {
        log(trace)("[{}] Init", __func__);
        std::vector<ParameterBindings> bindings;
        if (ssd.System.ParameterBindings.has_value())
        {
            for (auto &binding : ssd.System.ParameterBindings.value().ParameterBindings)
            {
                ParameterBindings b;
                if (binding.source.has_value())
                {
                    log(debug)("[{}] Parsing SSV {}", __func__, binding.source.value_or(""));
                    b.ssv = utils::xml::parse_file<ssp1::ssv::ParameterSet>((dir / binding.source.value()).string(), "ssv:ParameterSet");

                    if (binding.ParameterMapping.has_value() && binding.ParameterMapping.value().source.has_value())
                    {
                        auto pm = binding.ParameterMapping.value();
                        b.ssm = utils::xml::parse_file<ssp1::ssm::ParameterMapping>((dir / pm.source.value()).string(), "ssm:ParameterMapping");
                        log(debug)("[{}] Parsing SSM {}", __func__, pm.source.value_or(""));
                    }
                    bindings.push_back(std::move(b));
                }
            }
        }
        return bindings;
    }
}
