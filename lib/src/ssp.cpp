

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
    ssp1::ssv::ParameterSet get_parameter_set(std::filesystem::path &dir, ssp1::ssd::ParameterBinding binding, ssp4cpp::utils::log::Logger *log)
    {
        // TODO: Add tests for this

        if (binding.source.has_value())
        {
            LOG_DEBUG(log, "[{func}] Parsing SSV {}", __func__, binding.source.value_or(""));

            auto parameter_set = utils::xml::parse_file<ssp1::ssv::ParameterSet>((dir / binding.source.value()).string(), "ssv:ParameterSet");
            return *parameter_set;
        }
        else if (binding.ParameterValues.has_value())
        {
            return binding.ParameterValues.value();
        }
        else
        {
            LOG_DEBUG(log, "[{func}] Empty ParameterBinding in ssd", __func__);
            return ssp1::ssv::ParameterSet();
        }
    }

    ssp1::ssm::ParameterMapping get_parameter_mapping(std::filesystem::path &dir, ssp1::ssd::ParameterMapping mapping, ssp4cpp::utils::log::Logger *log)
    {
        // TODO: Add tests for this

        if (mapping.source.has_value())
        {
            LOG_DEBUG(log, "[{func}] Parsing SSM {}", __func__, mapping.source.value_or(""));

            auto parameter_mapping = utils::xml::parse_file<ssp1::ssm::ParameterMapping>((dir / mapping.source.value()).string(), "ssm:ParameterMapping");
            return *parameter_mapping;

        }
        else if (mapping.ParameterMapping.has_value())
        {
            return mapping.ParameterMapping.value();
        }
        else
        {
            LOG_DEBUG(log, "[{func}] Empty ParameterMapping in ssd", __func__);
            return ssp1::ssm::ParameterMapping();
        }
    }

    static std::vector<ParameterBindings> get_parameter_bindings(std::filesystem::path &dir, ssp1::ssd::SystemStructureDescription &ssd, ssp4cpp::utils::log::Logger *log)
    {
        std::vector<ParameterBindings> bindings;
        if (ssd.System.ParameterBindings.has_value())
        {
            for (auto &binding : ssd.System.ParameterBindings.value().ParameterBindings)
            {
                // Add test for both external and internal paramersets
                ParameterBindings b;

                b.ssv = get_parameter_set(dir, binding, log);
                if (binding.ParameterMapping.has_value())
                {
                    b.ssm = get_parameter_mapping(dir, binding.ParameterMapping.value(), log);
                }
                bindings.push_back(std::move(b));
            }
        }
        else
        {
            LOG_DEBUG(log, "[{func}] No bindings found", __func__);
            LOG_WARNING(log, "[{func}] If there are internal component connected parameter sets, move these up to system level to get support", __func__);
        }
        return bindings;
    }

    static std::vector<ssp1::ssd::TComponent *> get_resources(const ssp1::ssd::SystemStructureDescription &ssd)
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

    /**
     * @brief Create a map of FMU names to loaded Fmu objects.
     */
    static std::map<std::string, std::unique_ptr<Fmu>> create_fmu_map(ssp4cpp::Ssp *ssp)
    {
        auto items = std::map<std::string, std::unique_ptr<Fmu>>();

        auto resources = get_resources(*ssp->ssd);

        for (auto &resource : resources)
        {
            auto name = resource->name.value_or("null");
            LOG_TRACE_L1(ssp->log, "Resource {}", name);

            auto fmu = std::make_unique<ssp4cpp::Fmu>(ssp->dir / resource->source);
            items[name] = std::move(fmu);
        }

        LOG_TRACE_L1(ssp->log, "FMUs");
        for (auto &[name, fmu] : items)
        {
            LOG_TRACE_L1(ssp->log, "{} : {}", name, fmu->to_string());
        }
        return items;
    }

    Ssp::Ssp(const std::filesystem::path &file, std::string ssd_name) : Archive(file, "ssp_")
    {
        log = ssp4cpp::utils::log::make_logger("ssp4cpp.ssp." + file.stem().string());

        this->ssd = utils::xml::parse_file<ssp1::ssd::SystemStructureDescription>((dir / ssd_name).string(), "ssd:SystemStructureDescription");
        LOG_INFO(log, "SSP Imported, name: {name} ssd: {ssd}", this->ssd->name, ssd_name);

        this->fmus = create_fmu_map(this);
        this->parameter_bindings = get_parameter_bindings(this->dir, *this->ssd, this->log);
    }
}
