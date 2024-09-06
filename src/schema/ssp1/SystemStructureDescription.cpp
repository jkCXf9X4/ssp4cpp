#include "common_xml_element.cpp"

namespace ssp4cpp::ssp1::ssd
{

    // using namespace ssp4cpp::ssp1::ssc;

    // Conversion functions for each struct
    void to_xml(pugi::xml_node &node, const SystemStructureDescription &desc)
    {
        return;
    }

    void from_xml(const pugi::xml_node &node, SystemStructureDescription &desc)
    {
        BOOST_LOG_TRIVIAL(debug) << "Parsing SystemStructureDescription" << std::endl;

        desc.version = get_attribute<string>(node, "version");
        desc.name = get_attribute<string>(node, "name");

        desc.id = get_optional_attribute<string>(node, "id");
        desc.description = get_optional_attribute<string>(node, "description");
        desc.author = get_optional_attribute<string>(node, "author");
        desc.fileversion = get_optional_attribute<string>(node, "fileversion");
        desc.copyright = get_optional_attribute<string>(node, "copyright");
        desc.license = get_optional_attribute<string>(node, "license");
        desc.generationTool = get_optional_attribute<string>(node, "generationTool");
        desc.generationDateAndTime = get_optional_attribute<string>(node, "generationDateAndTime");

        from_xml(node.child("ssd:System"), desc.System);

        // auto enumerations = node.child("ssc:Enumerations");
        // if (enumerations)
        // {
        //     from_xml(enumerations, *desc.Enumerations);
        // }
        // auto units = node.child("ssc:TUnits");
        // if (units)
        // {
        //     from_xml(units, *desc.Units);
        // }
        // auto def_exp = node.child("ssd:DefaultExperiment");
        // if (def_exp)
        // {
        //     from_xml(def_exp, *desc.DefaultExperiment);
        // }
        // auto annotations = node.child("ssc:Annotations");
        // if (annotations)
        // {
        //     from_xml(annotations, *desc.Annotations);
        // }
    }

    std::ostream &operator<<(std::ostream &os, const SystemStructureDescription &ssd)
    {
        os << "SystemStructureDescription(version: " << ssd.version
           << ", name: " << ssd.name
           << ", id: " << ssd.id.value_or("null")
           << ", description: " << ssd.description.value_or("null")
           << ", author: " << ssd.author.value_or("null")
           << ", fileversion: " << ssd.fileversion.value_or("null")
           << ", copyright: " << ssd.copyright.value_or("null")
           << ", license: " << ssd.license.value_or("null")
           << ", generationTool: " << ssd.generationTool.value_or("null")
           << ", generationDateAndTime: " << ssd.generationDateAndTime.value_or("null") << ")";

        return os;
    }
}