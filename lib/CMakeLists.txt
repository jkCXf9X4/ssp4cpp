

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC schema_lib ="${ALL_SRC}")

add_library(schema_lib STATIC ${ALL_SRC})

target_include_directories(schema_lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/include/schema
    ${CMAKE_CURRENT_LIST_DIR}/include/schema/ssp1
    ${CMAKE_CURRENT_LIST_DIR}/include/schema/fmi2
    ${CMAKE_CURRENT_LIST_DIR}/include/utils
    ${CMAKE_CURRENT_LIST_DIR}/include/extensions

  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include_private
    ${CMAKE_CURRENT_LIST_DIR}/include_private/schema/fmi2
    ${CMAKE_CURRENT_LIST_DIR}/include_private/schema/ssp1   
)
target_compile_options(schema_lib PRIVATE -Wfatal-errors)

find_package(pugixml CONFIG REQUIRED)
target_link_libraries(schema_lib PRIVATE pugixml::static pugixml::pugixml)


find_package(libzip CONFIG REQUIRED)
target_link_libraries(schema_lib PRIVATE libzip::zip)