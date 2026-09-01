#include "engine/Error.h"

std::string Error::What() const noexcept
{
    return std::format(
        "{}({}:{}): {}",
        m_location.GetFileName().string(),
        m_location.GetLine(),
        m_location.GetColumn(),
        GetMessage()
    );
}