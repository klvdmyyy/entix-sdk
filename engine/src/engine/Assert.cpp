#include "engine/Assert.h"

#include <exception>

void HandlePanic(SourceLocation location)
{
    throw std::runtime_error("Panic");
}
void HandlePanic(const std::string& message, SourceLocation location)
{
    throw std::runtime_error(std::format("Panic: {}", message));
}

void HandleUnimplemented(SourceLocation location)
{
    throw std::runtime_error("Unimplemented");
}
void HandleUnimplemented(const std::string& message, SourceLocation location)
{
    throw std::runtime_error(std::format("Unimplemented: {}", message));
}

void HandleUnreachable(SourceLocation location)
{
    throw std::runtime_error("Unreachable");
}
void HandleUnreachable(const std::string& message, SourceLocation location)
{
    throw std::runtime_error(std::format("Unreachable: {}", message));
}

void HandleAssert(const std::string& expr, SourceLocation location)
{
    throw std::runtime_error(std::format("Assertion failed '{}'", expr));
}
void HandleAssert(const std::string& expr, const std::string& message, SourceLocation location)
{
    throw std::runtime_error(std::format("Assertion failed '{}': {}", expr, message));
}
