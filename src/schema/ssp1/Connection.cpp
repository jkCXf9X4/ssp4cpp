
#include "common_xml_element.cpp"

namespace ssp4cpp::ssp1::ssd
{

    std::ostream& operator<<(std::ostream& os, const Connection& connection) {
    os << "Connection {"
       << "startElement: " << (connection.startElement ? *connection.startElement : "null") << ", "
       << "startConnector: " << connection.startConnector << ", "
       << "endElement: " << (connection.endElement ? *connection.endElement : "null") << ", "
       << "endConnector: " << connection.endConnector << ", "
       << "suppressUnitConversion: " << (connection.suppressUnitConversion ? (*connection.suppressUnitConversion ? "true" : "false") : "null") << ", "
       << "LinearTransformation: " << (connection.LinearTransformation ? "present" : "null") << ", "
       << "BooleanMappingTransformation: " << (connection.BooleanMappingTransformation ? "present" : "null") << ", "
       << "IntegerMappingTransformation: " << (connection.IntegerMappingTransformation ? "present" : "null") << ", "
       << "EnumerationMappingTransformation: " << (connection.EnumerationMappingTransformation ? "present" : "null") << ", "
       << "ConnectionGeometry: " << (connection.ConnectionGeometry ? "present" : "null") << ", "
       << "Annotations: " << (connection.Annotations ? "present" : "null")
       << " }";
    return os;
}

    void to_xml(pugi::xml_node &node, const Connection &connection){

    }

    void from_xml(const pugi::xml_node &node, Connection &connection){
        BOOST_LOG_TRIVIAL(debug) << "Parsing Connection" << std::endl;

        connection.startElement = get_optional_attribute<string>(node, "startElement");
        connection.startConnector = get_attribute<string>(node, "startConnector");
        connection.endElement = get_optional_attribute<string>(node, "endElement");
        connection.endConnector = get_attribute<string>(node, "endConnector");

        BOOST_LOG_TRIVIAL(debug) << connection << std::endl;
    }

}