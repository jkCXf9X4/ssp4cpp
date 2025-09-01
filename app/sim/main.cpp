#include "common_log.hpp"
#include "simulator.hpp"

using namespace ssp4cpp;
using namespace ssp4cpp::common;

int main()
{
    auto log = Logger("main", LogLevel::debug);
    log.ext_trace("[{}] enter", __func__);

    // auto sim = Simulator("./resources/algebraic_loop_4.ssp", "./resources/model_props.json");
    // auto sim = sim::Simulator("./resources/sine_wave.ssp", "./resources/sine_wave_config.json");
    auto sim = sim::Simulator("./resources/delay_sys.ssp", "./resources/delay_sys_config.json");
    // auto sim = sim::Simulator("./resources/embrace.ssp", "./resources/generic_config.json");
    sim.init();
    sim.simulate();

    log.ext_trace("[{}] exit", __func__);
    return 0;
}
