find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    # Find all the public headers
    get_target_property(EMBEDDED_UTILS_PUBLIC_HEADER_DIR embedded_utils_lib INTERFACE_INCLUDE_DIRECTORIES)
    file(GLOB_RECURSE EMBEDDED_UTILS_PUBLIC_HEADER_DIR ${EMBEDDED_UTILS_PUBLIC_HEADER_DIR}/*.h)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
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

    add_custom_target(docs ALL DEPENDS ${DOXYGEN_INDEX_FILE})
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

find_package(Sphinx REQUIRED)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/docs/sphinx)

add_custom_target(Sphinx ALL
        COMMAND ${SPHINX_EXECUTABLE} -b html
        # Tell Breathe where to find the Doxygen output
#        -Dbreathe_projects.CatCutifier=${DOXYGEN_OUTPUT_DIR}
        ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Sphinx")