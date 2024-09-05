cmake_minimum_required(VERSION 3.10)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" projectVersion)
project(ssp4cpp VERSION ${projectVersion})
message("Current ssp4cpp version: ${projectVersion}\n")

set(CMAKE_CXX_STANDARD 17)

project(ssp4cpp)

add_subdirectory(src)
add_subdirectory(test)

