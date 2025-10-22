find_package(Catch2 3 CONFIG REQUIRED)

file(GLOB_RECURSE SSP4CPP_TEST_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_executable(ssp4cpp_tests
    ${SSP4CPP_TEST_SOURCES}
)

target_link_libraries(ssp4cpp_tests
    PRIVATE
        ssp4cpp::ssp4cpp
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(ssp4cpp_tests)
