add_subdirectory(_core)

if(SKBUILD)
    install(FILES __init__.py DESTINATION ${PYTHON_PACKAGE_NAME}/)
endif()
