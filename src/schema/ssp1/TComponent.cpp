#include "common_xml_element.cpp"

namespace ssp4cpp::ssp1::ssd
{


    std::ostream &operator<<(std::ostream &os, const ComponentKind &kind)
    {
        switch (kind)
        {
        case ComponentKind::XFmuSharedlibrary:
            os << "XFmuSharedlibrary";
            break;
        case ComponentKind::XSspDefinition:
            os << "XSspDefinition";
            break;
        case ComponentKind::XSspPackage:
            os << "XSspPackage";
            break;
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const TComponent &comp)
    {
        os << "TComponent(id: " << comp.id.value_or("null")
           << ", description: " << comp.description.value_or("null")
           << ", name: " << comp.name.value_or("null")
           << ", source: " << comp.source
           << ", implementation: " << comp.implementation.value_or("null") << ")";
        return os;
    }

    void from_xml(const pugi::xml_node &node, TComponent &comp)
    {
        BOOST_LOG_TRIVIAL(debug) << "Parsing TComponent" << std::endl;

        comp.description = get_optional_attribute<string>(node, "description");
        comp.id = get_optional_attribute<string>(node, "id");

        comp.name = get_optional_attribute<string>(node, "name");

        comp.source = get_attribute<string>(node, "source");
        comp.implementation = get_optional_attribute<string>(node, "implementation");
    }


}