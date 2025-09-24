cmake_minimum_required(VERSION 3.10)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" projectVersion)
project(ssp4cpp VERSION ${projectVersion})
message("Current ssp4cpp version: ${projectVersion}\n")

set(CMAKE_CXX_STANDARD 23)

# OPTIONS
option(SSP4CPP_BUILD_TEST "Build test executable" ON)
option(SSP4CPP_BUILD_PYTHON "Build python lib" OFF)

## Link static
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++")



# COMPILER

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -flto")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

message("CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}\n")
message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}\n")

message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}\n")
message("CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}\n")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n")


# OTHER
#set(CMAKE_BUILD_TYPE Release) # Turn off debug outputs for fmi4ssp

add_subdirectory(3rdParty)

add_subdirectory(lib/common)
add_subdirectory(lib/schema)
add_subdirectory(lib/sim)

add_subdirectory(app/sim)

if (SSP4CPP_BUILD_TEST)
    message("Building tests\n")
    add_subdirectory(tests)
ENDIF ()

if (SSP4CPP_BUILD_PYTHON)
    add_subdirectory(lib/python)
ENDIF ()


