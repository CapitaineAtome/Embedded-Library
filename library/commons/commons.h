/**
 * @file commons.h
 * @brief Provide common functions to the API
 *
 * Here are implemented common functions that are used throughout the API.
 *
 * @note The following functions have to be implemented:
 * - @ref sleep_ms
 * - @ref sleep_us
 *
 * @warning If these functions aren't implemented a warning will be raised and they won't do anything !
 *
 */

#ifndef EMBEDDED_LIBRARY_COMMONS_H
#define EMBEDDED_LIBRARY_COMMONS_H

#include <cstdint>
#include <cstddef>
#include <sys/types.h>

#include "commons_concepts.h"

namespace hal {

    namespace peripherals {

        /**
	 	 * Hardware instances of uart, i2c, spi, ... peripherals
	 	 */
        enum HardwareInstance : uint8_t {

        }; // enum HardwareInstance

        enum DefaultPeripheralSettings {

            UART_DEFAULT_BAUD_RATE = 115'200U,      ///< uart default baud rate
            I2C_DEFAULT_BAUD_RATE = 400'000U,       ///< i2c default baud rate
            SPI_DEFAULT_BAUD_RATE = 50'000'000U,    ///< spi default baud rate

        }; // enum DefaultPeripheralSettings

    } // namespace peripherals

    enum class Error {

        Ok = 0,
        Error,

    }; // enum class Error

    /**
	 * Set a bit in a bitset.
	 *
     * @code
     * uint8_t bit_set{0};
     * uint8_t pos{4};\
     * set_bit(bit_set, pos);
     * 
     * // Result: bit_set == 0b00010000;
     * @endcode
     *
	 * @tparam T1 type of bit_set
	 * @tparam T2 type of pos
	 * @param bit_set the bit field to modify
	 * @param pos the position of the bit to set
	 */
    template<typename T1, typename T2>
    requires concepts::is_bitwiseable<T1> and concepts::is_bitwiseable<T2>
    inline void set_bit(T1 &bit_set, const T2 pos) {

        bit_set |= 1U << pos;
    }

    /**
	 * Clear a bit in a bitset.
     *
	 * @code
     * uint8_t bit_set{0xFF};
     * uint8_t pos{4};
     * clear_bit(bit_set, pos);
     * 
     * // Result: bit_set == 0b11101111;
     * @endcode
     *
	 * @tparam T1 type of bit_set. Must be bitwiseable
	 * @tparam T2 type os pos. Must be bitwiseable
	 * @param bit_set the bit field to modify
	 * @param pos the position of the bit to clear
	 */
    template<typename T1, typename T2>
    requires concepts::is_bitwiseable<T1> and concepts::is_bitwiseable<T2>
    inline void clear_bit(T1 &bit_set, const T2 pos) {

        bit_set &= ~(1U << pos);
    }

    /**
     * Toggle a bit in a bitset.
     * If the bit at position 'pos' in 'bit_field' == 0 it becomes 1
     * If the bit at position 'pos' in 'bit_field' == 1 it becomes 0
     *
     * @code
     * uint8_t bit_set{0};
     * uint8_t pos{4};
     * toggle_bit(bit_set, pos);
     * 
     * // Result: bit_set == 0b00010000;
     * @endcode
     *
     * @tparam T1 type of bit_set. Must be bitwiseable
     * @tparam T2 type of pos. Must be bitwiseable
     * @param bit_set the bit field to modify
     * @param pos the position of the bit to toggle
     */
    template<typename T1, typename T2>
    requires concepts::is_bitwiseable<T1> and concepts::is_bitwiseable<T2>
    inline void toggle_bit(T1 &bit_set, const T2 pos) {

        bit_set ^= 1U << pos;
    }

    /**
     * Check whether or not a bit is set.
     * A bit is set if it is equal to 1.
     *
     * @code
     * uint8_t bit_set{0};
     * uint8_t pos{4};
     * bool val{check_bit(bit_set, pos)};
     * 
     * // Result: val == true;
     * @endcode
     *
     * @tparam T1 type of bit_set. Must be bitwiseable
     * @tparam T2 type of pos. Must be bitwiseable
     * @param bit_set the bit field to check
     * @param pos the position of the bit to check
     * @return true if the bit is set, false otherwise
     */
    template<typename T1, typename T2>
    requires concepts::is_bitwiseable<T1> and concepts::is_bitwiseable<T2>
    inline bool check_bit(const T1 &bit_set, const T2 pos) {

        return (bit_set >> pos) & 1U;
    }

