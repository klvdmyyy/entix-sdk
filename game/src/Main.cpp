#include <engine/EntryPoint.h>

#include <engine/io/FileStream.h>

#include <engine/serialization/Archive.h>

int EngineMain(
    [[maybe_unused]] int argc,
    [[maybe_unused]] char** argv
)
{
    io::FileStream myFile("helloworld.txt", io::StreamMode::Write);

    std::string myFileText = std::filesystem::current_path().string();

    myFile.Write(io::ConstByteSpan{reinterpret_cast<const io::Byte*>(myFileText.data()), myFileText.size()});

    return 0;
}