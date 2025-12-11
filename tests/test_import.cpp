

#include "ssp4cpp/ssp.hpp"
#include "ssp4cpp/fmu.hpp"
#include "cutecpp/log.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

#include <catch.hpp>

// using namespace std;
using namespace ssp4cpp;

void save_string(const std::string &filename, const std::string &content)
{
    std::ofstream myfile;
    myfile.open(filename);
    myfile << content;
    myfile.close();
}

TEST_CASE("SSP Import", "[SSP]")
{

    auto log = Logger("TEST::SSP_Import", LogLevel::debug);
    log(debug)("Opening ssp");

    auto ssp = ssp4cpp::Ssp("./tests/resources/embrace_scen");

    log(debug)("Imported ssp! \n");
    log(debug)("{}", ssp.to_string());

    log(debug)("Parsing ssp to external file");
    save_string("./tests/resources/references/embrace_scen_ssd.txt", ssp.ssd->to_string());

    REQUIRE(ssp.resources.size() == 6);

    for (auto &resource : ssp.resources)
    {
        log(debug)("Resource: {}", resource->name.value_or("null"));

        auto fmu = new ssp4cpp::Fmu(ssp.dir / resource->source);

        // If these changes, evaluate if correct
        save_string("./tests/resources/references/embrace_scen_fmu_" + resource->name.value_or("null") + ".txt", fmu->md->to_string());
    }

    std::cout << "Parsing complete\n";
}
