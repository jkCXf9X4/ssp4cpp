#include <boost/log/trivial.hpp>

#include "modelDescription.hpp"

#include "modelDescription_XML.hpp"

#include "xml_deserialize.hpp"

namespace ssp4cpp::fmi2
{
    using namespace std;
    using namespace pugi;
    using namespace ssp4cpp::xml;

    // void from_xml(const xml_node &node, DefaultExperiment &desc)
    // {
    //     BOOST_LOG_TRIVIAL(trace) << "Parsing DefaultExperiment" << std::endl;

    //     desc.startTime = get_optional_attribute<double>(node, "startTime");
    //     desc.stopTime = get_optional_attribute<double>(node, "stopTime");
    //     desc.tolerance = get_optional_attribute<double>(node, "tolerance");
    //     desc.stepSize = get_optional_attribute<double>(node, "startTime");

    //     BOOST_LOG_TRIVIAL(trace) << "Completed DefaultExperiment" << std::endl;
    // }

    // void from_xml(const xml_node &node, fmi2ModelDescription &desc)
    // {
    //     BOOST_LOG_TRIVIAL(trace) << "Parsing fmi2ModelDescription" << std::endl;

    //     desc.fmiVersion = get_attribute<string>(node, "fmiVersion");
    //     desc.modelName = get_attribute<string>(node, "modelName");


    //     // from_xml(node.child("ssd:System"), desc.System);

    //     get_optional_class(node, "DefaultExperiment", desc.DefaultExperiment);

    //     BOOST_LOG_TRIVIAL(trace) << "Completed fmi2ModelDescription" << std::endl;
    // }
}