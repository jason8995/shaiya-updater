#pragma once
#include <fstream>
#include <string>

namespace Updater::Data
{
    class StreamHelper
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

        /// <summary>
        /// Writes a section of a string to the stream.
        /// </summary>
        static void writeChars(std::ofstream& stream, const std::string& value, size_t index, size_t count)
        {
            if ((index + count) > value.length())
                throw std::invalid_argument::exception();

            stream.write(&value[index], count);
        }

        /// <summary>
        /// Writes an integer to the stream.
        /// </summary>
        template<class IntT, class = std::enable_if_t<std::is_integral_v<IntT>>>
        static void writeInt(std::ofstream& stream, IntT value)
        {
            stream.write(reinterpret_cast<char*>(&value), sizeof(IntT));
        }

        /// <summary>
        /// Writes a length-prefixed null-terminated string to the stream.
        /// </summary>
        template<class LengthT>
        static void writeString(std::ofstream& stream, const std::string& value)
        {
            auto length = static_cast<LengthT>(value.length() + 1);
            stream.write(reinterpret_cast<char*>(&length), sizeof(LengthT));
            stream.write(value.c_str(), length);
        }
    };
}
