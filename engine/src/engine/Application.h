#pragma once

#include "engine/PluginManager.h"

class Application
{
public:
    Application();
    ~Application();

    template<typename T>
    Application& PushOverlay() { }

    template<typename T>
    Application& PushLayer() { }

    ENGINE_API Application& LoadPlugin(const std::string& pathToPlugin);

    [[nodiscard]]
    ENGINE_API Result<void> Run();

private:
    PluginManager m_pluginManager;
};