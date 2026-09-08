#pragma once

#include "engine/io/Stream.h"

#include <filesystem>
#include <fstream>

namespace io
{
    class FileStream : public Stream
    {
    public:
        ENGINE_API FileStream(const std::filesystem::path& path, StreamMode mode);
        ENGINE_API ~FileStream();

        ENGINE_API Result<void> Write(ConstByteSpan src) override;
        ENGINE_API void Flush() override { m_file.flush(); }

        ENGINE_API Result<void> Read(ByteSpan dest);
        ENGINE_API Result<void> Seek(Int64 offset, SeekOrigin origin) override;
        ENGINE_API Usize Tell() const override { return m_exists ? static_cast<Usize>(m_file.tellg()) : (Usize)0U; }
        ENGINE_API Usize Size() const override { return m_size; }

        ENGINE_API StreamMode GetStreamMode() const noexcept override { return k_mode; }

        // Virtual for maybe future classes which are based on FileStream
        ENGINE_API virtual bool Exists() const noexcept { return m_exists; }

    private:
        const StreamMode k_mode;
        const std::filesystem::path k_path;

        bool m_exists = false;
        Usize m_size = 0;

        mutable std::fstream m_file;
    };
}