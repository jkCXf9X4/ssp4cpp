#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Model.hpp"
#include "ParameterManager.hpp"

class System {
public:
    void loadSystem();
    void unloadSystem();
    
private:
    Model* managedModel;
    ParameterManager* parameterManager;
};

#endif // SYSTEM_HPP