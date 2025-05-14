#pragma once

#include <list>

namespace ssp4cpp::cosim
{

    class TarjansStrongly
    {
    public:
        std::list<int> getStronglyConnectedComponents();
    };

}