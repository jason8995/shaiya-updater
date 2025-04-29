#pragma once
#include <fstream>
#include <string>

namespace Updater::Data
{
    class SBinaryReader
    {
    public:

        /// <summary>
        /// Reads the specified number of characters from the stream.
        /// </summary>
        static std::string readChars(std::ifstream& stream, size_t count)
        {
            std::string buffer(count, 0);
            stream.read(buffer.data(), buffer.size());
            return buffer;
        }

        /// <summary>
        /// Reads an integer from the stream.
        /// </summary>
        template<class IntT, class = std::enable_if_t<std::is_integral_v<IntT>>>
        static IntT readInt(std::ifstream& stream)
        {
            IntT buffer{};
            stream.read(reinterpret_cast<char*>(&buffer), sizeof(IntT));
            return buffer;
        }

        /// <summary>
        /// Reads a length-prefixed string from the stream.
        /// </summary>
        template<class LengthT>
        static std::string readString(std::ifstream& stream)
        {
            LengthT length{};
            stream.read(reinterpret_cast<char*>(&length), sizeof(LengthT));

            std::string buffer(length, 0);
            stream.read(buffer.data(), buffer.size());
            return buffer;
        }
    };
}
