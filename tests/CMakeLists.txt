find_package(Catch2 3 CONFIG REQUIRED)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC schema_lib ="${ALL_SRC}")

add_executable(logger_tests
    ${ALL_SRC}
)

target_link_libraries(logger_tests
    PRIVATE
        schema_lib
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(logger_tests)
