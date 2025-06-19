#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "node_base.hpp"
#include "node_connector.hpp"

#include "fmu_handler.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::utils
{
    // data centric storage
    template<typename T>
    class DataStorage
    {
    public:
        common::Logger log = common::Logger("Data", common::LogLevel::ext_trace);

        uint64_t time;
        vector<std::string> names;
        vector<int> sizes;
        map<std::string, int> index_name_map;
        
        // the data landing area enables easy access when exporting results
        unique_ptr<std::byte[]> data;
        vector<int> positions;    // data position relative to landing area 0, 4,...
        
        vector<void *> locations; // absolute location in memory
        vector<handler::DataType> types;

        int pos = 0;
        int index = 0;

        DataStorage() {}

        void add(T &item)
        {
            names.push_back(item.name);
            positions.push_back(pos);
            types.push_back(item.type)
            sizes.push_back(handler::get_data_type_size(item.type));
            
            index_name_map[item.name] = index;

            pos += sizes.back();
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
            data = std::make_unique<std::byte[]>(pos);
    
            for (auto pos : positions)
            {
                locations.push_back(data.get() + pos);
            }
        }

        vector<std::string> get_names()
        {
            return names;
        }

        auto get_data()
        {
            vector<pair<handler::DataType, void*>> output;
            int i = 0;
            for (auto &location :locations)
            {
                output.push_back(make_pair(types[i], location));
            }
            return output;
        }


    };   
}