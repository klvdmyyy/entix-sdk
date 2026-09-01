#pragma once

#include "engine/io/Stream.h"

namespace io
{
    /**
     * @brief Base stream class for networking
     * 
     * @details For client-server communication in game
     * use GNSStream (NetworkStream implementation on top of Valve's GameNetworkingSockets).
     */
    class NetworkStream
    {
    public:
        virtual ~NetworkStream() = default;

        virtual Result<void> Connect(const std::string& address, Uint16 port) = 0;
        virtual Result<void> Disconnect() = 0;
        virtual bool IsConnected() const noexcept = 0;
        virtual bool HasData() const noexcept = 0;
    };
}