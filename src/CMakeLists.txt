file(GLOB_RECURSE SOURCES
    *.h
    *.c
)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_executable(ccobalt ${SOURCES})
set_property(TARGET ccobalt PROPERTY C_STANDARD 23)

target_link_libraries(ccobalt m)
target_link_libraries(ccobalt ${CURL_LIBRARIES})