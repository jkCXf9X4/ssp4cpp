

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC ssp4cpp ="${ALL_SRC}")

add_library(ssp4cpp STATIC ${ALL_SRC})
add_library(ssp4cpp::ssp4cpp ALIAS ssp4cpp)

target_compile_features(ssp4cpp PUBLIC cxx_std_23)

target_include_directories(ssp4cpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include_private
        ${CMAKE_CURRENT_LIST_DIR}/include_private/schema/fmi2
        ${CMAKE_CURRENT_LIST_DIR}/include_private/schema/ssp1
        ${CMAKE_CURRENT_LIST_DIR}/include_private/utils
)

target_compile_options(ssp4cpp PRIVATE -Wfatal-errors)

find_package(pugixml CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE pugixml::static pugixml::pugixml)

find_package(libzip CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE libzip::zip)

find_package(cutecpp CONFIG REQUIRED)
target_link_libraries(ssp4cpp PRIVATE cutecpp::cutecpp)

set(SSP4CPP_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/ssp4cpp")

install(TARGETS ssp4cpp
    EXPORT ssp4cppTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ssp4cppTargets
    NAMESPACE ssp4cpp::
    FILE ssp4cppTargets.cmake
    DESTINATION ${SSP4CPP_CONFIG_INSTALL_DIR})

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ssp4cppConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ssp4cppConfig.cmake
    INSTALL_DESTINATION ${SSP4CPP_CONFIG_INSTALL_DIR})

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ssp4cppConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ssp4cppConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ssp4cppConfigVersion.cmake
    DESTINATION ${SSP4CPP_CONFIG_INSTALL_DIR})
