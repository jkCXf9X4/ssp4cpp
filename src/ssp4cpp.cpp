

#include "schema/ssp1/SystemStructureDescription.hpp"
#include "ssp4cpp.hpp"

#include <pugixml.hpp>
#include <iostream>

#include "ssd_xml.hpp"

namespace ssp4cpp::ssp1::ssd
{
    using namespace std;

    ssd::SystemStructureDescription parse_system_structure(const string &fileName)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(fileName.c_str());
        if (!result)
        {
            throw runtime_error("Unable to parse SystemStructure.ssd");
        }
        auto root = doc.child("ssd:SystemStructureDescription");

        ssd::SystemStructureDescription ssd;

        from_xml(root, ssd);

        return ssd;
    }
}