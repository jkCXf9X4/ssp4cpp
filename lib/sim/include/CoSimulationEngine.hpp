#pragma once



#include "System.hpp"
#include "Scheduler.hpp"
#include "DependencyManager.hpp"
#include "ParameterManager.hpp"
#include "common_log.hpp"

namespace ssp4cpp::cosim
{

    class CoSimulationEngine
    {
    public:
        void start();
        void stop();
        void reset();
        void loadSystem(System *system);

    private:
        System *managedSystem;
        Scheduler *scheduler;
        DependencyManager *dependencyManager;
        ParameterManager *parameterManager;
        common::Logger log;
    };

}