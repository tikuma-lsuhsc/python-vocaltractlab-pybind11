cmake_minimum_required(VERSION 3.27)

set(PYTHON_PACKAGE_NAME vocaltractlab)
set(PROJECT_NAME _core)

project(${PROJECT_NAME} LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)

find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

add_subdirectory(pybind11)
add_subdirectory(fmt)

if (MSVC)
	if (MSVC_VERSION VERSION_LESS 1930)
		message(FATAL_ERROR "Visual Studio 2022 (or later) is required to build Parselmouth.")
	endif ()
	add_compile_options(/permissive- /Zc:inline) # Please follow the standard more closely, MSVC (e.g. adds ciso646 alternative tokens for logical operators)
	add_compile_options(/utf-8) # Because Praat contains source files with unicode chars encoded as UTF-8, and because UTF-8 is not default enough for MSVC to read and compile these files correctly (also, because it's 2020 by now)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS UNICODE NOMINMAX) # Windows no "safe alternatives" warning, Windows unicode API by default, and no <windows.h> 'min' and 'max' macros
	if (MSVC_VERSION GREATER_EQUAL 1920)
		add_compile_options(/d2FH4-) # Because we don't want to link against VCRUNTIME140_1.dll (see https://cibuildwheel.readthedocs.io/en/stable/faq/#importerror-dll-load-failed-the-specific-module-could-not-be-found-error-on-windows)
	endif ()
	add_compile_definitions(_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING) # TODO 0.5: Update libfmt, so we don't need to silence this anymore? And what about C++20?
	add_compile_options(/wd4828)
endif ()

add_subdirectory(src)

add_subdirectory(vocaltractlab_backend)
target_link_libraries(${PROJECT_NAME} PRIVATE VocalTractLabBackend)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)

if(SKBUILD)
    install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${PYTHON_PACKAGE_NAME})
endif()
