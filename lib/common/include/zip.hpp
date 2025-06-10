#pragma once

#include <filesystem>

// dont name this 'zip', collision between namespace and types makes life harder
namespace ssp4cpp::common::zip_ns
{
    namespace fs = std::filesystem;

    /**
     * @brief Extract a zip archive to a newly created temporary directory.
     *
     * @param fileName Path to the archive file.
     * @param pre Prefix used when creating the temporary directory.
     * @return Path to the created directory containing the extracted files.
     */
    fs::path unzip_to_temp_dir(const std::string fileName, std::string pre);
}