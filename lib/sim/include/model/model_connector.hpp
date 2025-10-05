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

    class ConnectorInfo : public common::str::IString
    {
        public:
        common::Logger log = common::Logger("ConnectorInfo", common::LogLevel::info);

        utils::DataType type;
        size_t size;
        std::string name; // for debug

        uint32_t index;
        uint64_t value_ref;

        handler::FmuInfo *fmu;
        utils::RingStorage *storage;

        std::unique_ptr<std::byte[]> initial_value;

        bool forward_derivatives = false;
        int forward_derivatives_order = 0;

        virtual void print(std::ostream &os) const
        {
            os << "ConnectorInfo { "
               << "name: " << name
               << ", type: " << type
               << ", size: " << size
               << ", index: " << index
               << ", value_ref: " << value_ref
               << ", forward_derivatives: " << forward_derivatives_order
               << " }";
        }

    };
}
