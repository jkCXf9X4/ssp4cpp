#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "node_base.hpp"
#include "node_connector.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{

    class Model : public NodeBase
    {
    public:
        string fmu_name;

        map<string, Connector *> input_connector;
        map<string, Connector *> output_connector;

        Model() {}

        Model(std::string name, std::string fmu_name)
        {
            this->name = name;
            this->fmu_name = fmu_name;
        }

        friend ostream &operator<<(ostream &os, const Model &obj)
        {
            os << "Model { \n"
               << "Name: " << obj.name << endl
               << "Fmu: " << obj.fmu_name << endl
               << " }" << endl;

            return os;
        }
    };


    // public:
    //     uint64_t start_time = 0;
    //     uint64_t end_time = 0;
    //     uint64_t delayed_time = 0;
    //     uint64_t delay = 0;

    //     bool is_init = false;

    //     fmi4cpp::fmi2::cs_slave *model;

    //     common::Logger log = common::Logger("sim_graph::Model", common::LogLevel::ext_trace);

    //     Model() : Node() {}

    //     Model(const std::string &name, fmi4cpp::fmi2::cs_slave *model) : ssp4cpp::common::graph::Node(name)
    //     {
    //         this->model = model;
    //     }

    //     void add_incoming_connection()
    //     {
    //         //TODO
    //     }

    //     uint64_t invoke(uint64_t timestep)
    //     {
    //         fetch_incoming_data();

    //         auto out_time = take_step(timestep);

    //         store_result();
    //     }

    //     void fetch_incoming_data()
    //     {
    //         //TODO
    //     }

    //     void store_result()
    //     {
    //         //TODO
    //     }

    //     uint64_t take_step(uint64_t timestep)
    //     {
    //         // calculate step times
    //         start_time = end_time;
    //         end_time = start_time + timestep;
    //         delayed_time = end_time - delay;
    //         log.trace("[{}] SimNode start_time: {} end_time: {}, delayed_time {}", __func__, start_time, end_time, delayed_time);

    //         // take step
    //         auto step_double = (double)timestep / ssp4cpp::common::time::nanoseconds_per_second;
    //         log.trace("[{}] Model {} ", __func__, step_double);
    //         if (model->step(step_double) == false)
    //         {
    //             log.error("Error! step() returned with status: {}", std::to_string((int)model->last_status()));
    //         }

    //         return delayed_time;
    //     }

}