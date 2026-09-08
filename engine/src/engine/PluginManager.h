#pragma once

#include "engine/BaseTypes.h"

#include "engine/Result.h"

#include <type_traits>

class Plugin
{
private:
    friend class PluginManager;

    static Result<Plugin*> Load(const std::filesystem::path& path);
};

namespace internal
{
    struct PluginIndex
    {
        E_FORCE_INLINE
        [[nodiscard]]
        inline static Usize Get() noexcept
        {
            static Usize nextValue = 0;
            return nextValue++;
        }
    };
}

template<std::derived_from<Plugin> T>
struct PluginIndex
{
    E_FORCE_INLINE
    [[nodiscard]]
    inline static Usize Get() noexcept
    {
        static const Usize value = internal::PluginIndex::Get();
        return value;
    }
};

/**
 * @brief Class which manage plugins for your application.
 * 
 * @details
 * Loading plugin as raw pointers and wraps it into std::shared_ptr.
 */
class PluginManager
{
public:
    template<std::derived_from<Plugin> T>
    bool IsLoaded()
    {
        auto pluginIndex = PluginIndex<T>::Get();
        return m_plugins.contains(pluginIndex)
            && m_plugins.at(pluginIndex) != nullptr;
    }

    template<std::derived_from<Plugin> T>
    Result<void> Load(const std::filesystem::path& pluginPath)
    {
        E_ASSERT(!IsLoaded<T>());
        auto pluginIndex = PluginIndex<T>::Get();

        E_LET_TRY(plugin, Plugin::Load(pluginPath));

        m_plugins[pluginIndex] = std::shared_ptr(plugin);

        return {};
    }

    /**
     * @brief Getting your plugin!
     * 
     * @warning
     * It uses std::dynamic_pointer_cast which usually has overhead. Use it
     * only ones in your class constructor to get necessary plugins.
     * 
     * Using it in main loop can slow down your application!
     */
    template<std::derived_from<Plugin> T>
    std::shared_ptr<T> Get()
    {
        E_ASSERT(IsLoaded<T>());
        auto pluginIndex = PluginIndex<T>::Get();

        auto plugin = std::dynamic_pointer_cast<T>(m_plugins.at(pluginIndex));
        E_ASSERT(plugin != nullptr);

        return plugin;
    }

private:
    std::unordered_map<Usize, std::shared_ptr<Plugin>> m_plugins;
};