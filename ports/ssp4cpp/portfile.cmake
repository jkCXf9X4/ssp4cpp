vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO jkCXf9X4/ssp4cpp
    REF "${VERSION}"
    SHA512 6f99c6c3acb89abbb9f639c25c581a424b2a26d0c53e8bde67bc9cf65992c2fc41834d617b8548edf9a91cdadbdfa9d3fce58ccf2dd85e373d3e285ea9ce550d
    HEAD_REF main
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DSSP4CPP_BUILD_TESTS=OFF
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
    PACKAGE_NAME "ssp4cpp"
    CONFIG_PATH lib/cmake/ssp4cpp
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

vcpkg_install_copyright(
    FILE_LIST "${SOURCE_PATH}/LICENCE"
)
