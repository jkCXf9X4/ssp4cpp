#include "common_xml_element.cpp"

namespace ssp4cpp::ssp1::ssd
{


    std::ostream &operator<<(std::ostream &os, const Elements &elems)
    {
        os << "Elements(Components: [";
        for (const auto &comp : elems.Components)
        {
            os << comp << ", ";
        }
        os << "], SignalDictionaryReferences: [";
        for (const auto &ref : elems.SignalDictionaryReferences)
        {
            os << ref << ", ";
        }
        os << "], Systems: [";
        for (const auto &sys : elems.Systems)
        {
            os << sys << ", ";
        }
        os << "])";
        return os;
    }

    void from_xml(const pugi::xml_node &node, Elements &elements)
    {
        BOOST_LOG_TRIVIAL(debug) << "Parsing Elements" << std::endl;

        for (auto e_node : node.children("ssd:Component"))
        {
            TComponent x;
            from_xml(e_node, x);
            elements.Components.push_back(x);
        }
        // for (auto e_node : node.children("ssd:SignalDictionaryReference"))
        // {
        //     TSignalDictionaryReference x;
        //     from_xml(e_node, x);
        //     elements.SignalDictionaryReferences.push_back(x);
        // }
        for (auto e_node : node.children("ssd:System"))
        {
            TSystem x;
            from_xml(e_node, x);
            elements.Systems.push_back(x);
        }
        BOOST_LOG_TRIVIAL(debug) << "Completed Elements" << std::endl;
    }
}