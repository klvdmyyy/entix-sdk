file(GLOB_RECURSE
    GLAD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_library(glad ${GLAD_SOURCES})

target_include_directories(glad PUBLIC include/)

add_library(vendor::glad ALIAS glad)