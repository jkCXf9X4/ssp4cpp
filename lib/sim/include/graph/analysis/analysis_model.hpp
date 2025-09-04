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

        std::map<std::string, AnalysisConnector *> connectors;


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

        virtual void print(std::ostream &os) const
        {
            os << "Model { \n"
               << "Name: " << name << std::endl
               << "Fmu: " << fmu_name << std::endl
               << " }" << std::endl;
        }

    };
}