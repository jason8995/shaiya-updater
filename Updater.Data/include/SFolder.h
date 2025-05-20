#pragma once
#include <filesystem>
#include <map>
#include <memory>
#include "PathHelper.h"
#include "PathILexicographicalCompare.h"

namespace Updater::Data
{
    class SFile;

    class SFolder final
    {
    public:

        std::filesystem::path path;
        std::filesystem::path name;
        std::shared_ptr<SFolder> parentFolder;

        std::map<std::filesystem::path, std::shared_ptr<SFile>, PathILexicographicalCompare> files;
        std::map<std::filesystem::path, std::shared_ptr<SFolder>, PathILexicographicalCompare> subfolders;

        /// <summary>
        /// Initializes a new instance of the SFolder class.
        /// </summary>
        SFolder(const std::filesystem::path& name, const std::shared_ptr<SFolder>& parentFolder = nullptr)
            : name(name), parentFolder(parentFolder)
        {
            if (!parentFolder)
                path = name;
            else
                path = PathHelper::combine(parentFolder->path, name);
        }
    };
}
