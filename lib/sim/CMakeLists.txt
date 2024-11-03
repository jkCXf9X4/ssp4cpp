

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC sim ="${ALL_SRC}")

add_library(sim ${ALL_SRC})

target_include_directories(sim
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include

  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include_private  
)

# target_compile_options(sim PRIVATE -Wfatal-errors)

find_package(boost_log CONFIG REQUIRED)
target_link_libraries(sim PRIVATE Boost::log)
