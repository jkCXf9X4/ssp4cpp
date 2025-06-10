#pragma once

#include "node_base.hpp"

#include <vector>
#include <map>
#include <algorithm>

namespace ssp4cpp::sim::graph
{

    // split the graph in delay-vice equal parts
    // used in pure serial nodes
    // a -> b -> c -> d-> e...
    static auto split_delay(SimNode *n, size_t nr_parts)
    {
        vector<vector<SimNode*>> result;

        // calculate the total delay

        // traverse from the begining until delay/nr_parts is ~ equal

        // repeat for nr_parts

        // after initial split, finetune where the splits are positioned

        return result;
    }




}
