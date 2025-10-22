

// This is a generated file, do not alter
// it is based on ssp1_ssm.toml

#pragma once

#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureParameterMapping.hpp"
#include <pugixml.hpp>

namespace ssp4cpp::ssp1::ssm
{
    using namespace pugi;

    void from_xml(const xml_node &node, TMappingEntry &obj);

    void from_xml(const xml_node &node, ParameterMapping &obj);


}
