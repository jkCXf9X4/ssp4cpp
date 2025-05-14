#pragma once

#include <list>
namespace ssp4cpp::cosim
{
    class DependencyManager {
        public:
        void analyzeDependencies();
        std::list<int> getExecutionOrder();
    };
    
}
