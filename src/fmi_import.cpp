#include <boost/log/trivial.hpp>


#include <pugixml.hpp>
#include <iostream>

#include "fmi_import.hpp"

#include "modelDescription.hpp"
#include "modelDescription_XML.hpp"

#include "zip.hpp"

using namespace std;
namespace fs = std::filesystem;

namespace ssp4cpp::fmi2
{
    FmiImport::FmiImport(const path &file) : original_file(file)
    {
        BOOST_LOG_TRIVIAL(info) << "Importing fmi: " << file << std::endl;
        temp_dir = ssp4cpp::zip_ns::unzip_to_temp_dir(file.string(), "fmi_");
        
        md = parse_model_description(temp_dir.string() + "/modelDescription.xml");
    }

    FmiImport::~FmiImport()
    {
        // fs::remove_all(temp_dir);
    }

    fmi2ModelDescription FmiImport::parse_model_description(const string &fileName)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(fileName.c_str());
        if (!result)
        {
            throw runtime_error("Unable to parse modelDescription.xml");
        }
        auto root = doc.child("fmiModelDescription");

        fmi2ModelDescription md;

        from_xml(root, md);

        return md;
    }

}