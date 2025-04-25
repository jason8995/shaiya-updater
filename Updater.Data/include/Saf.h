#pragma once
#include <filesystem>
#include <vector>

namespace Updater::Data
{
    class Saf final
    {
    public:

        std::filesystem::path path;

        /// <summary>
        /// Initializes a new instance of the Saf class.
        /// </summary>
        Saf(const std::filesystem::path& path)
            : path(path)
        {
        }

        /// <summary>
        /// Opens the archive, overwrites file data with zeros, and then closes the archive.
        /// </summary>
        int eraseFile(int64_t offset, int32_t length) const;

        /// <summary>
        /// Opens the archive, reads file data from the archive into the specified buffer, and then closes the archive.
        /// </summary>
        int readFile(int64_t offset, std::vector<char>& output) const;

        /// <summary>
        /// Opens the archive, writes file data from the specified buffer to the end of the archive, and then closes the archive. 
        /// If an exception is caught, this method returns -1.
        /// </summary>
        int64_t writeFile(const std::vector<char>& buffer) const;

        /// <summary>
        /// Opens the archive, writes file data from the specified buffer to the archive, and then closes the archive.
        /// </summary>
        int writeFile(int64_t offset, const std::vector<char>& buffer) const;

    public:

        Saf(const Saf&) = delete;
        Saf& operator=(const Saf&) = delete;
    };
}
