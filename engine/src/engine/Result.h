/**
 * @file
 * @brief Result type for error-handling
 * 
 * @details
 * Rust-inspired Result class for error-handling.
 */

#pragma once

#include "engine/BaseTypes.h"
#include "engine/BaseMacros.h"

#include "engine/Error.h"
#include "engine/Assert.h"

#include <variant>

/**
 * @brief Try to execute the resulting expression
 * 
 * @details
 * Usage Example:
 * @code{.cpp}
 * extern Result<void> AnotherResultingFn();
 * 
 * Result<void> SomeFn()
 * {
 *      E_TRY(AnotherResultingFn());
 *      return {};
 * }
 * @endcode
 */
#define E_TRY(EXPR) \
    if(auto __engine_result_type__res = EXPR; __engine_result_type__res.IsError()) \
        return __engine_result_type__res.UnwrapErr()

/**
 * @brief Try to execute the resulting expression and if it success save unwrapped result to variable.
 * 
 * @details
 * Usage Example:
 * @code{.cpp}
 * extern Result<int> AnotherResultingFn();
 * 
 * Result<int> SomeFn()
 * {
 *      E_LET_TRY(code, AnotherResultingFn());
 *      return code; // It returns `AnotherResultingFn()` result if it successfuly executed
 * }
 * @endcode
 */
#define E_LET_TRY(VAR, EXPR) \
    auto VAR##__engine_result_type__try_result__ = EXPR; \
    if(VAR##__engine_result_type__try_result__.IsError()) \
        return VAR##__engine_result_type__try_result__.UnwrapErr(); \
    auto VAR = VAR##__engine_result_type__try_result__.Unwrap()

/**
 * @brief Rust-like Result type
 *
 */
template<typename SuccessType, typename ErrorType = Error>
class [[nodiscard("Result value must be handled")]] Result
{
    static_assert(!std::is_same_v<SuccessType, ErrorType>, "SuccessType and ErrorType can't be same in Result class.");

public:
    E_FORCE_INLINE
    inline constexpr Result(const SuccessType& value)
        requires (std::is_copy_assignable_v<SuccessType>)
        : m_value(value)
    {
    }

    E_FORCE_INLINE
    inline constexpr Result(const ErrorType& value)
        requires (std::is_copy_assignable_v<ErrorType>)
        : m_value(value)
    {
    }

    E_FORCE_INLINE
    inline constexpr Result(SuccessType&& value)
        requires ((!std::is_copy_assignable_v<SuccessType>) && std::is_move_assignable_v<SuccessType>)
        : m_value(std::move(value))
    {
    }

    E_FORCE_INLINE
    inline constexpr Result(ErrorType&& value)
        requires ((!std::is_copy_assignable_v<ErrorType>) && std::is_move_assignable_v<ErrorType>)
        : m_value(std::move(value))
    {
    }

    [[nodiscard]]
    bool IsSuccess() const noexcept
    {
        return std::holds_alternative<SuccessType>(m_value);
    }

    [[nodiscard]]
    bool IsError() const noexcept
    {
        return std::holds_alternative<ErrorType>(m_value);
    }

    explicit operator bool() const noexcept
    {
        return IsSuccess();
    }

    [[nodiscard]]
    SuccessType Unwrap(SourceLocation location = SourceLocation::Current()) const
        requires (std::is_copy_assignable_v<SuccessType>)
    {
        try {
            return std::get<SuccessType>(m_value);
        } catch ([[maybe_unused]] const std::bad_variant_access& ex) {
            HandlePanic(std::format("Unwrap on error value:\n{}", UnwrapErr()), location);
        }
    }

    [[nodiscard]]
    SuccessType Unwrap(SourceLocation location = SourceLocation::Current()) const
        requires ((!std::is_copy_assignable_v<SuccessType>) && std::is_move_assignable_v<SuccessType>)
    {
        try {
            SuccessType res = std::move(std::get<SuccessType>(m_value));
            m_value = std::monostate{};
            return res;
        } catch ([[maybe_unused]] const std::bad_variant_access& ex) {
            HandlePanic(std::format("Unwrap on error value:\n{}", UnwrapErr()), location);
        }
    }

    [[nodiscard]]
    ErrorType UnwrapErr(SourceLocation location = SourceLocation::Current()) const
        requires (std::is_copy_assignable_v<ErrorType>)
    {
        try {
            return std::get<ErrorType>(m_value);
        } catch ([[maybe_unused]] const std::bad_variant_access& ex) {
            HandlePanic("UnwrapErr on success value", location);
        }
    }

    [[nodiscard]]
    ErrorType UnwrapErr(SourceLocation location = SourceLocation::Current()) const
        requires ((!std::is_copy_assignable_v<ErrorType>) && std::is_move_assignable_v<ErrorType>)
    {
        try {
            ErrorType res = std::move(std::get<ErrorType>(m_value));
            m_value = std::monostate{};
            return res;
        } catch ([[maybe_unused]] const std::bad_variant_access& ex) {
            HandlePanic("UnwrapErr on success value", location);
        }
    }

private:
    mutable std::variant<SuccessType, ErrorType, std::monostate> m_value;
};

template<typename ErrorType>
class [[nodiscard("Result value must be handled")]] Result<void, ErrorType>
{
public:
    E_FORCE_INLINE
    inline constexpr Result(void)
        : m_value(std::monostate{})
    {
    }

    E_FORCE_INLINE
    inline constexpr Result(const ErrorType& value)
        requires (std::is_copy_assignable_v<ErrorType>)
        : m_value(value)
    {
    }

    E_FORCE_INLINE
    inline constexpr Result(ErrorType&& value)
        requires ((!std::is_copy_assignable_v<ErrorType>) && std::is_move_assignable_v<ErrorType>)
        : m_value(std::move(value))
    {
    }

    [[nodiscard]]
    bool IsSuccess() const noexcept
    {
        return !std::holds_alternative<ErrorType>(m_value);
    }

    [[nodiscard]]
    bool IsError() const noexcept
    {
        return std::holds_alternative<ErrorType>(m_value);
    }

    explicit operator bool() const noexcept
    {
        return IsSuccess();
    }

    void Unwrap(SourceLocation location = SourceLocation::Current()) const
    {
        if(IsError())
            HandlePanic(std::format("Unwrap on error value:\n{}", UnwrapErr()), location);
    }

    [[nodiscard]]
    ErrorType UnwrapErr(SourceLocation location = SourceLocation::Current()) const
        requires (std::is_copy_assignable_v<ErrorType>)
    {
        try {
            return std::get<ErrorType>(m_value);
        } catch ([[maybe_unused]] const std::bad_variant_access& ex) {
            HandlePanic("UnwrapErr on success value", location);
        }
    }

    [[nodiscard]]
    ErrorType UnwrapErr(SourceLocation location = SourceLocation::Current()) const
        requires ((!std::is_copy_assignable_v<ErrorType>) && std::is_move_assignable_v<ErrorType>)
    {
        try {
            ErrorType res = std::move(std::get<ErrorType>(m_value));
            m_value = std::monostate{};
            return res;
        } catch ([[maybe_unused]] const std::bad_variant_access& ex) {
            HandlePanic("UnwrapErr on success value", location);
        }
    }

private:
    mutable std::variant<ErrorType, std::monostate> m_value;
};