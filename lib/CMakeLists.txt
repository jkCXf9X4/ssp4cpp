

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC ssp4cpp ="${ALL_SRC}")

add_library(ssp4cpp STATIC ${ALL_SRC})

target_include_directories(ssp4cpp
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
    ${CMAKE_CURRENT_LIST_DIR}/include_private/utils   
)
target_compile_options(ssp4cpp PRIVATE -Wfatal-errors)

find_package(pugixml CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE pugixml::static pugixml::pugixml)

find_package(libzip CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE libzip::zip)

find_package(cutecpp CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE cutecpp::cutecpp)