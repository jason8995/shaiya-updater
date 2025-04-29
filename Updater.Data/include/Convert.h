#pragma once
#include <cstdint>
#include <limits>
#include <stdexcept>

namespace Updater::Data
{
    class Convert final
    {
    public:

        /// <summary>
        /// Converts the specified size_t value to a 32-bit signed integer.
        /// </summary>
        static int32_t toInt32(size_t value)
        {
            if (value > std::numeric_limits<int32_t>::max())
                throw std::overflow_error::exception();

            return static_cast<int32_t>(value);
        }

        /// <summary>
        /// Converts the specified size_t value to a 32-bit unsigned integer.
        /// </summary>
        static uint32_t toUInt32(size_t value)
        {
            if (value > std::numeric_limits<uint32_t>::max())
                throw std::overflow_error::exception();

            return static_cast<uint32_t>(value);
        }
    };
}
