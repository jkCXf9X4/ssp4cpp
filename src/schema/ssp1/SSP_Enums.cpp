
#include <stdexcept>

#include "SSP_Enums.hpp"
#include "to_string.hpp"

using namespace std;

// namespace ssp4cpp::ssp1::ssd
// {
//     ComponentType componentType_from_string(const string &str)
//     {
//         if (str == "application/x-fmu-sharedlibrary")
//         {
//             return ComponentType::fmu;
//         }
//         else if (str == "application/x-ssp-definition")
//         {
//             return ComponentType::ssd;
//         }
//         else if (str == "application/x-ssp-package")
//         {
//             return ComponentType::ssp;
//         }
//         throw invalid_argument("Unknown ComponentType: " + str);
//     }

//     string to_string(const ComponentType &obj)
//     {
//         switch (obj)
//         {
//         case ComponentType::fmu:
//             return "application/x-fmu-sharedlibrary";
//         case ComponentType::ssd:
//             return "application/x-ssp-definition";
//         case ComponentType::ssp:
//             return "application/x-ssp-package";
//         default:
//             return "unknown";
//         }
//     }

// }