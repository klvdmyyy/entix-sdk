function(setup_sdl3_binaries TARGET_NAME)
    set(SDL3_VERSION "3.4.14" CACHE STRING "SDL3 version to download")

    find_package(SDL3 QUIET CONFIG)
    if(SDL3_FOUND)
        message(STATUS "SDL3 found via find_package")

        get_target_property(SDL3_LOCATION SDL3::SDL3-shared IMPORTED_LOCATION_RELEASE)
        if(NOT SDL3_LOCATION)
            get_target_property(SDL3_LOCATION SDL3::SDL3-shared IMPORTED_LOCATION)
        endif()

        if(SDL3_LOCATION AND EXISTS "${SDL3_LOCATION}")
            add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${SDL3_LOCATION}"
                    $<TARGET_FILE_DIR:${TARGET_NAME}>
                COMMENT "Copying SDL3 binaries from system")
        endif()
        return()
    endif()

    message(STATUS "SDL3 not found, downloading prebuilt binaries")
endfunction()