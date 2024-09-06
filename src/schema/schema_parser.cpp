
#include "schema/schema_parser.hpp"
#include "schema/ssp1/SystemStructureDescription.hpp"
#include "schema/ssp1/xml_functions.hpp"
#include "schema/ssp1/operators.hpp"

#include <pugixml.hpp>
#include <sstream>
#include <stdexcept>
#include <iostream>

namespace ssp4cpp::ssp1::ssd
{
    using namespace std;

    unique_ptr<ssd::SystemStructureDescription> parse_system_structure(const string &fileName)
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

        cout << ssd;

        return make_unique<ssd::SystemStructureDescription>(ssd);
    }
}