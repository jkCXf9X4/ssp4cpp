#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "node_connector.hpp"

#include <string>
#include <vector>
#include <map>

namespace ssp4cpp::sim::analysis::graph
{

    class ModelNode : public ssp4cpp::common::graph::Node
    {
        uint64_t delay = 0;

    public:
        common::Logger log = common::Logger("ModelNode", common::LogLevel::info);

        string fmu_name;
        handler::FmuInfo *fmu;

        map<string, ConnectorNode *> input_connectors;
        map<string, ConnectorNode *> output_connectors;

        ModelNode() {}

        ModelNode(std::string name, std::string fmu_name, handler::FmuInfo *fmu)
        {
            this->fmu = fmu;
            this->name = name;
            this->fmu_name = fmu_name;
        }

        ~ModelNode()
        {
            log.ext_trace("[{}] Destroying ModelNode", __func__);
        }

        friend ostream &operator<<(ostream &os, const ModelNode &obj)
        {
            os << "Model { \n"
               << "Name: " << obj.name << endl
               << "Fmu: " << obj.fmu_name << endl
               << " }" << endl;

            return os;
        }
    };
}