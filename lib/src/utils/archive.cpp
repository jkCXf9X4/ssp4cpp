#include "ssp4cpp/utils/archive.hpp"

#include "zip.hpp"

#include <filesystem>
#include <string>

namespace ssp4cpp
{
    Archive::Archive(const std::filesystem::path &file, const std::string &tmp_prefix)
        : original_file(file)
    {

        log(trace)("[{}]Importing archive: {}", __func__, file.string());

        if (std::filesystem::exists(file))
        {
            log(trace)("[{}] File exists", __func__);
            if (is_regular_file(file))
            {
                log(trace)("[{}] Archive found, unzipping", __func__);
                dir = utils::zip_ns::unzip_to_temp_dir(file.string(), tmp_prefix);
                using_tmp_dir = true;
            }
            else if (is_directory(file))
            {
                log(trace)("[{}] Directory found", __func__);
                dir = file;
                using_tmp_dir = false;
            }
            else
            {
                throw std::runtime_error("File is not a regular file or directory: " + file.string());
            }
        }
        else
        {
            log(trace)("[{}] File does not exist", __func__);
            // try to remove the extension
            if (file.has_extension())
            {
                log(trace)("[{}] Retrying by removing extension", __func__);
                auto f = file;
                auto file_no_ext = f.replace_extension();

                if (is_regular_file(file_no_ext))
                {
                    log(trace)("[{}] Archive found, unzipping", __func__);
                    dir = utils::zip_ns::unzip_to_temp_dir(file_no_ext.string(), tmp_prefix);
                    using_tmp_dir = true;
                }
                else if (is_directory(file_no_ext))
                {
                    log(trace)("[{}] Directory found", __func__);
                    dir = file_no_ext;
                    using_tmp_dir = false;
                }
                else
                {
                    throw std::runtime_error("File is not a regular file or directory: " + file.string());
                }
            }
            else
            {
                log(trace)("[{}] File does not have extension, no more options to retry", __func__);
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
