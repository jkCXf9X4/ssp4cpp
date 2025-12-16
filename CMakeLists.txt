cmake_minimum_required(VERSION 3.15)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" projectVersion)
project(ssp4cpp VERSION ${projectVersion} LANGUAGES CXX)
message("ssp4cpp, version: ${projectVersion}\n")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SSP4CPP_BUILD_TESTS "Build ssp4cpp unit tests" OFF)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

## Link static
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
set(CMAKE_SHARED_LINKER_FLAGS "-static-libstdc++")


# COMPILER
# Optimize release builds
set(CMAKE_CXX_FLAGS_RELEASE "-flto=auto -O3 -g -march=native -fno-omit-frame-pointer -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-flto=auto -O3 -g -march=native -fno-omit-frame-pointer -DNDEBUG" CACHE STRING "" FORCE)

# Debug builds keep symbols, low optimizations
set(CMAKE_CXX_FLAGS_DEBUG "-O1 -fno-lto -g" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG   "-O1 -fno-lto -g" CACHE STRING "" FORCE)


# Status

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}\n")
message("CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}\n")
message("CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}\n")

message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}\n")
message("CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}\n")

message("CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}\n")
message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}\n")

message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}\n")
message("CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}\n")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n")
message("CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}\n")

add_subdirectory(3rdParty/cutecpp)
add_library(ssp4cpp::3rd::cutecpp ALIAS cutecpp)

add_subdirectory(lib)

if(SSP4CPP_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
