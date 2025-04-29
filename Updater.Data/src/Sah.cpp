#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "include/Convert.h"
#include "include/PathHelper.h"
#include "include/Sah.h"
#include "include/SBinaryReader.h"
#include "include/SBinaryWriter.h"
#include "include/SFile.h"
#include "include/SFolder.h"
using namespace Updater::Data;

std::shared_ptr<SFolder> Sah::ensureFolderExists(const std::filesystem::path& path)
{
    if (auto it = folders.find(path); it != folders.end())
        return it->second;

    std::shared_ptr<SFolder> currentFolder = rootFolder;

    auto parts = PathHelper::split(path);
    for (const auto& part : parts)
    {
        auto& subfolders = currentFolder->subfolders;
        if (auto it = subfolders.find(part); it != subfolders.end())
        {
            currentFolder = it->second;
        }
        else
        {
            auto subfolder = std::make_shared<SFolder>(part, currentFolder);
            subfolders.insert({ subfolder->name, subfolder });
            folders.insert({ subfolder->path, subfolder });
            currentFolder = subfolder;
        }
    }

    return currentFolder;
}

void Sah::read()
{
    std::ifstream stream(path, std::ios::binary);
    if (!stream)
        throw std::exception();

    signature = readChars(stream, 3);
    unknown = readInt<int32_t>(stream);
    fileCount = readInt<int32_t>(stream);
    stream.ignore(40);

    auto rootFolderName = readString<uint32_t>(stream);
    rootFolderName.pop_back();
    rootFolder = std::make_shared<SFolder>(rootFolderName);

    auto readFolder = [this, &stream](const auto& self, auto& currentFolder) -> void {
        folders.insert({ currentFolder->path, currentFolder });

        auto fileCount = readInt<int32_t>(stream);
        // Decrypt here (e.g., fileCount ^= 1234)
        for (int i = 0; i < fileCount; ++i)
        {
            auto fileName = readString<uint32_t>(stream);
            fileName.pop_back();

            auto file = std::make_shared<SFile>(fileName, currentFolder);
            file->offset = readInt<int64_t>(stream);
            file->length = readInt<int32_t>(stream);
            file->timestamp = readInt<int32_t>(stream);

            currentFolder->files.insert({ file->name, file });
            files.insert({ file->path, file });
        }

        auto subfolderCount = readInt<int32_t>(stream);
        for (int i = 0; i < subfolderCount; ++i)
        {
            auto subfolderName = readString<uint32_t>(stream);
            subfolderName.pop_back();

            auto subfolder = std::make_shared<SFolder>(subfolderName, currentFolder);
            self(self, subfolder);
            currentFolder->subfolders.insert({ subfolder->name, subfolder });
        }
    };

    readFolder(readFolder, rootFolder);
    fileCount = Convert::toInt32(files.size());
    stream.close();
}

void Sah::write()
{
    std::ofstream stream(path, std::ios::binary);
    if (!stream)
        throw std::exception();

    if (signature.size() != 3)
        signature.resize(3);

    writeChars(stream, signature, 0, 3);
    writeInt(stream, unknown);
    writeInt(stream, fileCount);
    writeChars(stream, std::string(40, 0), 0, 40);
    writeString<uint32_t>(stream, rootFolder->name.string());

    auto writeFolder = [this, &stream](const auto& self, const auto& currentFolder) -> void {
        auto fileCount = Convert::toInt32(currentFolder->files.size());
        // Encrypt here (e.g., fileCount ^= 1234)
        writeInt(stream, fileCount);

        for (const auto& [name, file] : currentFolder->files)
        {
            writeString<uint32_t>(stream, name.string());
            writeInt(stream, file->offset);
            writeInt(stream, file->length);
            writeInt(stream, file->timestamp);
        }

        auto subfolderCount = Convert::toInt32(currentFolder->subfolders.size());
        writeInt(stream, subfolderCount);

        for (const auto& [name, subfolder] : currentFolder->subfolders)
        {
            writeString<uint32_t>(stream, name.string());
            self(self, subfolder);
        }
    };

    writeFolder(writeFolder, rootFolder);
    writeInt<int32_t>(stream, 0);
    writeInt<int32_t>(stream, 0);
    stream.close();
}
