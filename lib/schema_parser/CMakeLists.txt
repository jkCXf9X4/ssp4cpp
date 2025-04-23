

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC schema_parser ="${ALL_SRC}")

add_library(schema_parser ${ALL_SRC})

target_include_directories(schema_parser
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/include/interface
    ${CMAKE_CURRENT_LIST_DIR}/include/schema
    ${CMAKE_CURRENT_LIST_DIR}/include/schema/ssp1
    ${CMAKE_CURRENT_LIST_DIR}/include/schema/fmi2
    ${CMAKE_CURRENT_LIST_DIR}/include/schema_ext

  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include_private
    ${CMAKE_CURRENT_LIST_DIR}/include_private/fmi2
    ${CMAKE_CURRENT_LIST_DIR}/include_private/ssp1   
)

# target_compile_options(schema_parser PRIVATE -Wfatal-errors)

find_package(boost_log CONFIG REQUIRED)
target_link_libraries(schema_parser PRIVATE Boost::log)

find_package(libzip CONFIG REQUIRED)
target_link_libraries(schema_parser PRIVATE libzip::zip)

find_package(pugixml CONFIG REQUIRED)
target_link_libraries(schema_parser PRIVATE pugixml::static pugixml::pugixml)

