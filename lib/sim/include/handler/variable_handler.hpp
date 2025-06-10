#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "variable.hpp"

#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::handler
{
    using namespace std;
    class VariableHandler
    {
        common::Logger log = common::Logger("sim::VariableHandler", common::LogLevel::ext_trace);

        VariableHandler(){}
        
        vector<VariableBase> variables;

        // using Job = std::function<void()>;
        // std::vector<Job> items;

        // A<int>         i{5};
        // A<std::string> s{"hello"};

        // items.emplace_back([i]{ i.print(); }); // copies i into lambda
        // items.emplace_back([s]{ s.print(); });

        // for (auto& job : items) job();         // just run the stored callable
    };

}