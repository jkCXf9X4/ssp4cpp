#pragma once
#include "common_log.hpp"

#include <filesystem>
#include <string>

using namespace std;
using namespace std::filesystem;

namespace ssp4cpp
{
    using namespace common;

    /**
     * @brief Base class for archives extracted to a temporary directory.
     */
    class Archive
    {
    public:
        Logger log = Logger("Archive", LogLevel::info);
        bool using_tmp_dir = false;
        path original_file;
        path dir;

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
        Archive(const path &file, const std::string &tmp_prefix);

        /** @brief Clean up any temporary directory used by the archive. */
        virtual ~Archive();
    };
}
