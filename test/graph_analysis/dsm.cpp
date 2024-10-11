
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
 

        graph_traits<Graph>::edge_iterator ei, ei_end;
        for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        {
            int u = source(*ei, g); // Source vertex of the edge
            int v = target(*ei, g); // Target vertex of the edge
            matrix[u, v] = 1;      // Mark the edge in the DSM
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