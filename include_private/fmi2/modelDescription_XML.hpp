#pragma once

#include <pugixml.hpp>

#include "modelDescription.hpp"

namespace ssp4cpp::fmi2
{
    using namespace pugi;

    void from_xml(const xml_node &node, fmi2ModelDescription &annotations);
    void from_xml(const xml_node &node, DefaultExperiment &annotations);

}


