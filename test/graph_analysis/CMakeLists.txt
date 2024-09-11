
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/schema)
include_directories(${PROJECT_SOURCE_DIR}/include/schema/ssp1)

add_executable(ssp4cpp_graph main.cpp)
target_link_libraries(ssp4cpp_graph PRIVATE ssp4cpp)

target_link_libraries(ssp4cpp_graph PRIVATE ssp4cpp::3rd::fmi4c)

find_package(boost_log REQUIRED CONFIG)
target_link_libraries(ssp4cpp_graph PRIVATE Boost::log)

find_package(boost_graph REQUIRED CONFIG)
target_link_libraries(ssp4cpp_graph PRIVATE Boost::graph)