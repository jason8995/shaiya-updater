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

        /// <summary>
        /// Compares two paths, ignoring case.
        /// </summary>
        static int icompare(const Path::string_type& lhs, const Path::string_type& rhs, const std::locale& loc = std::locale())
        {
            auto result = std::lexicographical_compare_three_way(
                lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(), [&loc](Path::value_type lc, Path::value_type rc) {
                    return std::toupper<Path::value_type>(lc, loc) <=> std::toupper<Path::value_type>(rc, loc);
                });

            return std::is_lt(result) ? -1 : std::is_gt(result) ? 1 : 0;
        }
    };

    /// <summary>
    /// A case-insensitive less than comparator.
    /// </summary>
    struct PathICompareLT : private PathHelper
    {
        bool operator()(const Path& lhs, const Path& rhs) const
        {
            return icompare(lhs, rhs) < 0;
        }
    };
}
