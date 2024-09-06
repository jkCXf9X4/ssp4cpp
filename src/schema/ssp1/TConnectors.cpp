#include "common_xml_element.cpp"

namespace ssp4cpp::ssp1::ssd
{

    std::ostream &operator<<(std::ostream &os, const TConnectors &conns)
    {
        os << "TConnectors(list: [";
        for (const auto &conn : conns.list)
        {
            os << conn << ", ";
        }
        os << "])";
        return os;
    }

    void from_xml(const pugi::xml_node &node, TConnectors &connectors)
    {
        BOOST_LOG_TRIVIAL(debug) << "Parsing TConnectors" << std::endl;

        for (auto conn_node : node.children("ssd:Connectors"))
        {
            Connector c;
            from_xml(conn_node, c);
            connectors.list.push_back(c);
        }
    }
}