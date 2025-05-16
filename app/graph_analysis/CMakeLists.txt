

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

message(ALL_SRC ssp4cpp_graph ="${ALL_SRC}")

add_executable(ssp4cpp_graph ${ALL_SRC})

target_include_directories(ssp4cpp_graph
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include_private
)

# target_compile_options(ssp4cpp_graph PRIVATE -Wfatal-errors)

target_link_libraries(ssp4cpp_graph PRIVATE schema_lib)
target_link_libraries(ssp4cpp_graph PRIVATE common)

find_package(boost_graph REQUIRED CONFIG)
target_link_libraries(ssp4cpp_graph PRIVATE Boost::graph)