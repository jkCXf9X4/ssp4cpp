#pragma once

#include <string>
namespace ssp4cpp::cosim
{
    
    class ParameterManager {
        public:
        void setParameter(const std::string& name, const void* value);
        void* getParameter(const std::string& name);
    };
    
}