#pragma once
#include <filesystem>
#include <vector>

namespace Updater::Data
{
    class PathHelper
    {
    public:

        using Path = std::filesystem::path;

        /// <summary>
        /// Combines two paths into a path.
        /// </summary>
        static Path combine(const Path& lhs, const Path& rhs)
        {
            return lhs / rhs;
        }

        /// <summary>
        /// Splits a path into components based on directory separators.
        /// </summary>
        static std::vector<Path> split(const Path& path)
        {
            std::vector<Path> parts;
            for (const auto& part : path)
                parts.push_back(part);

            return parts;
        }
    };
}
