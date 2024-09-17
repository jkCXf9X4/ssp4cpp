

#pragma once

#include <string>

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
    ComponentType from_string(const string &str);

}