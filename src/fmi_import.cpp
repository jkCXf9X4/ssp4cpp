#include <boost/log/trivial.hpp>


#include <pugixml.hpp>
#include <iostream>

#include "schema/fmi2/fmi2modelDescription.hpp"
#include "fmi_import.hpp"
#include "fmi2_xml.hpp"

#include "zip.hpp"

using namespace std;
namespace fs = std::filesystem;

namespace ssp4cpp::fmi2
{
    FmiImport::FmiImport(const path &file) : original_file(file)
    {
        BOOST_LOG_TRIVIAL(trace) << "Importing fmi: " << file << std::endl;
        temp_dir = import_fmi(file.string()).value();
        
        md = parse_model_description(temp_dir.string() + "/modelDescription.xml");
    }

    FmiImport::~FmiImport()
    {
        fs::remove_all(temp_dir);
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

    optional<fs::path> FmiImport::import_fmi(const string &fileName)
    {
        auto fmi_file = fs::path(fileName);
        if (!fs::exists(fmi_file))
        {
            BOOST_LOG_TRIVIAL(warning) << "File does not exist: " << fileName << "  " << std::endl;
            return nullopt;
        }

        std::string tmp_folder = std::tmpnam(nullptr);
        BOOST_LOG_TRIVIAL(debug) << "Temp folder: " << tmp_folder << endl;
        cout << "Temp folder: " << tmp_folder << endl;

        auto temp_dir = fs::path(tmp_folder.append("-ssp"));
        BOOST_LOG_TRIVIAL(debug) << "Temp dir: " << temp_dir << endl;

        fs::create_directory(temp_dir);

        ssp4cpp::zip_ns::unzip(fmi_file, temp_dir);

        return temp_dir;
    }
}