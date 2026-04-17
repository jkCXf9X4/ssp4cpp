#include "ssp4cpp/utils/archive.hpp"

#include "ssp4cpp/utils/log.hpp"

#include "zip.hpp"

#include <filesystem>
#include <string>

namespace ssp4cpp
{

    Archive::Archive(const std::filesystem::path &file, const std::string &tmp_prefix)
        : original_file(file)
    {
        log = ssp4cpp::utils::log::make_logger("ssp4cpp.archive." + file.stem().string(), quill::LogLevel::TraceL1);

        LOG_DEBUG(log, "[{}]Importing archive: {}", __func__, file.string());

        if (std::filesystem::exists(file))
        {
            LOG_DEBUG(log, "[{}] File exists", __func__);
            if (is_regular_file(file))
            {
                LOG_DEBUG(log, "[{}] Archive found, unzipping", __func__);
                dir = utils::zip_ns::unzip_to_temp_dir(file.string(), tmp_prefix, log);
                using_tmp_dir = true;
            }
            else if (is_directory(file))
            {
                LOG_DEBUG(log, "[{}] Directory found", __func__);
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
            LOG_DEBUG(log, "[{}] File does not exist", __func__);
            // try to remove the extension
            if (file.has_extension())
            {
                LOG_DEBUG(log, "[{}] Retrying by removing extension", __func__);
                auto f = file;
                auto file_no_ext = f.replace_extension();

                if (is_regular_file(file_no_ext))
                {
                    LOG_DEBUG(log, "[{}] Archive found, unzipping", __func__);
                    dir = utils::zip_ns::unzip_to_temp_dir(file_no_ext.string(), tmp_prefix, log);
                    using_tmp_dir = true;
                }
                else if (is_directory(file_no_ext))
                {
                    LOG_DEBUG(log, "[{}] Directory found", __func__);
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
                LOG_DEBUG(log, "[{}] File does not have extension, no more options to retry", __func__);
                throw std::runtime_error("File is not a regular file or directory: " + file.string());
            }
        }
    }

    /** @brief Clean up any temporary directory used by the archive. */
    Archive::~Archive()
    {
        LOG_DEBUG(log, "Destructor called for archive {}", original_file.string());
        if (using_tmp_dir)
        {
            remove_all(dir);
        }
    }
}
