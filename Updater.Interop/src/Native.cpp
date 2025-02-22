#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <Updater.Data/include/Convert.h>
#include <Updater.Data/include/Data.h>
#include <Updater.Data/include/Saf.h>
#include <Updater.Data/include/Sah.h>
#include <Updater.Data/include/SFile.h>
#include <Updater.Data/include/SFolder.h>
#include "include/Native.h"
using namespace Updater::Data;

void Native::DataBuilder(const wchar_t* sahPath, const wchar_t* safPath, const void(*progressCallback)())
{
    auto saf = std::make_unique<Saf>(safPath);
    auto sah = std::make_unique<Sah>(sahPath);
    sah->read();

    auto data = std::make_unique<Data>(sahPath, safPath);
    data->sah->path += ".bak";
    data->saf->path += ".bak";
    std::filesystem::rename(sahPath, data->sah->path);
    std::filesystem::rename(safPath, data->saf->path);

    auto writeFolder = [&](const auto& self, const auto& currentFolder) -> void {
        for (auto& [name, file] : currentFolder->files)
        {
            std::vector<char> buffer(file->length);
            if (data->saf->readFile(file->offset, buffer))
                throw std::runtime_error::exception();

            auto offset = saf->writeFile(buffer);
            if (offset == -1)
                throw std::runtime_error::exception();

            file->offset = offset;

            if (progressCallback)
                progressCallback();
        }

        for (const auto& [name, subfolder] : currentFolder->subfolders)
            self(self, subfolder);
    };

    writeFolder(writeFolder, sah->rootFolder);
    sah->write();
    std::filesystem::remove(data->sah->path);
    std::filesystem::remove(data->saf->path);
}

void Native::DataPatcher(
    const wchar_t* targetSahPath, 
    const wchar_t* targetSafPath, 
    const wchar_t* updateSahPath, 
    const wchar_t* updateSafPath, 
    const void(*progressCallback)()
)
{
    auto target = std::make_unique<Data>(targetSahPath, targetSafPath);
    target->sah->read();

    auto update = std::make_unique<Data>(updateSahPath, updateSafPath);
    update->sah->read();

    for (const auto& [path, patch] : update->sah->files)
    {
        if (auto it = target->sah->files.find(path); it != target->sah->files.end())
        {
            auto& file = it->second;
            if (patch->length > file->length)
            {
                std::vector<char> buffer(patch->length);
                if (update->saf->readFile(patch->offset, buffer))
                    throw std::runtime_error::exception();

                auto offset = target->saf->writeFile(buffer);
                if (offset == -1)
                    throw std::runtime_error::exception();

                target->saf->eraseFile(file->offset, file->length);
                file->offset = offset;
                file->length = patch->length;
            }
            else
            {
                std::vector<char> buffer(patch->length);
                if (update->saf->readFile(patch->offset, buffer))
                    throw std::runtime_error::exception();

                target->saf->eraseFile(file->offset, file->length);
                if (target->saf->writeFile(file->offset, buffer))
                    throw std::runtime_error::exception();

                file->length = patch->length;
            }
        }
        else
        {
            std::vector<char> buffer(patch->length);
            if (update->saf->readFile(patch->offset, buffer))
                throw std::runtime_error::exception();

            auto offset = target->saf->writeFile(buffer);
            if (offset == -1)
                throw std::runtime_error::exception();

            patch->offset = offset;
            auto parentFolder = target->sah->ensureFolderExists(patch->parentFolder->path);
            parentFolder->files.insert({ patch->name, patch });

            target->sah->files.insert({ patch->path, patch });
            target->sah->fileCount = Convert::toInt32(target->sah->files.size());
        }

        if (progressCallback)
            progressCallback();
    }

    target->sah->write();
}

int Native::GetSahFileCount(const wchar_t* sahPath)
{
    auto sah = std::make_unique<Sah>(sahPath);
    sah->read();
    return sah->fileCount;
}

void Native::RemoveFiles(const wchar_t* sahPath, const wchar_t* safPath, const wchar_t* lstPath, const void(*progressCallback)())
{
    std::ifstream list(lstPath);
    if (!list)
        return;

    std::vector<std::filesystem::path> paths;
    std::string line;

    while (std::getline(list, line))
    {
        std::filesystem::path path(line);
        paths.push_back(path.make_preferred());
    }

    list.close();
    if (paths.empty())
        return;

    auto data = std::make_unique<Data>(sahPath, safPath);
    data->sah->read();

    for (const auto& path : paths)
    {
        if (auto it = data->sah->files.find(path); it != data->sah->files.end())
        {
            auto& file = it->second;
            file->parentFolder->files.erase(file->name);

            data->saf->eraseFile(file->offset, file->length);
            data->sah->files.erase(it);
            data->sah->fileCount = Convert::toInt32(data->sah->files.size());
        }

        if (progressCallback)
            progressCallback();
    }

    data->sah->write();
}
