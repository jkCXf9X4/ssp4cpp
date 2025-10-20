#pragma once
#include "utils/log.hpp"
#include "utils/string.hpp"

#include <filesystem>
#include <string>


namespace ssp4cpp
{

    /**
     * @brief Base class for archives extracted to a temporary directory.
     */
    class Archive : public utils::str::IString
    {
    public:
        utils::Logger log = utils::Logger("ssp4cpp.Archive", utils::LogLevel::info);
        bool using_tmp_dir = false;
        std::filesystem::path original_file;
        std::filesystem::path dir;

        // Makes no sense to have a archive not associated with a file 
        Archive() = delete;

        // No move or copy to avoid ownership issues to files
        Archive(const Archive &) = delete;
        Archive(Archive &&other) = delete;
        Archive &operator=(const Archive &) = delete;
        Archive &operator=(Archive &&other) = delete;

        /**
         * @brief Extract a file or directory to a working location.
         */
        Archive(const std::filesystem::path &file, const std::string &tmp_prefix);

        /** @brief Clean up any temporary directory used by the archive. */
        virtual ~Archive();
    };
}
