#pragma once

#include <vector>

// #include <boost/graph/strong_components.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace ssp4cpp::dsm
{
    using namespace boost;

    struct vertex_info
    {
        std::string name_;
        std::string component;
        std::string connector;
        int index;
    };

    typedef adjacency_list<vecS, vecS, boost::directedS, vertex_info> Graph;

    class DSM
    {
    public:
        DSM(Graph &g);
        void Print();

    private:

        Graph& g_ref;
        size_t N;
        std::vector<std::vector<int>> dsm_row;
        std::vector<std::vector<int>> dsm_column;
    };

}
