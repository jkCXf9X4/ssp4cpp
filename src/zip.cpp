

#include <zip.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include <random>

#include <boost/log/trivial.hpp>

#include "zip.hpp"

// from https://github.com/NTNU-IHB/FMI4cpp/blob/master/src/fmi4cpp/tools/unzipper.hpp

namespace ssp4cpp::zip_ns
{

    namespace fs = std::filesystem;

    std::string random_generator(size_t length = 16)
    {
        const char charset[] = "0123456789"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);

        std::random_device rd;        // Obtain a random number from hardware
        std::mt19937 generator(rd()); // Seed the generator
        std::uniform_int_distribution<> distribution(0, max_index);

        std::stringstream ss;
        for (size_t i = 0; i < length; ++i)
        {
            ss << charset[distribution(generator)];
        }

        return ss.str();
    }

    bool unzip(fs::path &file, const fs::path &tmp_path)
    {
        BOOST_LOG_TRIVIAL(trace) << "Unzipping " << file << std::endl;

        int *err = nullptr;
        zip *za = zip_open(absolute(file).string().c_str(), 0, err);
        if (za == nullptr)
        {
            return false;
        }

        struct zip_file *zf;
        struct zip_stat sb
        {
        };

        const int bufferSize = 1000;
        std::vector<char> contents(bufferSize);
        zip_int64_t sum;
        zip_int64_t len;
        for (int i = 0; i < zip_get_num_entries(za, 0); i++)
        {
            if (zip_stat_index(za, i, 0, &sb) == 0)
            {

                const fs::path newFile = tmp_path / sb.name;

                if (sb.size == 0)
                {
                    fs::create_directories(newFile);
                }
                else
                {
                    const auto containingDirectory = newFile.parent_path();
                    if (!fs::exists(containingDirectory) && !fs::create_directories(containingDirectory))
                    {
                        return false;
                    }
                    zf = zip_fopen_index(za, i, 0);

                    std::ofstream file;
                    std::cout << "newFile: " << newFile << std::endl;
                    file.open(newFile, std::ios::out | std::ios::binary);

                    sum = 0;
                    while (sum != sb.size)
                    {
                        len = zip_fread(zf, contents.data(), bufferSize);
                        file.write(contents.data(), len);
                        sum += len;
                    }

                    file.flush();
                    file.close();

                    zip_fclose(zf);
                }
            }
        }
        zip_close(za);

        BOOST_LOG_TRIVIAL(trace) << "Completed Unzipping " << file << std::endl;

        return true;
    }

    fs::path create_temp_dir(const std::string &fileName, const std::string &pre)
    {
        auto temp_dir_base = fs::temp_directory_path();
        auto unique_id = random_generator();
        auto temp_dir = temp_dir_base / (pre + unique_id);

        BOOST_LOG_TRIVIAL(debug) << "Temp dir: " << temp_dir << std::endl;
        std::cout << "Temp dir: " << temp_dir << std::endl;

        fs::create_directory(temp_dir);

        return temp_dir;
    }

    fs::path unzip_to_temp_dir(const std::string &fileName)
    {
        auto file = fs::path(fileName);
        if (!fs::exists(file))
        {
            BOOST_LOG_TRIVIAL(warning) << "File does not exist: " << fileName << "  " << std::endl;
            throw std::runtime_error("File does not exist: " + fileName);
        }

        auto temp_dir = create_temp_dir(fileName, "ssp4cpp_");

        ssp4cpp::zip_ns::unzip(file, temp_dir);

        return temp_dir;
    }
}