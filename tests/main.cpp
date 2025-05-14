

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
#include <map>

using namespace std;
using namespace boost;
using namespace fmi4cpp;
using namespace ssp4cpp;
using namespace common::io;
using namespace common;

int main()
{
    auto log = Logger("cosim.main", LogLevel::debug);
    log.debug("Opening ssp");

    auto ssp = ssp4cpp::ssp1::SspImport("./resources/algebraic_loop_4.ssp");

    log.debug("Imported ssp! \n");
    log.debug("{}", ssp.to_str());

    log.debug("Parsing ssp to external file");
    save_string("./tests/references/ssd.txt", ssp.ssd.to_string());

    // Parsing FMI
    auto fmus = vector<pair<string, ssp4cpp::fmi2::FmiImport>>();
    auto fmu_name_to_ssp_name = pair<string, string>();

    for (int i = 0; i < ssp.resources.size(); i++)
    {
        auto resource = ssp.resources[i];

        auto fmu = ssp4cpp::fmi2::FmiImport(ssp.resources[i].file);
        auto p = pair(resource.name.value_or("null"), fmu);
        fmus.push_back(p);

        // If these changes, evaluate if correct
        save_string("./tests/references/fmu_" + std::to_string(i) + ".txt", fmu.md.to_string());
    }

    std::cout << "Parsing complete\n";
}