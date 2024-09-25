

#pragma once

#include <string>
#include <vector>
#include <optional>

#include "IXmlNode.hpp"

using namespace std;
using namespace ssp4cpp::interfaces;

namespace ssp4cpp::ssp1::ssd
{
    class ComponentType : public IReadWrite
    {
    public:
        enum Value :int
        {
            fmu, // application/x-fmu-sharedlibrary
            ssd, // application/x-ssp-definition
            ssp, // application/x-ssp-package
        };

        ComponentType() = default;
        constexpr ComponentType(Value value) : value(value) {}

        string to_string() const override
        {
            switch (value)
            {
            case Value::fmu:
                return "application/x-fmu-sharedlibrary";
            case Value::ssd:
                return "application/x-ssp-definition";
            case Value::ssp:
                return "application/x-ssp-package";
            default:
                return "unknown";
            }
        }

        void from_string(const string &str) override
        {
            if (str == "application/x-fmu-sharedlibrary")
            {
                value = Value::fmu;
            }
            else if (str == "application/x-ssp-definition")
            {
                value = Value::ssd;
            }
            else if (str == "application/x-ssp-package")
            {
                value = Value::ssp;
            }
            else
            {
                value = Value::fmu;
            }
        }

    private:
        Value value;
    };

}