#pragma once

#include "misc.hpp"

#include <vector>
#include <map>
#include <stdexcept>
#include <numeric>

namespace ssp4cpp::dsm
{
    template <typename T>
    class Matrix
    {
    public:
        Matrix(size_t size = 0) : N(size)
        {
            matrix = std::vector<std::vector<T>>(size, std::vector<T>(size, T()));
        }

        int &operator[](int row, int column)
        {
            return matrix[row][column];
        }

        void set_group(int row, int group)
        {
            group_map[row] = group;
        }

        // Get a list of the groups, in order
        std::vector<int> get_group_order()
        {
            auto groups = std::vector<int>();

            for (auto [key, group] : group_map)
            {
                if (misc::is_in_list(group, groups))
                {
                    groups.push_back(group);
                }
            }
            return groups;
        }

        // I iterates once 0-N
        // J itertes i times over 0-N
        template <typename Pred>
        void for_each_group_index(int group, Pred pred)
        {
            for (size_t i = 0; i < N; ++i)
            {
                if (group == -1 || group_map[i] == group)
                {
                    for (size_t j = 0; j < N; ++j)
                    {
                        pred(i, j);
                    }
                }
            }
        }

        // I iterates once 0-N
        // J itertes i times over 0-N
        template <typename Pred>
        void for_each_index(Pred pred){
            for_each_group_index(-1, pred);
        }

        // Function to get a reference to a specific row
        std::vector<T> row(size_t index)
        {
            std::vector<T> row(N);

            for_each_index([&row, this, index](int i, int j)
                           { row[i] = this->matrix[index][i]; });

            return row;
        }

        std::vector<T> &row_ref(size_t index)
        {
            return std::ref(matrix[index]);
        }

        // Function to get a specific column as a vector
        std::vector<T> column(size_t index) const
        {
            std::vector<T> column(N);
            for_each_index([&column, this, index](int i, int j)
                           { column[i] = this->matrix[i][index]; });

            return column;
        }

        Matrix<T> Transpose()
        {
            Matrix<T> mat(N);
            for_each_index([&mat, this](int i, int j)
                           { mat[i, j] = this->matrix[j][i]; });
            return mat;
        }

        T row_sum(size_t index)
        {
            auto row = this->row(index);
            return std::accumulate(row.begin(), row.end(), 0);
        }

        T column_sum(size_t index)
        {
            auto column = this->column(index);
            return std::accumulate(column.begin(), column.end(), 0);
        }

        bool row_has_value(size_t index)
        {
            return row_sum(index) != 0;
        }

        bool column_has_value(size_t index)
        {
            return row_sum(index) != 0;
        }

        Matrix<T> change_order(std::vector<int> order)
        {
            Matrix<T> mat(N);
            for (auto group : order)
            {
                for_each_group_index(group, [&mat, this](int row, int column)
                                     { mat[row, column] = matrix[row, column]; });
            }
            return mat;
        }

        std::map<int, int> get_group_map()
        {
            return group_map;
        }

    private:
        size_t N;
        std::vector<std::vector<T>> matrix;
        std::map<int, int> group_map = {};
    };
}
