

#pragma once

#include <string>
#include <vector>
#include <optional>

using namespace std;

namespace ssp4cpp::ssp1::ssd
{
    enum class ComponentType
    {
        fmu, // application/x-fmu-sharedlibrary
        ssd, // application/x-ssp-definition
        ssp, // application/x-ssp-package
    };
    string to_string(const ComponentType &obj);
    string to_string(const optional<ComponentType> &obj);
    string to_string(const vector<ComponentType> &obj);
    
    ComponentType componentType_from_string(const string &str);

}