    /**
     * Set a bit to 1 at a given position.
     *
     * @code
     * uint8_t bit_set{0};
     * uint8_t pos{4};
     * uint8_t value{0b1111};
     * set_bits_pos(bit_set, pos, value);
     * 
     * // Result: bit_set == 0b11110000;
     * @endcode
     *
     * @tparam T1 type of bit_set. Must be bitwiseable
     * @tparam T2 type of pos. Must be bitwiseable
     * @tparam T3 type of value. Must be bitwiseable
     * @param bit_set the bit field to modify
     * @param pos the position on which to start
     * @param bit_mask the bitmask to set
     */
    template<typename T1, typename T2, typename T3>
    requires concepts::is_bitwiseable<T1> and concepts::is_bitwiseable<T2> and concepts::is_bitwiseable<T3>
    inline void set_bits_pos(T1 &bit_set, const T2 pos, const T3 bit_mask) {

        bit_set = (bit_set & (~(bit_mask << pos))) | (bit_mask<<pos);
    }

    /**
     * Set the bit mask in the bit set.
     *
     * @code
     * uint8_t bit_set{0};
     * uint8_t bit_mask{0b1111};
     * set_bits(bit_set, bit_mask);
     *
     * // Result: bit_set == 0b11110000;
     * @endcode
     *
     * @tparam T1 type of bit_set. Must be bitwiseable
     * @tparam T2 type of bit_mask. Must be bitwiseable
     * @param bit_set the bit field to modify
     * @param bit_mask the bit mask to check
     */
    template<typename T1, typename T2>
    requires concepts::is_bitwiseable<T1> and concepts::is_bitwiseable<T2>
    inline void set_bits(T1 &bit_set, const T2 bit_mask) {

        bit_set = (bit_set & (~bit_mask)) | (bit_mask);
    }

    /**
     * Clear the bits in bit_set at bit_mask position.
     *
     * @code
     * uint8_t bitset{0b11111111};
     * uint8_t bitmask{0b11000011};
     * clear_bits(bitset, bitmask);
     *
     * // Result: bitset == 0b00111100;
     * @endcode
     *
     * @tparam T1 type of bit_set. Must be bitwiseable
     * @tparam T2 type of bit_mask. Must be bitwiseable
     * @param bit_set the bit field to modify
     * @param bit_mask the mask to clear bits
     */
    template<typename T1, typename T2>
    requires concepts::is_bitwiseable<T1> and concepts::is_bitwiseable<T2>
    inline void clear_bits(T1 &bit_set, const T2 bit_mask) {

        bit_set &= ~bit_mask;
    }

    /**
     * Toggle the bit in bit_set using bit_mask.
     *
     * @code
     * uint8_t bitset{0b11111111};
     * uint8_t bitmask{0b11000011};
     * toggle_bits(bitset, bitmask);
     *
     * // Result: bitset == 0b00111100
     * @endcode
     *
     * @tparam T1 type of bit_set. Must be bitwiseable
     * @tparam T2 type of bit_mask. Must be bitwiseable
     * @param bit_set the bit field to modify
     * @param bit_mask the mask to toggle bits
     */
    template<typename T1, typename T2>
    requires concepts::is_bitwiseable<T1> and concepts::is_bitwiseable<T2>
    inline void toggle_bits(T1 &bit_set, const T2 bit_mask) {

        bit_set ^= bit_mask;
    }

    /**
     * Check whether or not a bit mask is in the bit field.
     *
     * @tparam T1 type of bit_set. Must be bitwiseable
     * @tparam T2 type of bit_mask. Must be bitwiseable
     * @param bit_set the bit field to modify
     * @param bit_mask the bit mask to check
     * @return true or false if the bit mask is in the bit field
     */
    template<typename T1, typename T2>
    requires concepts::is_bitwiseable<T1> and concepts::is_bitwiseable<T2>
    inline bool check_bits(const T1 &bit_set, const T2 bit_mask) {

        return (bit_set & bit_mask) == bit_mask;
    }

    /**
     * Get the length of a given array
     *
     * @code
     * uint8_t buffer8[4096]{};
     * uint16_t buffer16[4096]{};
     * uint32_t buffer32[4096]{};
     * uint64_t buffer64[4096]{};
     *
     * sizeof_array(buffer8) == 4096 // True
     * sizeof_array(buffer16) == 4096 // True
     * sizeof_array(buffer32) == 4096 // True
     * sizeof_array(buffer64) == 4096 // True
     * @endcode
     *
     * @tparam T type of the array
     * @tparam length length of the array
     * @return length of the given array
     */
    template<typename T, size_t length>
    constexpr size_t sizeof_array(const T (&)[length]) {

        return length;
    }

    /**
     * Sleep for us microseconds
     *
     * @param us number of microseconds to sleep
     */
    void sleep_us(uint64_t us) {
#ifdef PICO_RP2040
        sleep_us(us);
#else
#warning Function not defined
#endif
    }

    /**
     * Sleep for ms milliseconds
     *
     * @param ms number of milliseconds to sleep
     */
    void sleep_ms(uint32_t ms) {
#ifdef PICO_RP2040
        sleep_ms(ms);
#else
#warning Function not defined
#endif
    }

} // namespace hal

#endif //EMBEDDED_LIBRARY_COMMONS_H
