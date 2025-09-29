#include "handler/fmi4c_adapter.hpp"

#include <catch.hpp>

#include <cmath>
#include <filesystem>
#include <string>

using namespace ssp4cpp::sim::handler;

namespace
{
    std::filesystem::path repository_root()
    {
        auto root = std::filesystem::path(SSP4CPP_PROJECT_ROOT);
        return root;
    }

    std::filesystem::path scenario_fmu_path()
    {
        auto path = repository_root() / "resources" / "scenario" / "scenario.fmu";
        REQUIRE(std::filesystem::exists(path));
        return path;
    }

    std::filesystem::path atmos_fmu_path()
    {
        auto path = repository_root() / "resources" / "embrace" / "atmos" / "0004_Atmos.fmu";
        REQUIRE(std::filesystem::exists(path));
        return path;
    }
}

TEST_CASE("detail message utilities capture the last message", "[fmi4c_adapter]")
{
    detail::clear_last_message();
    detail::fmi4c_message_callback("test message");
    auto message = detail::consume_last_message();
    REQUIRE(message == "test message");
    REQUIRE(detail::consume_last_message().empty());
}

TEST_CASE("FmuInstance loads FMI 2.0 co-simulation FMUs", "[fmi4c_adapter]")
{
    auto fmu_path = scenario_fmu_path();

    FmuInstance instance(fmu_path, "catch-instance");

    REQUIRE(std::filesystem::path(instance.path()) == fmu_path);
    REQUIRE(instance.instance_name() == "catch-instance");
    REQUIRE(instance.version() == fmiVersion2);
    REQUIRE(instance.supports_co_simulation());
}

TEST_CASE("FmuInstance surfaces load failures", "[fmi4c_adapter]")
{
    auto invalid_path = repository_root() / "resources" / "scenario" / "missing.fmu";
    REQUIRE_FALSE(std::filesystem::exists(invalid_path));

    try
    {
        FmuInstance instance(invalid_path, "missing");
        (void)instance;
        FAIL("Expected FMU load failure");
    }
    catch (const std::runtime_error &ex)
    {
        REQUIRE(std::string(ex.what()).find("Failed to load FMU") != std::string::npos);
    }
}

TEST_CASE("CoSimulationModel enforces call order", "[fmi4c_adapter]")
{
    auto fmu_path = scenario_fmu_path();
    FmuInstance instance(fmu_path, "call-order-instance");
    CoSimulationModel model(instance);

    REQUIRE_THROWS_AS(model.setup_experiment(0.0, 1.0, 0.0), std::logic_error);
    REQUIRE_THROWS_AS(model.enter_initialization_mode(), std::logic_error);
    REQUIRE_THROWS_AS(model.exit_initialization_mode(), std::logic_error);
    REQUIRE_THROWS_AS(model.step(0.1), std::logic_error);
}

TEST_CASE("CoSimulationModel runs scenario FMU lifecycle", "[fmi4c_adapter][integration]")
{
    auto fmu_path = scenario_fmu_path();
    FmuInstance instance(fmu_path, "lifecycle-instance");
    CoSimulationModel model(instance);

    REQUIRE(model.instantiate(false, false));
    REQUIRE(model.instantiate(false, false));

    REQUIRE(model.setup_experiment(0.0, 10.0, 1e-4));
    REQUIRE(model.get_simulation_time() == Catch::Approx(0.0));

    REQUIRE(model.enter_initialization_mode());
    auto scenario_schedule = std::string("Alt;L;0.0,0.0;300.0,10000.0\nMach;L;0.0,0.0;300.0,1.2\nheat_load;ZOH;0.0,50.0;150.0,4000.0\nWgt_On_Whl;ZOH;0.0,1.0;150.0,0.0\nAircraft_state;ZOH;0.0,0.0;150.0,4.0");
    REQUIRE(model.write_string(0, scenario_schedule));
    REQUIRE(model.exit_initialization_mode());

    REQUIRE(model.step(0.5));
    REQUIRE(model.last_status() == fmi2OK);
    REQUIRE(model.get_simulation_time() == Catch::Approx(0.5));

    double altitude = 0.0;
    REQUIRE(model.read_real(1, altitude));
    REQUIRE(std::isfinite(altitude));

    REQUIRE(model.terminate());
    REQUIRE(model.terminate());
}

double kxm(double k, double x, double m)
{
    return k * x + m;
}

