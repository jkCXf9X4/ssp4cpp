

#include "ssp4cpp/ssp.hpp"
#include "ssp4cpp/fmu.hpp"
#include "ssp4cpp/utils/log.hpp"

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

    auto log = ssp4cpp::utils::log::simple_logger();
    LOG_DEBUG(log, "Opening ssp");

    auto ssp = ssp4cpp::Ssp("./tests/resources/embrace_scen");

    LOG_DEBUG(log, "Imported ssp! \n");
    LOG_DEBUG(log, "{}", ssp.to_string());

    LOG_DEBUG(log, "Parsing ssp to external file");
    save_string("./tests/resources/references/embrace_scen_ssd.txt", ssp.ssd->to_string());

    REQUIRE(ssp.fmus.size() == 6);

    for (auto &[name, fmu] : ssp.fmus)
    {
        LOG_DEBUG(log, "Resource: {}", name);

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

    auto log = ssp4cpp::utils::log::simple_logger();
    LOG_DEBUG(log, "Opening ssp");

    auto ssp = ssp4cpp::Ssp("./tests/resources/ssp_implicit_fmi2");

    LOG_DEBUG(log, "Imported ssp! \n");
    LOG_DEBUG(log, "{}", ssp.to_string());

    LOG_DEBUG(log, "Parsing ssp to external file");
    save_string("./tests/resources/references/ssp_implicit_fmi2_ssd.txt", ssp.ssd->to_string());

    REQUIRE(ssp.fmus.size() == 6);

    for (auto &[name, fmu] : ssp.fmus)
    {
        LOG_DEBUG(log, "Resource: {}", name);

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