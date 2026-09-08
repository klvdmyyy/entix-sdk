#include <engine/EntryPoint.h>

#include <engine/Application.h>

class GameLayer
{
public:
    GameLayer();
};

Result<void> EngineMain(
    [[maybe_unused]] int argc,
    [[maybe_unused]] char** argv
)
{
    return Application()
        .LoadPlugin("engine/rhi-opengl")
        .LoadPlugin("engine/rhi-d3d11")
        .LoadPlugin("engine/audio-sdl3")
        .LoadPlugin("engine/client-server")
        .LoadPlugin("engine/client-server-gns")
        .LoadPlugin("engine/entix-gui")
        .PushLayer<GameLayer>()
        .Run();
}