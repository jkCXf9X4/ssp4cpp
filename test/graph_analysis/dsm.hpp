#pragma once

#include "matrix.hpp"

#include <vector>
#include <map>

// #include <boost/graph/strong_components.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

// design structure matrix
namespace ssp4cpp::dsm
{
    using namespace boost;

    struct vertex_info
    {
        std::string name;
        std::string component;
        std::string connector;
        int index;
    };

    typedef adjacency_list<vecS, vecS, boost::directedS, vertex_info, vertex_info> Graph;

    class DSM
    {
    public:
        DSM(Graph &g);
        std::string GetCSV();
        void PrintGroups();

    private:
        Graph &g_ref;
        size_t N;

        std::vector<int> group_order;

        Matrix<int> matrix;
    };
}
