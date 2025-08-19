   
    
file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

message(ALL_SRC sim ="Test1 ${ALL_SRC}")

add_executable(test_1 ${ALL_SRC})

# target_include_directories(test_1
#   PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/include

#   PRIVATE
#     ${CMAKE_CURRENT_LIST_DIR}/include_private  
# )

# target_compile_options(sim PRIVATE -Wfatal-errors)
find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(test_1 PRIVATE Catch2::Catch2WithMain)

target_link_libraries(test_1 PRIVATE schema_lib)
target_link_libraries(test_1 PRIVATE common)
target_link_libraries(test_1 PRIVATE sim)

include(Catch)
catch_discover_tests(test_1)