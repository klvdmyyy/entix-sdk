/**
 * @file
 * @brief Error base class.
 */

#pragma once

#include "engine/BaseTypes.h"
#include "engine/BaseMacros.h"

#include "engine/Assert.h"

#include <ranges>
#include <sstream>
#include <format>

/**
 * @brief Error base class
 * 
 * @details
 * Mainly implemented for using in Result class. You can also
 * use it for throw/try/catch statements.
 */
class Error
{
public:
    Error(const std::string& message, SourceLocation location = SourceLocation::Current())
        : m_message(message), m_location(location)
    {
    }
    virtual ~Error() = default;

    /**
     * @brief Says what's wrong =)
     * 
     * @return String Formatter error message
     */
    ENGINE_API virtual std::string What() const noexcept;
    
    /**
     * @brief Just return raw error message
     * 
     * @return StringView
     */
    const std::string& GetMessage() const noexcept
    {
        return m_message;
    }

protected:
    std::string m_message;
    SourceLocation m_location;
};

/**
 * @ingroup Core
 */
template<>
struct std::formatter<Error, char>
{
    template<typename ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        return it;
    }

    template<typename FmtContext>
    FmtContext::iterator format(Error err, FmtContext& ctx) const
    {
        std::ostringstream out;
        out << err.What();

        return std::ranges::copy(std::move(out).str(), ctx.out()).out;
    }
};