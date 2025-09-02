#include "archive.hpp"

#include "zip.hpp"

#include <filesystem>
#include <string>

namespace ssp4cpp
{

    Archive::Archive(const std::filesystem::path &file, const std::string &tmp_prefix)
        : original_file(file)
    {

        log.debug("Importing archive: {}", file.string());

        if (is_regular_file(file))
        {
            dir = common::zip_ns::unzip_to_temp_dir(file.string(), tmp_prefix);
            using_tmp_dir = true;
        }
        else if (is_directory(file))
        {
            dir = file;
            using_tmp_dir = false;
        }
        else
        {
            throw std::runtime_error("File is not a regular file or directory: " + file.string());
        }
    }

    /** @brief Clean up any temporary directory used by the archive. */
    Archive::~Archive()
    {
        log.ext_trace("Destructor called for archive {}", original_file.string());
        if (using_tmp_dir)
        {
            remove_all(dir);
        }
    }
}
