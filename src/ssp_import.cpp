

#include "schema/ssp1/SystemStructureDescription.hpp"
#include "ssp_import.hpp"

#include <pugixml.hpp>
#include <iostream>

#include "ssd_xml.hpp"

#include "unzip.hpp"

using namespace std;
namespace fs = std::filesystem;

namespace ssp4cpp::ssp1
{
    SspImport::SspImport(const path &file) : original_file(file)
    {
        temp_dir = import_ssp(file.string()).value();
        ssd = parse_system_structure(temp_dir.string() + "/SystemStructure.ssd");

        auto elements = ssd.System.Elements;
        if (elements)
        {

            for (auto comp : elements.value().components)
            {
                SspResource res;
                res.type = comp.component_type;
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

    optional<fs::path> SspImport::import_ssp(const string &fileName)
    {
        auto ssp_file = fs::path(fileName);
        if (!fs::exists(ssp_file))
        {
            cout << "File does not exist";
            return nullopt;
        }

        std::string tmp_folder = std::tmpnam(nullptr);
        cout << "Temp folder: " << tmp_folder << endl;

        auto temp_dir = fs::path(tmp_folder.append("-ssp"));
        cout << "Temp dir: " << temp_dir << endl;

        fs::create_directory(temp_dir);

        ssp4cpp::zip_ns::unzip(ssp_file, temp_dir);

        return temp_dir;
    }
}