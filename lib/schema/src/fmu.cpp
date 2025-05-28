

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