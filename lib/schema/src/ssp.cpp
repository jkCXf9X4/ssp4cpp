
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

    Ssp::Ssp()
    {
        using_tmp_dir = false;
    }

    Ssp::Ssp(const path &file) : original_file(file)
    {
        log = Logger("Ssp.Ssp", LogLevel::info);
        log.info("Importing SSP: {}", file.string());

        if (fs::is_regular_file(file))
        {
            dir = common::zip_ns::unzip_to_temp_dir(file.string(), "ssp_");
            using_tmp_dir = true;
        }
        else if (fs::is_directory(file))
        {
            dir = file;
            using_tmp_dir = false;
        }
        else
        {
            throw runtime_error("Fmu file is not a regular file or directory: " + file.string());
        }


        ssd = parse_system_structure(dir.string() + "/SystemStructure.ssd");

        log.info("SSP Imported");
    }

    Ssp::~Ssp()
    {
        log.debug("Destructor called");
        if (using_tmp_dir)
        {
            fs::remove_all(dir);
        }
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