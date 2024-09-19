#include <boost/log/trivial.hpp>

#include "modelDescription.hpp"

#include "modelDescription_XML.hpp"

#include "xml_deserialize.hpp"

namespace ssp4cpp::fmi2
{
    using namespace std;
    using namespace pugi;
    using namespace ssp4cpp::xml;

    void from_xml(const xml_node &node, BaseUnit &obj) {}
    void from_xml(const xml_node &node, DisplayUnit &obj) {}
    void from_xml(const xml_node &node, fmi2Unit &obj) {}
    void from_xml(const xml_node &node, UnitDefinitions &obj) {}
    void from_xml(const xml_node &node, Boolean &obj) {}
    void from_xml(const xml_node &node, Integer &obj) {}
    void from_xml(const xml_node &node, String &obj) {}
    void from_xml(const xml_node &node, Real &obj) {}
    void from_xml(const xml_node &node, Enumeration &obj) {}
    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj) {}
    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj) {}
    void from_xml(const xml_node &node, fmi2SimpleType &obj) {}
    void from_xml(const xml_node &node, TypeDefinitions &obj) {}
    void from_xml(const xml_node &node, Category &obj) {}
    void from_xml(const xml_node &node, LogCategories &obj) {}
    void from_xml(const xml_node &node, fmi2Annotation &obj) {}
    void from_xml(const xml_node &node, VendorAnnotations &obj) {}
    void from_xml(const xml_node &node, fmi2ScalarVariable &obj) {}
    void from_xml(const xml_node &node, unknown &obj) {}
    void from_xml(const xml_node &node, ModelStructure &obj) {}
    void from_xml(const xml_node &node, ModelVariables &obj) {}
    void from_xml(const xml_node &node, File &obj) {}
    void from_xml(const xml_node &node, ModelExchange &obj) {}
    void from_xml(const xml_node &node, CoSimulation &obj) {}


    void from_xml(const xml_node &node, DefaultExperiment &desc)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing DefaultExperiment" << std::endl;

        desc.startTime = get_optional_attribute<double>(node, "startTime");
        desc.stopTime = get_optional_attribute<double>(node, "stopTime");
        desc.tolerance = get_optional_attribute<double>(node, "tolerance");
        desc.stepSize = get_optional_attribute<double>(node, "startTime");

        BOOST_LOG_TRIVIAL(trace) << "Completed DefaultExperiment" << std::endl;
    }

    void from_xml(const xml_node &node, fmi2ModelDescription &desc)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2ModelDescription" << std::endl;

        desc.fmiVersion = get_attribute<string>(node, "fmiVersion");
        desc.modelName = get_attribute<string>(node, "modelName");


        // from_xml(node.child("ssd:System"), desc.System);

        get_optional_class(node, "DefaultExperiment", desc.DefaultExperiment);

        BOOST_LOG_TRIVIAL(trace) << "Completed fmi2ModelDescription" << std::endl;
    }
}