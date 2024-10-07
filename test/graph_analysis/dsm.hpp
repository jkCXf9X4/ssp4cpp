#pragma once

#include <vector>

// #include <boost/graph/strong_components.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace ssp4cpp::dms
{
    using namespace boost;

    typedef adjacency_list<vecS, vecS, directedS, property<vertex_name_t, std::string>> Graph;

    class DSM
    {
    public:
        DSM(Graph g);
        void DSM::print(std::map<int, std::string> name_map);

    private:
        size_t N;
        std::vector<std::vector<int>> dsm_row;
        std::vector<std::vector<int>> dsm_column;
    };

}
