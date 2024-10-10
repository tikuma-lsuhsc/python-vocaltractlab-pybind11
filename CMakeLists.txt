cmake_minimum_required(VERSION 3.30)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

add_subdirectory(pybind11)

set(PYTHON_PACKAGE_NAME vocaltractlab)

add_subdirectory(src)

add_subdirectory(vocaltractlab_backend)
target_link_libraries(${PYTHON_PACKAGE_NAME} PRIVATE VocalTractLabBackend)
target_include_directories(${PYTHON_PACKAGE_NAME} PRIVATE vocaltractlab_backend/include)

if(SKBUILD)
    install(TARGETS ${PYTHON_PACKAGE_NAME} DESTINATION ${SKBUILD_PROJECT_NAME})
endif()
