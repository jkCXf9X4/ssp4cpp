
#include <stdexcept>

#include "SSP_Enums.hpp"
#include "to_string.tpp"

using namespace std;

namespace ssp4cpp::ssp1::ssd
{
    ComponentType from_string(const string &str)
    {
        if (str == "application/x-fmu-sharedlibrary")
        {
            return ComponentType::fmu;
        }
        else if (str == "application/x-ssp-definition")
        {
            return ComponentType::ssd;
        }
        else if (str == "application/x-ssp-package")
        {
            return ComponentType::ssp;
        }
        throw invalid_argument("Unknown ComponentType: " + str);
    }

    string to_string(const ComponentType &obj)
    {
        switch (obj)
        {
        case ComponentType::fmu:
            return "application/x-fmu-sharedlibrary";
        case ComponentType::ssd:
            return "application/x-ssp-definition";
        case ComponentType::ssp:
            return "application/x-ssp-package";
        default:
            return "unknown";
        }
    }
    string to_string(const optional<ComponentType> &obj) { return to_string_optional(obj); }
    string to_string(const vector<ComponentType> &obj) { return to_string_vector(obj); }

}