

// This is a generated file, do not alter
// it is based on ssp1_ssv.toml

#pragma once

#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureParameterValues.hpp"
#include <pugixml.hpp>

namespace ssp4cpp::ssp1::ssv
{
    using namespace pugi;

    void from_xml(const xml_node &node, Real &obj);

    void from_xml(const xml_node &node, Integer &obj);

    void from_xml(const xml_node &node, Boolean &obj);

    void from_xml(const xml_node &node, String &obj);

    void from_xml(const xml_node &node, Enumeration &obj);

    void from_xml(const xml_node &node, Binary &obj);

    void from_xml(const xml_node &node, TParameter &obj);

    void from_xml(const xml_node &node, TParameters &obj);

    void from_xml(const xml_node &node, ParameterSet &obj);


}
