#ifndef PARAMETERMANAGER_HPP
#define PARAMETERMANAGER_HPP

#include <string>

class ParameterManager {
public:
    void setParameter(const std::string& name, const void* value);
    void* getParameter(const std::string& name);
};

#endif // PARAMETERMANAGER_HPP