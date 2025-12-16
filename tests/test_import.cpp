

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

TEST_CASE("SSP Import SSP", "[SSP]")
{

    auto log = Logger("TEST::SSP_Import", LogLevel::debug);
    log(debug)("Opening ssp");

    auto ssp = ssp4cpp::Ssp("./tests/resources/embrace_scen");

    log(debug)("Imported ssp! \n");
    log(debug)("{}", ssp.to_string());

    log(debug)("Parsing ssp to external file");
    save_string("./tests/resources/references/embrace_scen_ssd.txt", ssp.ssd->to_string());

    REQUIRE(ssp.fmus.size() == 6);

    for (auto &[name, fmu] : ssp.fmus)
    {
        log(debug)("Resource: {}", name);

        // If these changes, evaluate if correct
        save_string("./tests/resources/references/embrace_scen_fmu_" + name + ".txt", fmu->md->to_string());
    }

    int index = 0;
    for (auto &binding : ssp.parameter_bindings )
    {

        // If these changes, evaluate if correct
        save_string("./tests/resources/references/embrace_scen_parameter_set" + std::to_string(index) + ".txt", binding.ssv->to_string());

        if (binding.ssm)
        {

           save_string("./tests/resources/references/embrace_scen_parameter_map" + std::to_string(index) + ".txt", binding.ssm->to_string());
        }
    }

    std::cout << "Parsing complete\n";
}

TEST_CASE("SSP Import delay Folder", "[SSP]")
{

    auto log = Logger("TEST::SSP_Import of delay ssp, folder", LogLevel::debug);
    log(debug)("Opening ssp");

    auto ssp = ssp4cpp::Ssp("./tests/resources/ssp_implicit_fmi2");

    log(debug)("Imported ssp! \n");
    log(debug)("{}", ssp.to_string());

    log(debug)("Parsing ssp to external file");
    save_string("./tests/resources/references/ssp_implicit_fmi2_ssd.txt", ssp.ssd->to_string());

    REQUIRE(ssp.fmus.size() == 6);

    for (auto &[name, fmu] : ssp.fmus)
    {
        log(debug)("Resource: {}", name);

        // If these changes, evaluate if correct
        save_string("./tests/resources/references/ssp_implicit_fmi2_fmu_" + name + ".txt", fmu->md->to_string());
    }

    int index = 0;
    for (auto &binding : ssp.parameter_bindings )
    {

        // If these changes, evaluate if correct
        save_string("./tests/resources/references/ssp_delay_parameter_set" + std::to_string(index) + ".txt", binding.ssv->to_string());

        if (binding.ssm)
        {

           save_string("./tests/resources/references/ssp_delay_parameter_map" + std::to_string(index) + ".txt", binding.ssm->to_string());
        }
    }

    std::cout << "Parsing complete\n";
}