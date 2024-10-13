
#include "dsm.hpp"

#include <vector>
#include <iostream>
#include <numeric>
#include <ranges>

namespace ssp4cpp::dsm
{
    DSM::DSM(Graph &g) : g_ref(g)
    {
        N = num_vertices(g);
        matrix = Matrix<int>(N);
 
        // group_order
        std::map<std::string, int> comp_map;
        int group_id = 1;
        graph_traits<Graph>::edge_iterator ei, ei_end;
        for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        {
            int row = source(*ei, g); // Source vertex of the edge
            int column = target(*ei, g); // Target vertex of the edge
            matrix[row, column] = 1;      // Mark the edge in the DSM

            auto component = g[row].component;
            if(!comp_map.contains(component))
            {
                std::cout << component << " : " << group_id << std::endl;
                comp_map[component] = group_id++;
            }
            matrix.set_group(row, comp_map[component]);

        }


    }

    void DSM::PrintGroups()
    {
        auto groups = matrix.get_group_map();
        for (int i = 0; i < N; i++)
        {
            std::cout << "Row " << i << " group: " << groups[i] << std::endl;
        }
    }


    void DSM::Print()
    {

        // Display the DSM matrix
        std::cout << "Design Structure Matrix (DSM):" << std::endl;
        for (int i = 0; i < N; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j < N; j++)
                {
                    if (matrix.column_has_value(j))
                    {
                        std::cout << ";" << g_ref[j].name;
                    }
                }
                std::cout << std::endl;
            }
            if (matrix.row_has_value(i))
            {
                std::cout << g_ref[i].name;
                for (int j = 0; j < N; j++)
                {
                    if (matrix.column_has_value(j))
                    {
                        std::cout << ";" << matrix[i, j];
                    }
                }

                std::cout << std::endl;
            }
        }
    }

}