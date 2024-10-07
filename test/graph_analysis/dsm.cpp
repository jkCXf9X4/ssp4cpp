
#include "dsm.hpp"

#include <vector>
#include <iostream>

namespace ssp4cpp::dms
{
    DSM::DSM(Graph g)
    {
        N = num_vertices(g);
        dsm_row = std::vector(N, std::vector<int>(N, 0));
        dsm_column = std::vector(N, std::vector<int>(N, 0));

        graph_traits<Graph>::edge_iterator ei, ei_end;
        for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        {
            int u = source(*ei, g); // Source vertex of the edge
            int v = target(*ei, g); // Target vertex of the edge
            dsm_row[u][v] = 1;      // Mark the edge in the DSM
            dsm_column[v][u] = 1;   // Mark the edge in the DSM
        }
    }

    void DSM::print(std::map<int, std::string> name_map)
    {
        // Display the DSM matrix
        std::cout << "Design Structure Matrix (DSM):" << std::endl;
        for (int i = 0; i < N; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j < N; j++)
                {
                    std::cout << ";" << name_map[j];
                }
                std::cout << std::endl;
            }

            std::cout << name_map[i];
            for (int j = 0; j < N; j++)
            {
                std::cout << ";" << dsm_row[i][j];
            }

            std::cout << std::endl;
        }
    }

}