#include "ssp4cpp/utils/archive.hpp"

#include "zip.hpp"

#include <filesystem>
#include <string>

namespace ssp4cpp
{

    Archive::Archive(const std::filesystem::path &file, const std::string &tmp_prefix)
        : original_file(file)
    {

        log(debug)("Importing file: {}", file.string());

        if (is_regular_file(file))
        {
            log(debug)("Opening archive: {}", file.string());
            dir = utils::zip_ns::unzip_to_temp_dir(file.string(), tmp_prefix);
            using_tmp_dir = true;
        }
        else if (is_directory(file))
        {
            log(debug)("Opening directory: {}", file.string());

            dir = file;
            using_tmp_dir = false;
        }
        else
        {
            // Trying to strip the extension and open again.
            auto f = file;
            auto wo_ext = f.replace_extension();
            if (is_directory(wo_ext))
            {
                log(debug)("Opening stripped directory: {}", f.string());
                dir = wo_ext;
                using_tmp_dir = false;
            }
            else
            {
                throw std::runtime_error("File is not a regular file or directory: " + file.string());
            }

        }
    }

    /** @brief Clean up any temporary directory used by the archive. */
    Archive::~Archive()
    {
        log(ext_trace)("Destructor called for archive {}", original_file.string());
        if (using_tmp_dir)
        {
            remove_all(dir);
        }
    }
}
