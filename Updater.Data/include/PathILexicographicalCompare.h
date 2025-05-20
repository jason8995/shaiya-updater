#pragma once
#include <algorithm>
#include <filesystem>
#include <locale>

namespace Updater::Data
{
    struct PathILexicographicalCompare
    {
        using Path = std::filesystem::path;

        bool operator()(const Path::string_type& lhs, const Path::string_type& rhs) const
        {
            return std::lexicographical_compare(
                lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(), [](Path::value_type lc, Path::value_type rc) {
                    return std::toupper<Path::value_type>(lc, std::locale()) < std::toupper<Path::value_type>(rc, std::locale());
                });
        }
    };
}
