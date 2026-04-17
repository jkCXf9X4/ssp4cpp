

// This is a generated file, do not alter
// it is based on ssp1_enums.toml

#include "SSP1_Enums_XML.hpp"


#include "xml_deserialize.hpp"

#include "ssp4cpp/utils/log.hpp"

namespace ssp4cpp::ssp1::ssd
{
    using namespace pugi;

    ssp4cpp::utils::log::Logger* log()
    {
        // Cache this logger locally so we avoid eager header initialization.
        static ssp4cpp::utils::log::Logger* logger =
            ssp4cpp::utils::log::make_logger("ssp4cpp.ssp1.ssd");
        return logger;
    }


}
