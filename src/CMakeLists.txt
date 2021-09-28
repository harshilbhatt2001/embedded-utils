set(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CMAKE_PROJECT_NAME}/include/embedded_utils/*.h")
file(GLOB_RECURSE SOURCES_LIST LIST_DIRECTORIES true *.c)
set(SOURCES_LIST ${SOURCES_LIST})

# Make automatic library - will be static or dynamic based on user setting
add_library(embedded_utils_lib ${SOURCES_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it to
target_include_directories(embedded_utils_lib PUBLIC ../include)

# IDEs should put the headers in a nice place
source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)