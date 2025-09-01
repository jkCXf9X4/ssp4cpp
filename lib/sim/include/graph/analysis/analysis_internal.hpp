#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "common_log.hpp"

#include "analysis_connector.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::sim::analysis::graph
{
    // intra model connections
    class AnalysisModelVariable : public ssp4cpp::common::graph::Node
    {
        uint64_t delay = 0;

    public:
        common::Logger log = common::Logger("AnalysisModelVariable", common::LogLevel::debug);
        string component;
        string variable_name;

        AnalysisModelVariable() {}

        AnalysisModelVariable(string component, string variable_name)
        {
            this->component = component;
            this->variable_name = variable_name;
            update_name();
        }

        ~AnalysisModelVariable()
        {
            log.ext_trace("[{}] Destroying AnalysisModelVariable", __func__);
        }

        void update_name()
        {
            this->name = AnalysisConnector::create_name(component, variable_name);
        }

        std::string get_connector_name()
        {
            return AnalysisConnector::create_name(component, variable_name);
        }

        friend ostream &operator<<(ostream &os, const AnalysisModelVariable &obj)
        {
            os << "AnalysisModelVariable { \n"
               << "name: " << obj.name << endl
               << "component: " << obj.component << endl
               << "variable_name: " << obj.variable_name << endl
               << " }" << endl;

            return os;
        }
    };

}