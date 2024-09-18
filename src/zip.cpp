
#include "zip.hpp"

#include <zip.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/log/trivial.hpp>

// from https://github.com/NTNU-IHB/FMI4cpp/blob/master/src/fmi4cpp/tools/unzipper.hpp

namespace ssp4cpp::zip_ns
{

    namespace fs = std::filesystem;

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
        struct zip_stat sb{};

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
}