

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/interface)
include_directories(${PROJECT_SOURCE_DIR}/include/schema)
include_directories(${PROJECT_SOURCE_DIR}/include/schema/ssp1)
include_directories(${PROJECT_SOURCE_DIR}/include/schema/fmi2)
include_directories(${PROJECT_SOURCE_DIR}/include_private)
include_directories(${PROJECT_SOURCE_DIR}/include_private/fmi2)
include_directories(${PROJECT_SOURCE_DIR}/include_private/ssp1)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

add_library(ssp4cpp  ${ALL_SRC})

target_compile_options(ssp4cpp PRIVATE -Wfatal-errors)

find_package(boost_log CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE Boost::log)

find_package(libzip CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE libzip::zip)

find_package(pugixml CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE pugixml::static pugixml::pugixml)

