

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/schema)

add_library(ssp4cpp ssp4cpp.cpp)

find_package(libzip CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE libzip::zip)

find_package(pugixml CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE pugixml::static pugixml::pugixml)

