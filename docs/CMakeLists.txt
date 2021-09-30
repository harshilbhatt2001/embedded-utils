find_package(Doxygen)
if (DOXYGEN_FOUND)
    # Find all the public headers
    get_target_property(EMBEDDED_UTILS_PUBLIC_HEADER_DIR embedded_utils_lib INTERFACE_INCLUDE_DIRECTORIES)
    file(GLOB_RECURSE EMBEDDED_UTILS_PUBLIC_HEADER_DIR ${EMBEDDED_UTILS_PUBLIC_HEADER_DIR}/*.h)

    # set input and output files
    set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/include)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doxygen)
    set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)


    # request to configure the file
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
    message("Doxygen build started")

    # This is the main output
    set(DOXYGEN_INDEX_FILE ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html)

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_command( OUTPUT ${DOXYGEN_INDEX_FILE}
                        DEPENDS ${EMBEDDED_UTILS_PUBLIC_HEADER_DIR}
                        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                        COMMENT "Generating API documentation with Doxygen"
                        VERBATIM )

    add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# sphinx
find_package(Sphinx REQUIRED)
find_package(Sphinx REQUIRED)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)

add_custom_target(Sphinx ALL
        COMMAND
        ${SPHINX_EXECUTABLE} -b html
        # Tell Breathe where to find the Doxygen output
        -Dbreathe_projects.embedded_utils=${DOXYGEN_OUTPUT_DIR}/xml
        ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Sphinx")
