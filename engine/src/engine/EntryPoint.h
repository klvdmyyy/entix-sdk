#pragma once

#include "engine/Result.h"

/// @brief Platform-independent entry point
extern Result<void> EngineMain(int argc, char** argv);

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
        auto mainResult = ::EngineMain(__argc, __argv);
        return mainResult.IsSuccess() ? 0 : 1;
    }
    //! [entry_windows]
#else
    //! [entry_linux]
    int main(int argc, char** argv) // NOLINT
    {
        auto mainResult = ::EngineMain(argc, argv);
        return mainResult.IsSuccess() ? 0 : 1;
    }
    //! [entry_linux]
#endif