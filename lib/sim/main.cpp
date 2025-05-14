

#include "ssp_import.hpp"
#include "fmi_import.hpp"
#include "common_io.hpp"
#include "common_log.hpp"


#include "SSP1_SystemStructureDescription_Ext.hpp"
#include "FMI2_modelDescription_Ext.hpp"

#include <iostream>
#include <fstream>
#include <cassert>

#include <boost/config.hpp>
#include <vector>
#include <algorithm> 

#include <list>

#include <fmi4cpp/fmi4cpp.hpp>

using namespace std;
using namespace boost;
using namespace fmi4cpp;
using namespace ssp4cpp;
using namespace common::io;
using namespace common;

int main()
{
    Logger(LogLevel::debug);

    Logger::debug("hello! {}", "me");

    // Opening zip
    std::cout << "Opening ssp\n";

    auto ssp = ssp4cpp::ssp1::SspImport("./app/graph_analysis/resources/algebraic_loop_4.ssp");

    std::cout << "Imported ssp! \n";

    std::cout << ssp << endl;

    std::cout << "Parsing ssp to external file\n";

    save_string("./app/graph_analysis/resources/parsed.txt", ssp.ssd.to_string());

    // Parsing FMI
    auto fmus = vector<pair<string, ssp4cpp::fmi2::FmiImport>>();
    auto fmu_name_to_ssp_name = pair<string, string>();

    for (int i = 0; i < ssp.resources.size(); i++)
    {
        auto resource = ssp.resources[i];

        auto fmu = ssp4cpp::fmi2::FmiImport(ssp.resources[i].file);
        auto p = pair(resource.name.value_or("null"), fmu);
        fmus.push_back(p);

        save_string("./app/graph_analysis/resources/" + std::to_string(i) + ".txt", fmu.md.to_string());
    }


    std::cout << "Parsing complete\n";
}