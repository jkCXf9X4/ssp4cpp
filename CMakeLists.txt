cmake_minimum_required(VERSION 3.10)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt" projectVersion)
project(ssp4cpp VERSION ${projectVersion})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
     if(EXISTS "/usr/bin/lld")
         message(STATUS "Using lld linker")
         set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
         set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=lld")
     endif()
 endif()

# # Speed up linker times
add_compile_options(-gsplit-dwarf)

message("Current ssp4cpp version: ${projectVersion}\n")

message("CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}\n")
message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}\n")

# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -flto -O3")

message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}\n")
message("CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}\n")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n")

set(CMAKE_BUILD_TYPE Release) # Turn off debug outputs for fmi4ssp

set(CMAKE_CXX_STANDARD 23)

option(SSP4CPP_BUILD_TEST "Build test executable" OFF)
option(SSP4CPP_BUILD_PYTHON "Build python lib" OFF)

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


