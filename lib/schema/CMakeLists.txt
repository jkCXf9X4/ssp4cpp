

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC schema_lib ="${ALL_SRC}")

add_library(schema_lib ${ALL_SRC})

target_include_directories(schema_lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/include/schema
    ${CMAKE_CURRENT_LIST_DIR}/include/schema/ssp1
    ${CMAKE_CURRENT_LIST_DIR}/include/schema/fmi2
    ${CMAKE_CURRENT_LIST_DIR}/include/schema_ext

  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include_private
    ${CMAKE_CURRENT_LIST_DIR}/include_private/fmi2
    ${CMAKE_CURRENT_LIST_DIR}/include_private/ssp1   
)
target_compile_options(schema_lib PRIVATE -Wfatal-errors)

target_link_libraries(schema_lib PRIVATE common)

find_package(pugixml CONFIG REQUIRED)
target_link_libraries(schema_lib PRIVATE pugixml::static pugixml::pugixml)
