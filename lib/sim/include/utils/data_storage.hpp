#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "node_base.hpp"
#include "node_connector.hpp"
#include "data_type.hpp"

#include "fmu_handler.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::utils
{
    // data centric storage
    template <typename T>
    class DataStorage
    {
        common::Logger log = common::Logger("Data", common::LogLevel::ext_trace);

        map<std::string, int> index_name_map;

        // the data landing area enables easy access when exporting results
        unique_ptr<std::byte[]> data;
        vector<int> positions;    // data position relative to start, 0, 4,...
        vector<void *> locations; // absolute location in memory
        vector<utils::DataType> types;

    public:
        uint64_t time;
        vector<std::string> names;
        vector<pair<utils::DataType, void *>> type_data;

        int pos = 0;
        int index = 0;

        DataStorage() {}

        void add(T &item)
        {
            names.push_back(item.name);
            positions.push_back(pos);
            types.push_back(item.type);

            index_name_map[item.name] = index;

            pos += utils::get_data_type_size(item.type);
            index += 1;
        }

        void add(vector<T> &items)
        {
            for (auto &item : items)
            {
                add(item);
            }
        }

        void allocate()
        {
            locations.clear();
            data = std::make_unique<std::byte[]>(pos);

            for (auto p : positions)
            {
                locations.push_back(data.get() + p);
            }

            int i = 0;
            for (auto &l : locations)
            {
                type_data.push_back(make_pair(types[i], l));
                i += 1;
            }
        }

        int index_by_name(std::string name)
        {
            return index_name_map[name];
        }
    };
}