find_package(Catch2 3 CONFIG REQUIRED)

add_executable(logger_tests
    logger_tests.cpp
)

target_link_libraries(logger_tests
    PRIVATE
        schema_lib
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(logger_tests)
