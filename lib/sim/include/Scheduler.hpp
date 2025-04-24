#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "ModelExecutor.hpp"
#include "DataManager.hpp"

class Scheduler {
public:
    void step();
    
private:
    ModelExecutor* modelExecutor;
    DataManager* dataManager;
};

#endif // SCHEDULER_HPP