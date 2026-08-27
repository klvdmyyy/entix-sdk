#pragma once

#include "engine/core/BaseMacros.h"

#include <string>
#include <format>
#include <source_location>

class SourceLocation {
public:
    static SourceLocation Current();
};

// -----------------------------------------------
// Panic
// -----------------------------------------------
ENGINE_API void [[noreturn]] HandlePanic(SourceLocation location = SourceLocation::Current());
ENGINE_API void [[noreturn]] HandlePanic(const std::string& message, SourceLocation location = SourceLocation::Current());

#define E_PANIC() HandlePanic()
#define E_PANIC_FMT(MSG, ...) HandlePanic(std::format(MSG, ##__VA_ARGS__))

// -----------------------------------------------
// Unimplemented
// -----------------------------------------------
ENGINE_API void [[noreturn]] HandleUnimplemented(SourceLocation location = SourceLocation::Current());
ENGINE_API void [[noreturn]] HandleUnimplemented(const std::string& message, SourceLocation location = SourceLocation::Current());

#define E_UNIMPLEMENTED() HandleUnimplemented()
#define E_UNIMPLEMENTED_FMT(MSG, ...) HandleUnimplemented(std::format(MSG, ##__VA_ARGS__))

// -----------------------------------------------
// Unreachable
// -----------------------------------------------
ENGINE_API void [[noreturn]] HandleUnreachable(SourceLocation location = SourceLocation::Current());
ENGINE_API void [[noreturn]] HandleUnreachable(const std::string& message, SourceLocation location = SourceLocation::Current());

#define E_UNREACHABLE() HandleUnreachable()
#define E_UNREACHABLE_FMT(MSG, ...) HandleUnreachable(std::format(MSG, ##__VA_ARGS__))

// -----------------------------------------------
// Assertion
// -----------------------------------------------
ENGINE_API void [[noreturn]] HandleAssert(const std::string& expr, SourceLocation location = SourceLocation::Current());
ENGINE_API void [[noreturn]] HandleAssert(const std::string& expr, const std::string& message, SourceLocation location = SourceLocation::Current());

#define E_ASSERT(EXPR) do { if(!(EXPR)) { HandleAssert(#EXPR); } } while(0)
#define E_ASSERT_FMT(EXPR, FMT, ...) do { if(!(EXPR)) { HandleAssert(#EXPR, std::format(FMT, ##__VA_ARGS__)); } } while(0)
