

#include "SSP1_SystemStructureParameter_Ext.hpp"

#include "xml_deserialize.hpp"

#include "SSP1_SystemStructureParameterValues_XML.hpp"
#include "SSP1_SystemStructureParameterMapping_XML.hpp"

namespace ssp4cpp::ssp1::ext::ssv
{
    std::vector<ParameterBindings> get_parameter_bindings(std::filesystem::path &dir, ssp1::ssd::SystemStructureDescription &ssd)
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

    std::vector<StartValue> get_start_values(std::vector<ParameterBindings> &bindings)
    {
        log(trace)("[{}] Init", __func__);

        std::vector<StartValue> start_values;
        for (auto &binding : bindings)
        {
            for (auto &parameter : binding.ssv->Parameters.Parameters)
            {
                log(trace)("[{}] - Store values, {}", __func__, parameter.name);
                StartValue start_value(parameter.name, get_parameter_type(parameter));
                start_value.store_value(get_parameter_value(parameter));

                if (binding.ssm)
                {
                    for (auto &map : binding.ssm->MappingEntry)
                    {
                        if (start_value.name == map.source)
                        {
                            log(trace)("[{}] Add mapping for {} - {}", __func__, parameter.name, map.target);
                            start_value.mappings.push_back(map.target);
                        }
                    }
                }
                start_values.push_back(std::move(start_value));
            }
        }
        return start_values;
    }

    std::map<std::string, StartValue> get_start_value_map(std::vector<StartValue> &start_values)
    {
        std::map<std::string, StartValue> parameter_map;
        for (auto &value : start_values)
        {
            log(trace)("[{}] - Parameter {}, {}", __func__, value.name, value.type.to_string());
            for (auto name : value.mappings)
            {
                if (parameter_map.contains(name))
                {
                    log(warning)("[{}] Overwriting parameter start value for, {}", __func__, name);
                }

                log(debug)("[{}] Inserting parameter {} as {}", __func__, value.name, name);
                parameter_map.insert_or_assign(name, value);

            }
        }
        return parameter_map;
    }

    std::map<std::string, StartValue> get_start_value_mappings(std::filesystem::path &dir, ssp1::ssd::SystemStructureDescription &ssd)
    {
        // Get initial values
        auto bindings = get_parameter_bindings(dir, ssd);
        auto initial_values = get_start_values(bindings);
        return get_start_value_map(initial_values);
    }
}