TEST_CASE("Atmos FMU computes ambient properties based on inputs", "[fmi4c_adapter][integration]")
{
    constexpr uint64_t kTambVr = 335544320;
    constexpr uint64_t kPambVr = 335544321;
    constexpr uint64_t kAltVr = 352321536;
    constexpr uint64_t kMachVr = 352321537;
    constexpr uint64_t kDtisaVr = 16777216;
    constexpr uint64_t kEventCounterVr = 67108867;

    auto fmu_path = atmos_fmu_path();
    FmuInstance instance(fmu_path, "atmos-instance");
    CoSimulationModel model(instance);

    REQUIRE(model.instantiate(false, false));
    REQUIRE(model.setup_experiment(0.0, 1.0, 1e-4));
    REQUIRE(model.enter_initialization_mode());

    REQUIRE(model.write_real(kDtisaVr, 0.0));
    REQUIRE(model.write_real(kAltVr, 0.0));
    REQUIRE(model.write_real(kMachVr, 0.0));

    REQUIRE(model.exit_initialization_mode());

    REQUIRE(model.step(0.1));
    REQUIRE(model.get_simulation_time() == Catch::Approx(0.1));

    double sea_level_temp = 0.0;
    double sea_level_pressure = 0.0;
    REQUIRE(model.read_real(kTambVr, sea_level_temp));
    REQUIRE(model.read_real(kPambVr, sea_level_pressure));
    REQUIRE(std::isfinite(sea_level_temp));
    REQUIRE(std::isfinite(sea_level_pressure));

    REQUIRE(model.write_real(kAltVr, 10000.0));
    REQUIRE(model.write_real(kMachVr, 0.8));
    bool input_derivative_supported = model.set_real_input_derivative(kAltVr, 1, -5.0);
    bool input_status_ok = model.last_status() == fmi2OK || model.last_status() == fmi2Warning;
    if (input_derivative_supported)
    {
        REQUIRE(input_status_ok);
    }
    else
    {
        REQUIRE_FALSE(input_status_ok);
    }

    REQUIRE(model.step(0.1));

    double high_alt_temp = 0.0;
    double high_alt_pressure = 0.0;
    REQUIRE(model.read_real(kTambVr, high_alt_temp));
    REQUIRE(model.read_real(kPambVr, high_alt_pressure));

    REQUIRE(high_alt_temp < sea_level_temp);
    REQUIRE(high_alt_pressure < sea_level_pressure);

    double temperature_derivative = 0.0;
    bool output_derivative_supported = model.get_real_output_derivative(kTambVr, 1, temperature_derivative);
    bool output_status_ok = model.last_status() == fmi2OK || model.last_status() == fmi2Warning;
    if (output_derivative_supported)
    {
        REQUIRE(output_status_ok);
        REQUIRE(std::isfinite(temperature_derivative));
    }
    else
    {
        REQUIRE_FALSE(output_status_ok);
    }

    REQUIRE(model.terminate());
}

TEST_CASE("Atmos FMU reports solver events via EventCounter", "[fmi4c_adapter][fmi4c_atmos]")
{
    constexpr uint64_t kAltVr = 352321536;
    constexpr uint64_t kMachVr = 352321537;
    constexpr uint64_t kDtisaVr = 16777216;
    constexpr uint64_t kEventCounterVr = 67108867;

    double altitude_derivative = 10;
    double mach_derivative = 0.1;

    double step = 0.01;
    double total_time = 10;
    double Dtisa = 0;

    auto fmu_path = atmos_fmu_path();
    FmuInstance instance(fmu_path, "atmos-events-instance");
    CoSimulationModel model(instance);

    REQUIRE(model.instantiate(true, false));
    
    REQUIRE(model.setup_experiment(0.0, 0.0, 1e-4));


    REQUIRE(model.enter_initialization_mode());
    
    REQUIRE(model.write_real(kDtisaVr, 0.0));
    REQUIRE(model.write_real(kAltVr, 0.0));
    REQUIRE(model.write_real(kMachVr, 0.0));
    
    REQUIRE(model.exit_initialization_mode());

    double event_counter = 0.0;
    REQUIRE(model.read_real(kEventCounterVr, event_counter));
    INFO("Initial EventCounter: " << event_counter);

    REQUIRE(std::isfinite(event_counter));
    REQUIRE(event_counter >= 0.0);

    const double initial_counter = event_counter;

    // model.step(step);

    uint64_t index = 0;
    for (double time = 0; time < total_time;)
    {
        index++;
        time = model.get_simulation_time();
        double new_altitude = altitude_derivative * time;
        double new_mach = mach_derivative * time;

        // std::cout <<"new_altitude: " << new_altitude <<" new_mach: " << new_mach << std::endl;
        model.write_real(kAltVr, new_altitude);
        model.write_real(kMachVr, new_mach);
        model.write_real(kDtisaVr, 0.0);

        // model.read_real(kAltVr, new_altitude);
        // model.read_real(kMachVr, new_mach);
        // model.read_real(kDtisaVr, Dtisa);

        bool derivative_supported;
        derivative_supported = model.set_real_input_derivative(kAltVr, 1, altitude_derivative+0.000000000000001);
        derivative_supported = model.set_real_input_derivative(kMachVr, 1, mach_derivative);

        // unsigned int vrs[] = {kAltVr, kAltVr};
        // int orders[] = {0, 1};
        // double values[] = {new_altitude, altitude_derivative};
        // fmi2_setRealInputDerivatives(model.handle, vrs, 2, orders, values);

        // unsigned int vrs_m[] = {kMachVr, kMachVr};
        // int orders_m[] = {0, 1};
        // double values_m[] = {new_mach, mach_derivative};
        // fmi2_setRealInputDerivatives(model.handle, vrs_m, 2, orders_m, values_m);
        // if (time > 0.1)
        // {

        //     derivative_supported = model.set_real_input_derivative(kAltVr, 2, 0.0);
        //     derivative_supported = model.set_real_input_derivative(kMachVr, 2, 0.0);
        // }

        INFO("setRealInputDerivatives supported: " << derivative_supported);

        bool derivative_status_ok = model.last_status() == fmi2OK || model.last_status() == fmi2Warning;
        INFO("derivative_status_ok: " << derivative_status_ok);

        model.step(step);

        double current_counter = 0.0;
        INFO("Read real ");
        model.read_real(kEventCounterVr, current_counter);
        INFO("EventCounter after time " << time << ": " << current_counter);
        std::isfinite(current_counter);
        current_counter >= event_counter;
        event_counter = current_counter;
    }

    INFO("event_counter: " << event_counter);

    REQUIRE(event_counter > initial_counter);
    REQUIRE(model.terminate());
    REQUIRE(false);
}
