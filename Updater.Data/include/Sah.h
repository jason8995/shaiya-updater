#pragma once
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include "PathHelper.h"
#include "StreamHelper.h"

namespace Updater::Data
{
    class SFile;
    class SFolder;

    class Sah final : StreamHelper
    {
    public:

        std::filesystem::path path;
        std::string signature;
        int32_t unknown; // to-do
        int32_t fileCount;
        std::shared_ptr<SFolder> rootFolder;

        std::map<std::filesystem::path, std::shared_ptr<SFile>, PathICompareLT> files;
        std::map<std::filesystem::path, std::shared_ptr<SFolder>, PathICompareLT> folders;

        /// <summary>
        /// Initializes a new instance of the Sah class.
        /// </summary>
        Sah(const std::filesystem::path& path)
            : path(path), signature("SAH"), unknown(0), fileCount(0), rootFolder(nullptr)
        {
        }

        /// <summary>
        /// Ensures each folder in the specified path exists. If the specified path already 
        /// exists, the last folder is returned. Otherwise, each folder that does not exist 
        /// is created, and then the last folder is returned.
        /// </summary>
        std::shared_ptr<SFolder> ensureFolderExists(const std::filesystem::path& path);

        /// <summary>
        /// 
        /// </summary>
        void read();

        /// <summary>
        /// 
        /// </summary>
        void write();

    public:

        Sah(const Sah&) = delete;
        Sah& operator=(const Sah&) = delete;
    };
}
