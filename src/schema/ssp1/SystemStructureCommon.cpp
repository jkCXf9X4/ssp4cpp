#include <boost/log/trivial.hpp>

#include "SystemStructureCommon.hpp"
#include "xml_helpers.hpp"

#include "ssc_xml.hpp"

using namespace std;
using namespace ssp4cpp::xml;

namespace ssp4cpp::ssp1::ssc
{
    void from_xml(const pugi::xml_node &node, TAnnotations &annotations) {}
    void from_xml(const pugi::xml_node &node, TEnumerations &enumerations) {}
    void from_xml(const pugi::xml_node &node, TUnits &units) {}
}