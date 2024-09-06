
#include "schema/system_structure_parser.hpp"
#include "schema/ssp1/SystemStructureDescription.hpp"

#include <pugixml.hpp>
#include <sstream>
#include <stdexcept>
#include <iostream>

namespace ssp4cpp::ssp1
{
    using namespace std;


    ostream& operator<<(ostream& os, const ssd::SystemStructureDescription& ssd)
    {
        return os << "SSD:\nversion: " << ssd.version << endl
                  << "name: " << ssd.name << endl;
    }


    std::unique_ptr<ssd::SystemStructureDescription> parse_system_structure(const std::string &fileName)
    {

        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(fileName.c_str());
        if (!result)
        {
            throw std::runtime_error("Unable to parse SystemStructure.ssd");
        }
        auto root = doc.child("ssd:SystemStructureDescription");

        ssd::SystemStructureDescription ssd;

        ssd.name = root.attribute("name").as_string();
        ssd.version = root.attribute("version").as_string();
        ssd.id = root.attribute("id").as_string();
        ssd.description = root.attribute("description").as_string();

        cout << ssd.name << endl;

        std::cout << ssd;


        // for (const auto &v : root)
        // {
        //     if (std::string("CoSimulation") == v.name())
        //     {
        //         coSimulation = parse_cs_attributes(v);
        //     }
        //     else if (std::string("ModelExchange") == v.name())
        //     {
        //         modelExchange = parse_me_attributes(v);
        //     }
        //     else if (std::string("DefaultExperiment") == v.name())
        //     {
        //         base.default_experiment = parse_default_experiment(v);
        //     }
        //     else if (std::string("ModelVariables") == v.name())
        //     {
        //         base.model_variables = std::move(parse_model_variables(v));
        //     }
        //     else if (std::string("ModelStructure") == v.name())
        //     {
        //         base.model_structure = std::move(parse_model_structure(v));
        //     }
        // }

        return std::make_unique<ssd::SystemStructureDescription>(ssd);
    }
}