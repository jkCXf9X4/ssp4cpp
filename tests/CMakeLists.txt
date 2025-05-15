

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC sim ="${ALL_SRC}")

add_executable(test_1 ${ALL_SRC})
# add_library(sim ${ALL_SRC})

target_include_directories(test_1
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include

  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include_private  
)

# target_compile_options(sim PRIVATE -Wfatal-errors)

target_link_libraries(test_1 PRIVATE schema)
target_link_libraries(test_1 PRIVATE common)

find_package(fmi4cpp REQUIRED CONFIG)
target_link_libraries(test_1 PRIVATE fmi4cpp::fmi4cpp)
