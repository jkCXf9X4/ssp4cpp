

// This is a generated file, do not alter
// it is based on fmi2_enums.toml

#include "FMI2_Enums_XML.hpp"


#include "xml_deserialize.hpp"

#include "ssp4cpp/utils/log.hpp"

namespace ssp4cpp::fmi2::md
{
    using namespace pugi;

    quill::Logger* log()
    {
        // Cache this logger locally so we avoid eager header initialization.
        static quill::Logger* logger =
            ssp4cpp::utils::log::make_logger("ssp4cpp.fmi2.md", quill::LogLevel::TraceL1);
        return logger;
    }


}
