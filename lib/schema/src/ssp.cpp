

#include "ssp.hpp"

#include "xml_deserialize.hpp"

#include "SSP1_SystemStructureDescription_XML.hpp"
#include "SSP1_SystemStructureParameterValues_XML.hpp"
#include "SSP1_SystemStructureParameterMapping_XML.hpp"

// #include <cstring>
#include <format>
#include <filesystem>

namespace ssp4cpp
{

    Ssp::Ssp(const std::filesystem::path &file) : Archive(file, "ssp_")
    {
        log = common::Logger("Ssp", common::LogLevel::debug);

        this->ssd = common::xml::parse_file<ssp1::ssd::SystemStructureDescription>((dir / "SystemStructure.ssd").string(), "ssd:SystemStructureDescription");
        log.info("SSP Imported, {}", ssd->name);

        log.info("Parse parameter sets");

        // should be moved to ext
        std::vector<ssp1::ext::ssv::Bindings> bindings;
        if (ssd->System.ParameterBindings.has_value())
        {
            for (auto &binding : ssd->System.ParameterBindings.value().ParameterBindings)
            {
                ssp1::ext::ssv::Bindings b;
                if (binding.source.has_value())
                {
                    log.info("Parsing SSV {}", binding.source.value_or(""));
                    b.ssv = common::xml::parse_file<ssp1::ssv::ParameterSet>((dir / binding.source.value()).string(), "ssv:ParameterSet");

                    if (binding.ParameterMapping.has_value() && binding.ParameterMapping.value().source.has_value())
                    {
                        auto pm = binding.ParameterMapping.value();
                        b.ssm = common::xml::parse_file<ssp1::ssm::ParameterMapping>((dir / pm.source.value()).string(), "ssm:ParameterMapping");
                        log.info("Parsing SSM {}", pm.source.value_or(""));
                    }
                    bindings.push_back(std::move(b));
                }
            }
        }
        for (auto &binding : bindings)
        {
            log.ext_trace("Store parameters");
            for (auto &parameter : binding.ssv->Parameters.Parameters)
            {
                ssp1::ext::ssv::Parameter p(parameter.name, ssp1::ext::ssv::get_parameter_type(parameter));
                p.store_value(ssp1::ext::ssv::get_parameter_value(parameter));
                binding.parameters.push_back(std::move(p));
            }
            if (binding.ssm)
            {
                log.ext_trace("Store bindings");
                for (auto &map : binding.ssm->MappingEntry)
                {
                    ssp1::ext::ssv::Mapping m(map.source, map.target);
                    binding.mappings.push_back(std::move(m));
                }
            }
            log.ext_trace("Map bindings");
            for (auto &p : binding.parameters)
            {
                for (auto &m : binding.mappings)
                {
                    if (p.name == m.source)
                    {
                        p.name = m.target;
                    }
                }
            }
            log.ext_trace("Store global parameters");
            for (auto &p : binding.parameters)
            {
                parameter_map.insert_or_assign(p.name, std::move(p));
            }

            for (auto& [name, p]: parameter_map)
            {
                log.debug("[{}] - parameter {}, {}, {}", __func__, name, p.type.to_string(), *(double*)p.value.get());
            }
        }
    }
}