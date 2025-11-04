#include "ssp4cpp/utils/interface.hpp"

#include <sstream>

namespace ssp4cpp::utils::interfaces
{

        IPrintable::~IPrintable() = default;

        std::string IPrintable::to_string() const
        {
            std::ostringstream oss;
            oss << *this;
            return oss.str();
        }
}
