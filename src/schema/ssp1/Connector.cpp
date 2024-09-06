#include "common_xml_element.cpp"

namespace ssp4cpp::ssp1::ssd
{

    std::ostream &operator<<(std::ostream &os, const Connector &conn)
    {
        os << "Connector(id: " << conn.id.value_or("null")
           << ", description: " << conn.description.value_or("null")
           << ", name: " << conn.name
           << ", kind: " << conn.kind << ")";
        return os;
    }

    void from_xml(const pugi::xml_node &node, Connector &conn)
    {
        BOOST_LOG_TRIVIAL(debug) << "Parsing Connector" << std::endl;

        conn.description = get_optional_attribute<string>(node, "description");
        conn.id = get_optional_attribute<string>(node, "id");

        conn.name = get_attribute<string>(node, "name");
        conn.kind = get_attribute<string>(node, "kind");

    }

}