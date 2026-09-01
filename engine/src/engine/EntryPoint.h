#pragma once

/// @brief Platform-independent entry point
extern int EngineMain(int argc, char** argv);

#if defined(ENGINE_PLATFORM_WINDOWS) & defined(ENGINE_WINDOWS_WIN32_BUILD)
    //! [entry_windows]
    #include <Windows.h>
    int APIENTRY WinMain(
        [[maybe_unused]] HINSTANCE hInstance,
        [[maybe_unused]] HINSTANCE hPrevInstance,
        [[maybe_unused]] LPSTR lpCmdLine,
        [[maybe_unused]] int nShowCmd
    )
    {
        return ::EngineMain(__argc, __argv);
    }
    //! [entry_windows]
#else
    //! [entry_linux]
    int main(int argc, char** argv) // NOLINT
    {
        return ::EngineMain(argc, argv);
    }
    //! [entry_linux]
#endif