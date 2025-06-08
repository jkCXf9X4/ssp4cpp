
file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC sim ="${ALL_SRC}")

add_executable(sim_app ${ALL_SRC})

target_compile_options(sim_app PRIVATE -Wfatal-errors)

target_link_libraries(sim_app PRIVATE sim)
target_link_libraries(sim_app PRIVATE schema_lib)
target_link_libraries(sim_app PRIVATE common)


find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(sim_app PRIVATE nlohmann_json::nlohmann_json)
