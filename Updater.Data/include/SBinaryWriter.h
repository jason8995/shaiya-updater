#pragma once
#include <fstream>
#include <string>

namespace Updater::Data
{
    class SBinaryWriter
    {
    public:

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
