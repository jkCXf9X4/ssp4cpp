
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/schema)
include_directories(${PROJECT_SOURCE_DIR}/include/schema/ssp1)

add_executable(ssp4cpp_test main.cpp)
target_link_libraries(ssp4cpp_test PRIVATE ssp4cpp)
