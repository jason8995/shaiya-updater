#pragma once
#include <algorithm>
#include <filesystem>
#include <locale>
#include <string>
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
        /// <param name="lhs"></param>
        /// <param name="rhs"></param>
        /// <returns>See std::filesystem::operator/ docs.</returns>
        static Path combine(const Path& lhs, const Path& rhs)
        {
            return lhs / rhs;
        }

        /// <summary>
        /// Splits a path into components based on directory separators.
        /// </summary>
        /// <param name="path"></param>
        /// <returns>A vector containing the components delimited by directory separators.</returns>
        static std::vector<Path> split(const Path& path)
        {
            std::vector<Path> parts;
            for (const auto& part : path)
                parts.push_back(part);

            return parts;
        }

        /// <summary>
        /// Returns a copy of the specified path converted to lowercase.
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        static Path toLower(const Path& path, const std::locale& loc = std::locale())
        {
            Path::string_type text = path.native();
            std::transform(text.begin(), text.end(), text.begin(), [&loc](auto c) {
                return std::tolower(c, loc);
                });

            return text;
        }

        /// <summary>
        /// Returns a copy of the specified path converted to uppercase.
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        static Path toUpper(const Path& path, const std::locale& loc = std::locale())
        {
            Path::string_type text = path.native();
            std::transform(text.begin(), text.end(), text.begin(), [&loc](auto c) {
                return std::toupper(c, loc);
                });

            return text;
        }
    };

    struct PathToLowerCompare : private PathHelper
    {
        bool operator()(const Path& lhs, const Path& rhs) const
        {
            return toLower(lhs).compare(toLower(rhs)) < 0;
        }
    };

    struct PathToUpperCompare : private PathHelper
    {
        bool operator()(const Path& lhs, const Path& rhs) const
        {
            return toUpper(lhs).compare(toUpper(rhs)) < 0;
        }
    };
}
