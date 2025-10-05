#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "common_definitions.hpp"

#include "FMI2_Enums_Ext.hpp"

#include "data_ring_storage.hpp"
#include "data_recorder.hpp"
#include "invocable.hpp"
#include "config.hpp"

#include "fmu_handler.hpp"

#include <string>
#include <vector>
#include <functional>

namespace ssp4cpp::sim::graph
{
    struct ConnectionInfo : public common::str::IString
    {
        common::Logger log = common::Logger("ConnectionInfo", common::LogLevel::info);

        utils::DataType type;
        size_t size;

        utils::RingStorage *source_storage;
        utils::RingStorage *target_storage;
        uint32_t source_index;
        uint32_t target_index;

        bool forward_derivatives = false;
        int forward_derivatives_order = 0;

        virtual void print(std::ostream &os) const
        {
            os << "ConnectionInfo { "
               << "type: " << type
               << ", size: " << size
               << ", source_storage: " << source_storage
               << ", target_storage: " << target_storage
               << ", source_index: " << source_index
               << ", target_index: " << target_index
               << ", forward_derivatives: " << forward_derivatives_order
               << " }";
        }
    };
}
