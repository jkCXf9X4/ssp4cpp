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

# Optimize release builds
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto -O3 -march=native -fno-omit-frame-pointer -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto -O3 -march=native -fno-omit-frame-pointer -DNDEBUG" CACHE STRING "" FORCE)

# Debug builds keep symbols, no optimizations
set(CMAKE_CXX_FLAGS_DEBUG "-O3 -g" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG   "-O3 -g" CACHE STRING "" FORCE)

# Unsure how much this does
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffp-contract=fast -fno-math-errno -fno-trapping-math")


# Status

message("CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}\n")
message("CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}\n")

message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}\n")
message("CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}\n")

message("CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}\n")
message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}\n")

message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}\n")
message("CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}\n")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n")

# Subdirectories

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


