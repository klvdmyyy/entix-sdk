#pragma once

#include "engine/core/Result.h"
#include "engine/core/Assert.h"

#include <string>
#include <filesystem>

// Platform independent implementation of dynamic link library.
//
// Used for module/plugin loading
class DynamicLibrary
{
public:
    ENGINE_API DynamicLibrary(const std::filesystem::path& path, bool autoload = true);
    ENGINE_API ~DynamicLibrary();

    DynamicLibrary(const DynamicLibrary&)
    {
        E_UNIMPLEMENTED_FMT("DynamicLibrary copy-constructor");
    }
    DynamicLibrary& operator=(const DynamicLibrary&)
    {
        E_UNIMPLEMENTED_FMT("DynamicLibrary copy-assignment");
    }

    DynamicLibrary(DynamicLibrary&&) = delete;
    DynamicLibrary& operator=(DynamicLibrary&&) = delete;

    ENGINE_API Result<void> Load();
    ENGINE_API Result<void> Unload();

    template<typename F>
    Result<F> GetSymbol(const std::string& name)
    {
        E_ASSERT(m_loaded);
    }

private:
    bool m_loaded = false;
};