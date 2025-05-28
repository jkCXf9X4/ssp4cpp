

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC common ="${ALL_SRC}")

add_library(common ${ALL_SRC})

target_include_directories(common
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include

  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include_private  
)

# target_compile_options(common PRIVATE -Wfatal-errors)

find_package(libzip CONFIG REQUIRED)
target_link_libraries(common PRIVATE libzip::zip)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(common PRIVATE nlohmann_json::nlohmann_json)