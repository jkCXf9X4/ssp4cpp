

#pragma once

#include "common_interface.hpp"

#include <string>
#include <vector>
#include <optional>



namespace ssp4cpp::ssp1::ssd
{
    using namespace std;
    using namespace ssp4cpp::common::interfaces;
    class ComponentType : public IEnum
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
        operator Value () const {return value;}

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