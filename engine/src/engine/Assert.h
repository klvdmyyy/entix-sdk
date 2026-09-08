#pragma once

#include "engine/BaseMacros.h"
#include "engine/BaseTypes.h"

#include <string>
#include <format>
#include <source_location>
#include <filesystem>

// -----------------------------------------------
// Platform-independent debug break definition
// -----------------------------------------------
#ifdef ENGINE_BUILD_DEBUG
    #ifdef ENGINE_PLATFORM_WINDOWS
        #define E_DEBUGBREAK() __debugbreak()
    #else
        #warning "Debug break are not supported on current platform!"
        #define E_DEBUGBREAK()
    #endif
#else
    #define E_DEBUGBREAK()
#endif

// -----------------------------------------------
// Source location wrapper
// -----------------------------------------------
class SourceLocation {
public:
    [[nodiscard]]
    static consteval SourceLocation Current()
    {
        std::source_location location = std::source_location::current();
        return SourceLocation(location.line(), location.column(), location.file_name(), location.function_name());
    }

    [[nodiscard]]
    constexpr Usize GetLine() const noexcept
    {
        return m_line;
    }

    [[nodiscard]]
    constexpr Usize GetColumn() const noexcept
    {
        return m_column;
    }

    [[nodiscard]]
    constexpr const char* GetFileNameRaw() const noexcept
    {
        return m_filename;
    }

    [[nodiscard]]
    std::filesystem::path GetFilePath() const noexcept
    {
        return std::filesystem::path(GetFileNameRaw());
    }

    [[nodiscard]]
    std::filesystem::path GetFileName() const noexcept
    {
        return std::filesystem::path(GetFileNameRaw()).filename();
    }

    [[nodiscard]]
    const char* GetFunctionName() const noexcept
    {
        return m_functionname;
    }

private:
    constexpr SourceLocation(
        Uint32 line_,
        Uint32 column_,
        const char* filename_,
        const char* functionname_
    ) : m_line(line_),
        m_column(column_),
        m_filename(filename_),
        m_functionname(functionname_)
    {
    }

    Uint32 m_line;
    Uint32 m_column;
    const char* m_filename;
    const char* m_functionname;
};

// -----------------------------------------------
// Panic
// -----------------------------------------------
[[noreturn]] ENGINE_API void HandlePanic(SourceLocation location = SourceLocation::Current());
[[noreturn]] ENGINE_API void HandlePanic(const std::string& message, SourceLocation location = SourceLocation::Current());

#define E_PANIC() HandlePanic()
#define E_PANIC_FMT(MSG, ...) HandlePanic(std::format(MSG, ##__VA_ARGS__))

// -----------------------------------------------
// Unimplemented
// -----------------------------------------------
[[noreturn]] ENGINE_API void HandleUnimplemented(SourceLocation location = SourceLocation::Current());
[[noreturn]] ENGINE_API void HandleUnimplemented(const std::string& message, SourceLocation location = SourceLocation::Current());

#define E_UNIMPLEMENTED() HandleUnimplemented()
#define E_UNIMPLEMENTED_FMT(MSG, ...) HandleUnimplemented(std::format(MSG, ##__VA_ARGS__))

// -----------------------------------------------
// Unreachable
// -----------------------------------------------
[[noreturn]] ENGINE_API void HandleUnreachable(SourceLocation location = SourceLocation::Current());
[[noreturn]] ENGINE_API void HandleUnreachable(const std::string& message, SourceLocation location = SourceLocation::Current());

#define E_UNREACHABLE() HandleUnreachable()
#define E_UNREACHABLE_FMT(MSG, ...) HandleUnreachable(std::format(MSG, ##__VA_ARGS__))

// -----------------------------------------------
// Assertion
// -----------------------------------------------
[[noreturn]] ENGINE_API void HandleAssert(const std::string& expr, SourceLocation location = SourceLocation::Current());
[[noreturn]] ENGINE_API void HandleAssert(const std::string& expr, const std::string& message, SourceLocation location = SourceLocation::Current());

#define E_ASSERT(EXPR) do { if(!(EXPR)) { HandleAssert(#EXPR); } } while(0)
#define E_ASSERT_FMT(EXPR, FMT, ...) do { if(!(EXPR)) { HandleAssert(#EXPR, std::format(FMT, ##__VA_ARGS__)); } } while(0)
