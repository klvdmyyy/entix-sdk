add_executable(game src/Main.cpp)

target_link_libraries(game PRIVATE engine)

include(third-party)

setup_sdl3_binaries(game)

# Copy engine.dll and all other dlls to game executable directory
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:game>
        $<TARGET_FILE_DIR:game>
    COMMAND_EXPAND_LISTS)