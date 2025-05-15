

#include <pugixml.hpp>
#include <iostream>

#include "common_log.hpp"

#include "fmu.hpp"

#include "FMI2_modelDescription.hpp"
#include "FMI2_modelDescription_XML.hpp"

#include "zip.hpp"

using namespace std;
namespace fs = std::filesystem;

namespace ssp4cpp
{
    using namespace common;

    Fmu::Fmu(const path &file) : original_file(file)
    {
        log = Logger("fmi2.Fmu", LogLevel::info);
        log.info("Importing fmi: {}", file.string());

        temp_dir = common::zip_ns::unzip_to_temp_dir(file.string(), "fmi_");

        md = parse_model_description(temp_dir.string() + "/modelDescription.xml");
    }

    Fmu::~Fmu()
    {
        fs::remove_all(temp_dir);
    }

    fmi2::md::fmi2ModelDescription Fmu::parse_model_description(const string &fileName)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(fileName.c_str());
        if (!result)
        {
            throw runtime_error("Unable to parse modelDescription.xml");
        }
        auto root = doc.child("fmiModelDescription");

        fmi2::md::fmi2ModelDescription md;

        from_xml(root, md);

        return md;
    }

}