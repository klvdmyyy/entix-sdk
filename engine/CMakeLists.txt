add_subdirectory(vendor)

function(collect_platform_files PLATFORM_NAME)
    set(HEADERS)
    set(SOURCES)

    file(GLOB_RECURSE PLATFORM_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/${PLATFORM_NAME}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/${PLATFORM_NAME}/*.hpp"
    )
    list(APPEND HEADERS ${PLATFORM_HEADERS})
    
    file(GLOB_RECURSE PLATFORM_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/${PLATFORM_NAME}/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/${PLATFORM_NAME}/*.cpp"
    )
    list(APPEND SOURCES ${PLATFORM_SOURCES})

    set(ENGINE_HEADERS ${ENGINE_HEADERS} ${HEADERS} PARENT_SCOPE)
    set(ENGINE_SOURCES ${ENGINE_SOURCES} ${SOURCES} PARENT_SCOPE)
endfunction()

file(
    GLOB_RECURSE
    ENGINE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.h
)

file(
    GLOB_RECURSE
    ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp
)

if(WIN32)
    message(STATUS "Collecting Windows platform-specific implementation")
    collect_platform_files(windows)
elseif(LINUX)
    message(STATUS "Collecting Linux platform-specific implementation")
    collect_platform_files(linux)
else()
    message(FATAL_ERROR "Current platform doesn't have platform-specific implementation")
endif()

# Engine main library are must be DLL
add_library(engine SHARED ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(engine
    PRIVATE
        vendor::glad)

target_compile_definitions(engine
    PRIVATE
        ENGINE_BUILD_DLL
    
    PUBLIC
        $<$<CONFIG:Debug>:ENGINE_BUILD_DEBUG>)

target_precompile_headers(engine PRIVATE
    <iostream>
    <memory>
    <utility>
    <algorithm>
    <functional>
    <string>
    <sstream>
    <vector>
    <array>
    <unordered_map>
    <unordered_set>
    <span>
    <variant>
    <cstddef>
    <cstdint>
    <print>
    <filesystem>
    <any>
    <condition_variable>
    <queue>
    <mutex>
    <thread>
    <type_traits>
    <future>)