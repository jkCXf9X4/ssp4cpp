#include <boost/log/trivial.hpp>

#include <pugixml.hpp>
#include <iostream>

#include "ssp_import.hpp"

#include "SSP1_SystemStructureDescription.hpp"
#include "SSP1_SystemStructureDescription_XML.hpp"

#include "zip.hpp"

using namespace std;
namespace fs = std::filesystem;

namespace ssp4cpp::ssp1
{
    SspImport::SspImport(const path &file) : original_file(file)
    {
        BOOST_LOG_TRIVIAL(info) << "Importing ssp: " << file << std::endl;
        temp_dir = ssp4cpp::common::zip_ns::unzip_to_temp_dir(file.string(), "ssp_");
        
        ssd = parse_system_structure(temp_dir.string() + "/SystemStructure.ssd");

        auto elements = ssd.System.Elements;
        if (elements)
        {

            for (auto comp : elements.value().Components)
            {
                SspResource res;
                res.type = comp.type;
                res.name = comp.name;
                res.file = temp_dir / comp.source;
                resources.push_back(res);
            }
        }
    }

    SspImport::~SspImport()
    {
        fs::remove_all(temp_dir);
    }

    ssd::SystemStructureDescription SspImport::parse_system_structure(const string &fileName)
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