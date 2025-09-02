#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "analysis_connector.hpp"

#include <string>
#include <vector>
#include <map>

namespace ssp4cpp::sim::analysis::graph
{

    class AnalysisModel : public ssp4cpp::common::graph::Node
    {
        uint64_t delay = 0;

    public:
        common::Logger log = common::Logger("AnalysisModel", common::LogLevel::info);

        std::string fmu_name;
        handler::FmuInfo *fmu;

        std::map<std::string, AnalysisConnector *> input_connectors;
        std::map<std::string, AnalysisConnector *> output_connectors;
        std::map<std::string, AnalysisConnector *> parameters;

        AnalysisModel() {}

        AnalysisModel(std::string name, std::string fmu_name, handler::FmuInfo *fmu)
        {
            this->fmu = fmu;
            this->name = name;
            this->fmu_name = fmu_name;
        }

        ~AnalysisModel()
        {
            log.ext_trace("[{}] Destroying AnalysisModel", __func__);
        }

        friend std::ostream &operator<<(std::ostream &os, const AnalysisModel &obj)
        {
            os << "Model { \n"
               << "Name: " << obj.name << std::endl
               << "Fmu: " << obj.fmu_name << std::endl
               << " }" << std::endl;

            return os;
        }

    };
}