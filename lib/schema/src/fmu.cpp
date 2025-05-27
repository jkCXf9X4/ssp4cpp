



#include "common_log.hpp"

#include "fmu.hpp"

#include "FMI2_modelDescription.hpp"
#include "FMI2_modelDescription_XML.hpp"

#include "zip.hpp"

#include <pugixml.hpp>
#include <filesystem>
#include <iostream>


using namespace std;
namespace fs = std::filesystem;

namespace ssp4cpp
{
    using namespace common;

    Fmu::Fmu(const path &file) : original_file(file)
    {
        log = Logger("fmi2.Fmu", LogLevel::info);
        log.info("Importing fmi: {}", file.string());

        if (fs::is_regular_file(file))
        {
            dir = common::zip_ns::unzip_to_temp_dir(file.string(), "fmi_");
            using_tmp_dir = true;
        }
        else if (fs::is_directory(file))
        {
            dir = file;
            using_tmp_dir = false;
        }
        else{
            throw runtime_error("Fmu file is not a regular file or directory: " + file.string());
        }

        md = parse_model_description(dir.string() + "/modelDescription.xml");
    }

    Fmu::~Fmu()
    {
        if (using_tmp_dir)
        {
            fs::remove_all(dir);
        }
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