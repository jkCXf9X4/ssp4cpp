
file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "*.hpp" "*.cpp")

# message(ALL_SRC sim ="${ALL_SRC}")

# add_library(ssp4cpp_python_da ${ALL_SRC})

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

# pybind11 method:
pybind11_add_module(py_ssp4cpp ${ALL_SRC})

target_link_libraries(py_ssp4cpp PRIVATE schema_lib)
target_link_libraries(py_ssp4cpp PRIVATE common)
target_link_libraries(py_ssp4cpp PRIVATE sim)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/pyproject.toml" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/pyssp4cpp")


add_custom_command(
    TARGET py_ssp4cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:py_ssp4cpp>
            ${CMAKE_CURRENT_BINARY_DIR}/pyssp4cpp/$<TARGET_FILE_NAME:py_ssp4cpp>
)
