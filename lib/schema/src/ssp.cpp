
#include <pugixml.hpp>
#include <iostream>

#include "common_log.hpp"

#include "ssp.hpp"

#include "SSP1_SystemStructureDescription.hpp"
#include "SSP1_SystemStructureDescription_XML.hpp"

#include "zip.hpp"

using namespace std;
namespace fs = std::filesystem;

namespace ssp4cpp
{
    using namespace common;

    Ssp::Ssp(const path &file) : original_file(file)
    {
        log = Logger("Ssp.Ssp", LogLevel::info);
        log.info("Importing SSP: {}", file.string()); 
        
        temp_dir = common::zip_ns::unzip_to_temp_dir(file.string(), "ssp_");
        
        ssd = parse_system_structure(temp_dir.string() + "/SystemStructure.ssd");

        log.info("SSP Imported"); 
    }

    Ssp::~Ssp()
    {
        fs::remove_all(temp_dir);
    }

    ssp1::ssd::SystemStructureDescription Ssp::parse_system_structure(const string &fileName)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(fileName.c_str());
        if (!result)
        {
            throw runtime_error("Unable to parse SystemStructure.ssd");
        }
        auto root = doc.child("ssd:SystemStructureDescription");

        ssp1::ssd::SystemStructureDescription ssd;

        from_xml(root, ssd);

        return ssd;
    }
}