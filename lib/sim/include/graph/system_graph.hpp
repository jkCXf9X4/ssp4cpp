#include "common_list.hpp"

#include "connection.hpp"
#include "ssp_ext.hpp"
#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::graph
{
    using namespace std;

    inline auto log = common::Logger("sim::graph", common::LogLevel::debug);

    vector<common::graph::Node*> create_system_graph(Ssp &ssp)
    {
        auto fmus = ssp4cpp::ssp::ext::create_fmu_map(ssp);

        map<string, common::graph::Node*> models;
        for (auto &[str, fmu] : fmus)
        {
            // ownership of fmu should be decided
            models[str] = new Model(str, &fmu);
        }

        auto fmu_connections = ssp1::ext::elements::get_fmu_connections(ssp.ssd);
        for (auto &[source, target] : fmu_connections)
        {
            log.debug("Connection: {} -> {}", source, target);
            models[source]->add_child(models[target]);
        }

        return ssp4cpp::common::list::map_to_value_vector(models);

    }
}