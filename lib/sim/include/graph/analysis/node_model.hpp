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

namespace ssp4cpp::sim::analysis::graph
{

    class ModelNode : public NodeBase
    {
    public:
        common::Logger log = common::Logger("ModelNode", common::LogLevel::info);

        string fmu_name;

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