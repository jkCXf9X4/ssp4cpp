
file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC sim ="${ALL_SRC}")

add_library(sim ${ALL_SRC})

target_include_directories(sim
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/include/graph
    ${CMAKE_CURRENT_LIST_DIR}/include/graph/analysis
    ${CMAKE_CURRENT_LIST_DIR}/include/handler
    ${CMAKE_CURRENT_LIST_DIR}/include/utils
    ${CMAKE_CURRENT_LIST_DIR}/include/execution

  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include_private  
)

target_compile_options(sim PRIVATE -Wfatal-errors)

target_link_libraries(sim PRIVATE schema_lib)
target_link_libraries(sim PRIVATE common)


find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(sim PRIVATE nlohmann_json::nlohmann_json)

find_package(TBB CONFIG REQUIRED)
target_link_libraries(sim PRIVATE TBB::tbb TBB::tbbmalloc)

find_package(fmi4cpp REQUIRED CONFIG)
target_link_libraries(sim PRIVATE fmi4cpp::fmi4cpp)
