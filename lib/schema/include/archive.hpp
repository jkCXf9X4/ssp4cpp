#pragma once

#include "zip.hpp"
#include "common_log.hpp"
#include <filesystem>
#include <string>

using namespace std;
using namespace std::filesystem;

namespace ssp4cpp
{
    using namespace common;

    class Archive
    {
    public:
        Logger log;
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

        Archive(Logger log, const path &file, const std::string &tmp_prefix)
            : log(log),
              original_file(file)
        {

            log.info("Importing archive: {}", file.string());

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
                throw runtime_error("File is not a regular file or directory: " + file.string());
            }
        }

        virtual ~Archive()
        {
            log.debug("Destructor called for archive {}", original_file.string());
            if (using_tmp_dir)
            {
                remove_all(dir);
            }
        }

    };
}
