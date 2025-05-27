

#include "ssp.hpp"
#include "fmu.hpp"
#include "common_io.hpp"
#include "common_log.hpp"


#include "SSP1_SystemStructureDescription_Ext.hpp"
#include "FMI2_modelDescription_Ext.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm> 
#include <list>
#include <map>

#include <catch.hpp>

using namespace std;
using namespace ssp4cpp;
using namespace common::io;
using namespace common;

TEST_CASE("SSP Import", "[SSP]") {

    // auto log = Logger("cosim.main", LogLevel::debug);
    // log.debug("Opening ssp");

    auto ssp = ssp4cpp::Ssp("./resources/algebraic_loop_4.ssp");

    // log.debug("Imported ssp! \n");
    // log.debug("{}", ssp.to_string());

    // log.debug("Parsing ssp to external file");
    save_string("./tests/references/ssd.txt", ssp.ssd.to_string());

    auto resources = ssp1::ext::ssd::get_resources(ssp.ssd);
    REQUIRE(resources.size() == 4);

    for (auto &resource : resources)
    {
        // log.debug("Resource: {}", resource->name.value_or("null"));

        auto fmu = ssp4cpp::Fmu(ssp.dir / resource->source);
        auto p = pair(resource->name.value_or("null"), fmu);

        // If these changes, evaluate if correct
        save_string("./tests/references/fmu_" + resource->name.value_or("null") + ".txt", fmu.md.to_string());
    }

    std::cout << "Parsing complete\n";
}