find_package(Catch2 3 CONFIG REQUIRED)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

add_executable(tests
    ${ALL_SRC}
)

target_link_libraries(tests
    PRIVATE
        ssp4cpp
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(tests)
