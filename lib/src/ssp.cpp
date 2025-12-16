

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


    static Logger static_log = Logger("ssp4cpp.ssp", LogLevel::info);

    static std::vector<ParameterBindings> get_parameter_bindings(std::filesystem::path &dir, ssp1::ssd::SystemStructureDescription &ssd)
    {
        static_log(trace)("[{}] Init", __func__);
        std::vector<ParameterBindings> bindings;
        if (ssd.System.ParameterBindings.has_value())
        {
            for (auto &binding : ssd.System.ParameterBindings.value().ParameterBindings)
            {
                ParameterBindings b;
                if (binding.source.has_value())
                {
                    static_log(debug)("[{}] Parsing SSV {}", __func__, binding.source.value_or(""));
                    b.ssv = utils::xml::parse_file<ssp1::ssv::ParameterSet>((dir / binding.source.value()).string(), "ssv:ParameterSet");

                    if (binding.ParameterMapping.has_value() && binding.ParameterMapping.value().source.has_value())
                    {
                        auto pm = binding.ParameterMapping.value();
                        b.ssm = utils::xml::parse_file<ssp1::ssm::ParameterMapping>((dir / pm.source.value()).string(), "ssm:ParameterMapping");
                        static_log(debug)("[{}] Parsing SSM {}", __func__, pm.source.value_or(""));
                    }
                    bindings.push_back(std::move(b));
                }
            }
        }
        else
        {
            static_log(trace)("[{}] No bindings found", __func__);
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
            static_log(trace)("Resource {}", name);

            auto fmu = std::make_unique<ssp4cpp::Fmu>(ssp->dir / resource->source);
            items[name] = std::move(fmu);
        }

        static_log(trace)("FMUs");
        for (auto &[name, fmu] : items)
        {
            static_log(trace)("{} : {}", name, fmu->to_string());
        }
        return items;
    }

        
    Ssp::Ssp(const std::filesystem::path &file, std::string ssd_name) : Archive(file, "ssp_")
    {
        log = Logger("ssp4cpp.ssp", LogLevel::debug);
        
        this->ssd = utils::xml::parse_file<ssp1::ssd::SystemStructureDescription>((dir / ssd_name).string(), "ssd:SystemStructureDescription");
        log(info)("SSP Imported, name: {} ssd: {}", this->ssd->name, ssd_name);
        
        this->fmus = create_fmu_map(this);
        this->parameter_bindings = get_parameter_bindings(this->dir, *this->ssd);
    }
}
