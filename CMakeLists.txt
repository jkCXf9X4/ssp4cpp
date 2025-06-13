cmake_minimum_required(VERSION 3.10)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" projectVersion)
project(ssp4cpp VERSION ${projectVersion})


message("Current ssp4cpp version: ${projectVersion}\n")

message("CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}\n")
message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}\n")

message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}\n")
message("CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}\n")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n")

set(CMAKE_CXX_STANDARD 23)

project(ssp4cpp)

add_subdirectory(3rdParty)

add_subdirectory(lib/common)
add_subdirectory(lib/schema)
add_subdirectory(lib/sim)

add_subdirectory(app/sim)
add_subdirectory(test)

