#include "common_xml_element.cpp"

namespace ssp4cpp::ssp1::ssd
{


    void from_xml(const pugi::xml_node &node, TSystem &sys)
    {
        BOOST_LOG_TRIVIAL(debug) << "Parsing TSystem" << std::endl;

        sys.id = get_optional_attribute<string>(node, "id");
        sys.description = get_optional_attribute<string>(node, "description");

        sys.name = get_optional_attribute<string>(node, "name");

        if (auto a = node.child("ssd:Connectors"))
        {
            from_xml(a, *sys.Connectors);
        }
        // if (auto a = node.child("ssd:ElementGeometry"))
        // {
        //     from_xml(a, *sys.ElementGeometry);
        // }
        // if (auto a = node.child("ssd:ParameterBindings"))
        // {
        //     from_xml(a, *sys.ParameterBindings);
        // }
        if (auto a = node.child("ssd:Elements"))
        {
            from_xml(a, *sys.Elements);
        }
        if (auto a = node.child("ssd:Connections"))
        {
            from_xml(a, *sys.Connections);
        }
        // if (auto a = node.child("ssd:SignalDictionaries"))
        // {
        //     from_xml(a, *sys.SignalDictionaries);
        // }
        // if (auto a = node.child("ssd:SystemGeometry"))
        // {
        //     from_xml(a, *sys.SystemGeometry);
        // }
        // if (auto a = node.child("ssd:GraphicalElements"))
        // {
        //     from_xml(a, *sys.GraphicalElements);
        // }
        // if (auto a = node.child("ssd:Annotations"))
        // {
        //     from_xml(a, *sys.Annotations);
        // }
    }

    std::ostream &operator<<(std::ostream &os, const TSystem &sys)
    {
        os << "TSystem(id: " << sys.id.value_or("null")
           << ", description: " << sys.description.value_or("null")
           << ", name: " << sys.name.value_or("null") << ")";
        return os;
    }
}