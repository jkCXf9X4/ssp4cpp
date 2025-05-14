#pragma once

#include "Model.hpp"
#include "ParameterManager.hpp"
namespace ssp4cpp::cosim
{
    class System
    {

    public:
        void loadSystem();
        void unloadSystem();

    private:
        Model *managedModel;
        ParameterManager *parameterManager;
    };

}