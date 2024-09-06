
#include "SystemStructureDescription.hpp"
#include "schema/ssp1/xml_functions.hpp"
#include "schema/ssp1/operators.hpp"
#include "xml_misc.cpp"

#include <iostream>


namespace ssp4cpp::ssp1::ssd
{
    using namespace ssp4cpp::xml;

    // Conversion functions for each struct
    void to_xml(pugi::xml_node& node, const SystemStructureDescription& desc) {
        // node.append_child("version").text().set(desc.version.c_str());
        // node.append_child("name").text().set(desc.name.c_str());
        // set_optional(node, "id", desc.id);
        // set_optional(node, "description", desc.description);
        // set_optional(node, "author", desc.author);
        // set_optional(node, "fileversion", desc.fileversion);
        // set_optional(node, "copyright", desc.copyright);
        // set_optional(node, "license", desc.license);
        // set_optional(node, "generationTool", desc.generationTool);
        // set_optional(node, "generationDateAndTime", desc.generationDateAndTime);
        // // Add other fields similarly...
        return;
    }

    void from_xml(const pugi::xml_node& node, SystemStructureDescription& desc) {

        desc.version = get_attribute<string>(node, "version");
        desc.name = get_attribute<string>(node, "name");

        // desc.name = node.child("name").text().as_string();
        // desc.id = get_optional<string>(node, "id");
        // desc.description = get_optional<string>(node, "description");
        // desc.author = get_optional<string>(node, "author");
        // desc.fileversion = get_optional<string>(node, "fileversion");
        // desc.copyright = get_optional<string>(node, "copyright");
        // desc.license = get_optional<string>(node, "license");
        // desc.generationTool = get_optional<string>(node, "generationTool");
        // desc.generationDateAndTime = get_optional<string>(node, "generationDateAndTime");
        // Add other fields similarly...
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