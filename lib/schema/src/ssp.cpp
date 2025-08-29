

#include "ssp.hpp"

#include "xml_deserialize.hpp"

#include "SSP1_SystemStructureDescription_XML.hpp"
#include "SSP1_SystemStructureParameterValues_XML.hpp"
#include "SSP1_SystemStructureParameterMapping_XML.hpp"

// #include <cstring>
#include <format>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace ssp4cpp
{
    using namespace common;

        Ssp::Ssp(const path &file) : Archive(file, "ssp_")
        {
            log = Logger("Ssp", LogLevel::debug);
            ssd = parse_file<ssp1::ssd::SystemStructureDescription>((dir / "SystemStructure.ssd").string(), "ssd:SystemStructureDescription");
            log.info("SSP Imported, {}", ssd.name);

            if (ssd.System.ParameterBindings.has_value())
            {
                for (auto &binding : ssd.System.ParameterBindings.value().ParameterBindings)
                {
                    Bindings b;
                    if (binding.source.has_value())
                    {
                        log.info("Parsing SSV {}", binding.source.value());
                        b.ssv = parse_file<ssp1::ssv::ParameterSet>((dir / binding.source.value()).string(), "ssv:ParameterSet");

                        if (binding.ParameterMapping.has_value() && binding.ParameterMapping.value().source.has_value())
                        {
                            auto m = binding.ParameterMapping.value();
                            b.ssm = parse_file<ssp1::ssm::ParameterMapping>((dir / m.source.value()).string(), "ssm:ParameterMapping");
                        }
                    }
                    bindings.push_back(std::move(b));
                }
            }
        }

        std::string Ssp::to_string()
        {
            return common::str::stream_to_str(*this);
        }



}