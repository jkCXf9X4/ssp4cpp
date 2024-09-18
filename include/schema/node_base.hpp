#pragma once

#include <string>

using namespace std;

namespace ssp4cpp
{
    class IToStr
    {
    public:
        virtual string to_string() = 0;
    };
}