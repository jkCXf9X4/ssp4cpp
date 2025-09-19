#include "common_log.hpp"
#include "simulator.hpp"

using namespace ssp4cpp;

int main()
{
    auto log = common::Logger("main", common::LogLevel::debug);
    log.ext_trace("[{}] enter", __func__);

    // auto sim = Simulator("./resources/algebraic_loop/algebraic_loop_4.ssp", "./resources/model_props.json");
    // auto sim = sim::Simulator("./resources/sine_wave.ssp", "./resources/sine_wave_config.json");
    // auto sim = sim::Simulator("./resources/delay_sys/delay_sys.ssp", "./resources/delay_sys/delay_sys_config.json");
    // auto sim = sim::Simulator("./resources/embrace/embrace.ssp", "./resources/generic_config.json");
    auto sim = sim::Simulator("./resources/scenario/scenario.ssp", "./resources/generic_config.json");
    sim.init();
    sim.simulate();

    log.ext_trace("[{}] exit", __func__);
    return 0;
}
