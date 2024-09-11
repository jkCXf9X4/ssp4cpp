
option(FMI4C_BUILD_SHARED OFF)
option(FMI4C_USE_INCLUDED_ZLIB ON)

add_subdirectory(fmi4c)
add_library(ssp4cpp::3rd::fmi4c ALIAS fmi4c)