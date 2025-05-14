#pragma once

#include "ModelExecutor.hpp"
#include "DataManager.hpp"

namespace ssp4cpp::cosim
{

    class Scheduler
    {
    public:
        void step();

    private:
        ModelExecutor *modelExecutor;
        DataManager *dataManager;
    };

}