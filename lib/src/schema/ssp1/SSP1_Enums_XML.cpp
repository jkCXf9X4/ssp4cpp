

// This is a generated file, do not alter
// it is based on ssp1_enums.toml

#include "SSP1_Enums_XML.hpp"


#include "xml_deserialize.hpp"

#include "ssp4cpp/utils/log.hpp"

namespace ssp4cpp::ssp1::ssd
{
    using namespace pugi;

    quill::Logger* log()
    {
        // Cache this logger locally so we avoid eager header initialization.
        static quill::Logger* logger =
            ssp4cpp::utils::log::make_logger("ssp4cpp.ssp1.ssd", quill::LogLevel::TraceL1);
        return logger;
    }


}
