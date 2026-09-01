#pragma once

#include "engine/BaseMacros.h"
#include "engine/Hash.h"

#include <cstdint>
#include <cstddef>

#include <type_traits>
#include <tuple>

/**
 * @brief Defines Id type from template.
 *
 * @details
 * Creates a empty tag structure and defines Id type with following template parameters:
 * `Id<Usize, TAG_STRUCTURE>`
 *
 * @param[in] NAME You Id type name. Tag structure are named as `NAME##Tag`
 */
#define E_DEFINE_ID_TYPE(NAME) \
    struct NAME##Tag {}; \
    using NAME = ::Id<::Usize, NAME##Tag>

using Int8 = std::int8_t;
using Int16 = std::int16_t;
using Int32 = std::int32_t;
using Int64 = std::int64_t;

using Uint8 = std::uint8_t;
using Uint16 = std::uint16_t;
using Uint32 = std::uint32_t;
using Uint64 = std::uint64_t;

using Usize = std::size_t;

/**
 * @brief Simple version class
 */
class Version
{
public:
    constexpr Version(Uint32 major, Uint32 minor, Uint32 patch)
        : m_major(major),
          m_minor(minor),
          m_patch(patch)
    {
    }

    E_FORCE_INLINE
    [[nodiscard]]
    inline constexpr Uint32 GetMajor() const noexcept
    {
        return m_major;
    }

    E_FORCE_INLINE
    [[nodiscard]]
    inline constexpr Uint32 GetMinor() const noexcept
    {
        return m_minor;
    }

    E_FORCE_INLINE
    [[nodiscard]]
    inline constexpr Uint32 GetPatch() const noexcept
    {
        return m_minor;
    }

    E_FORCE_INLINE
    [[nodiscard]]
    inline Usize GetHash() const noexcept
    {
        Usize seed = 0;
        HashCombine(seed, m_major, m_minor, m_patch);
        return seed;
    }

    E_FORCE_INLINE
    [[nodiscard]]
    bool operator==(const Version& other) const noexcept
    {
        return GetMajor() == other.GetMajor()
            && GetMinor() == other.GetMinor()
            && GetPatch() == other.GetPatch();
    }

    E_FORCE_INLINE
    [[nodiscard]]
    bool operator>(const Version& other) const noexcept
    {
        return GetMajor() > other.GetMajor()
            || GetMinor() > other.GetMinor()
            || GetPatch() > other.GetPatch();
    }

    E_FORCE_INLINE
    [[nodiscard]]
    bool operator>=(const Version& other) const noexcept
    {
        return *this == other || *this > other;
    }

    E_FORCE_INLINE
    [[nodiscard]]
    bool operator<(const Version& other) const noexcept
    {
        return GetMajor() < other.GetMajor()
            || GetMinor() < other.GetMinor()
            || GetPatch() < other.GetPatch();
    }

    E_FORCE_INLINE
    [[nodiscard]]
    bool operator<=(const Version& other) const noexcept
    {
        return *this == other || *this < other;
    }

private:
    Uint32 m_major;
    Uint32 m_minor;
    Uint32 m_patch;
};

/**
 * @brief Id template type.
 *
 * @tparam T Id unsigned integer type (std::is_unsigned_v<T> is required)
 * @tparam Tag For different Id types. Tag must be empty structure (std::is_empty_v<Tag> is required)
 * 
 * @details
 * Usage example:
 * @code{.cpp}
 * struct MyIdTag {};
 * struct MyIdTag2 {};
 *
 * void IdTest()
 * {
 *      Id<Usize, MyIdTag> myId = 10;
 *      Id<Usize, MyIdTag2> myId2 = 10;
 *
 *      // This is error. You can't compare different Id types implicitly
 *      if(myId == myId2)
 *      {
 *          // Do something...
 *      }
 *
 *      // Following convertion are acceptable.
 *      //
 *      // Convertion are available when Id type
 *      // are convertable or the same (std::is_convertible_v || std::is_same_v)
 *      if(myId == (Id<Usize, MyIdTag>)myId2)
 *      {
 *          // Do something...
 *      }
 * }
 * @endcode
 *
 * Following code doing the same but with macro:
 * @code{.cpp}
 * E_DEFINE_ID_TYPE(MyId);
 * E_DEFINE_ID_TYPE(MyId2);
 *
 * void IdTest()
 * {
 *      MyId myId = 10;
 *      MyId2 myId2 = 10;
 *
 *      // This is error. You can't compare different Id types implicitly
 *      if(myId == myId2)
 *      {
 *          // Do something...
 *      }
 *
 *      // Following convertion are acceptable.
 *      //
 *      // Convertion are available when Id type
 *      // are convertable or the same (std::is_convertible_v || std::is_same_v)
 *      if(myId == (MyId)myId2)
 *      {
 *          // Do something...
 *      }
 * }
 * @endcode
 */
template<typename T, typename Tag>
    requires (std::is_trivial_v<T> && std::is_unsigned_v<T> && std::is_empty_v<Tag>)
class Id {
public:
    inline constexpr Id(T value)
        : m_value(value)
    {
    }

    inline constexpr T Get() const noexcept { return m_value; }

    inline T& operator*() noexcept
    {
        return m_value;
    }

    inline bool operator==(const Id<T, Tag>& other) const noexcept
    {
        return m_value == other.m_value;
    }

    inline bool operator!=(const Id<T, Tag>& other) const noexcept
    {
        return !(*this == other);
    }

    template<typename OtherT, typename OtherTag>
        requires (std::is_same_v<T, OtherT> || std::is_convertible_v<T, OtherT>)
    inline explicit operator Id<OtherT, OtherTag>() const noexcept
    {
        return Id<OtherT, OtherTag>(static_cast<OtherT>(m_value));
    }

    /**
     * @brief Hasher struct for Id type.
     *
     * @details
     * Usage example:
     * @code{.cpp}
     * // Type definitions
     * EX_DEFINE_ID_TYPE(PlayerId);
     * struct Player {};
     *
     * // Somewhere in your class or function
     * std::unordered_map<PlayerId, Player, PlayerId::Hasher> players;
     * @endcode
     */
    struct Hasher
    {
        Usize operator()(const Id<T, Tag>& id)
        {
            return std::hash<T>{}(id.m_value);
        }
    };

private:
    T m_value;
};