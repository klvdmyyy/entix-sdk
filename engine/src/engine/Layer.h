#pragma once

#include "engine/BaseMacros.h"

#include <string>

class Layer
{
public:
    Layer(const std::string& debugName)
        : k_debugName(debugName)
    {
    }
    virtual ~Layer() = default;

    E_FORCE_INLINE
    [[nodiscard]]
    inline const std::string& GetDebugName() const noexcept
    {
        return k_debugName;
    }

    virtual void OnAttach() { }
    virtual void OnDetach() { }

    virtual void OnTick([[maybe_unused]] unsigned int ticks) { }

private:
    const std::string k_debugName;
};