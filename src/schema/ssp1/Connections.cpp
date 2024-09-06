#include "common_xml_element.cpp"

namespace ssp4cpp::ssp1::ssd
{

    std::ostream &operator<<(std::ostream &os, const Connections &conns)
    {
        os << "Connections(list: [";
        for (const auto &conn : conns.list)
        {
            os << conn << ", ";
        }
        os << "])";
        return os;
    }

    void from_xml(const pugi::xml_node &node, Connections &connections)
    {
        BOOST_LOG_TRIVIAL(debug) << "Parsing Connections" << std::endl;

        for (auto conn_node : node.children("ssd:Connection"))
        {
            Connection conn;
            from_xml(conn_node, conn);
            connections.list.push_back(conn);
        }
    }
}