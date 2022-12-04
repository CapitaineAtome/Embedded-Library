/**
 * @file commons.h
 * @brief Provide common functions to the API
 *
 * Here are implemented common functions that are used throughout the API.
 *
 * @note The following functions have to be implemented:
 * - @ref hal::sleep(uint32_t ms) "sleep ms"
 * - @ref hal::sleep(uint64_t us) "sleep µs"
 *
 * @warning If these functions aren't implemented a warning will be raised and they won't do anything !
 *
 */

#ifndef EMBEDDED_LIBRARY_COMMONS_H
#define EMBEDDED_LIBRARY_COMMONS_H

#include <atomic>

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <sys/types.h>

#include "../traits/NonCopyable.h"
#include "../traits/NonMovable.h"

#include "commons_concepts.h"

#ifdef LIB_PICO_PLATFORM
#include "commons_rp2040.h"
//#elif defined(HAL_ATMEGA328) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) // NOTE: NOT IMPLEMENTED YET
//#include "commons_atmega328p.h"
#else
#warning Platform not defined or not recognised
#endif

/**********************************************************************************************************************
 * These are implemented in platform specific headers
 *      namespace hal::peripherals {
 *          enum UARTInstance : uint8_t {}; which list number of UART instance
 *          enum SPIInstance : uint8_t {}; which list number of SPI instance
 *          enum I2CInstance : uint8_t {}; which list number of I2C instance
 *          and so on
 *          ....
 *      }
 *
 * Not all platform implement the enum classes nor their fields.
 * For more platform specific functions use the platform API.
 *
 **********************************************************************************************************************/

namespace hal {

    // ****************************************************************
    //                              Enums
    // ****************************************************************

    namespace peripherals {

        constexpr uint UART_DEFAULT_BAUD_RATE{115'200U};      ///< uart default baud rate
        constexpr uint I2C_DEFAULT_BAUD_RATE{400'000U};       ///< i2c default baud rate
        constexpr uint SPI_DEFAULT_BAUD_RATE{50'000'000U};    ///< spi default baud rate

        namespace gpio {

            /**
             * Direction definition of a GPIO pin
             */
            enum class Direction : uint8_t {

                IN,
                OUT,
            };

            /**
             * Pulling mode definition of a GPIO pin
             */
            enum class Pull : uint8_t {

                NONE,
                UP,
                DOWN,
                OPEN_DRAIN,
            };

            /**
             * Function definition of a GPIO pin. What it is used for. NONE = DEFAULT
             */
            enum class Function : uint8_t {

                NONE,
                GPIO,
                UART,
                SPI,
                I2C,
                PWM,
                USB,
            };

            /**
             * Interrupt level definition of a GPIO pin
             */
            enum class IRQ : uint8_t {

                NONE,
                LEVEL_LOW,
                LEVEL_HIGH,
                EDGE_FALL,
                EDGE_RISE,
            };

            enum class SlewRate : uint8_t {
                SLOW,
                FAST,
            };

        } // namespace gpio

        namespace uart {

            enum class Parity : uint8_t {
                PARITY_NONE,
                PARITY_EVEN,
                PARITY_ODD,
            };
        } // namespace uart

        namespace spi {

            enum class ClockPhase : uint8_t {

                CLOCK_PHASE0,
                CLOCK_PHASE1,
            };

            enum class ClockPolarity : uint8_t {

                CLOCK_POLARITY0,
                CLOCK_POLARITY1,
            };
        }

        enum class Mode : uint8_t {
            MODE_SLAVE,
            MODE_MASTER,
        };

    } // namespace peripherals

    enum class BitOrder : uint8_t {

        ORDER_LITTLE_ENDIAN,
        ORDER_BIG_ENDIAN,
    };

    enum class Error {

        NONE,
        ERROR,
        NOTAVAILABLEONPLATFORM,
        READ,
        WRITE,
        TOOSMALL,
        TOOBIG,
        TIMEOUT,
        AGAIN,

    }; // enum class Error

    // ****************************************************************
    //                         Global Variables
    // ****************************************************************

    std::atomic<Error> error;

    // ****************************************************************
    //                             Functions
    // ****************************************************************

    /**
     * Set a bit in a bitset.
     *
     * @code{cpp}
     * uint8_t bit_set{0};
     * uint8_t pos{4};
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
     * @code{cpp}
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
     * @code{cpp}
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
     * @code{cpp}
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
     * @code{cpp}
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
     * @code{cpp}
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
     * @code{cpp}
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
     * @code{cpp}
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
     * @code{cpp}
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
     * Compares and returns the minimum value given in parameters.
     *
     * @note Return type depend on rule of T1 and T2 cast rule. double > float > long int > int
     *
     * @tparam T1 type of first parameter that has to be totally ordered
     * @tparam T2 type of second parameter that has to be totally ordered
     * @param a element to compare
     * @param b element to compare
     * @return minimum value between the first and second parameters
     */
    template<typename T1, typename T2>
    requires std::totally_ordered<T1> and std::totally_ordered<T2>
    auto min(T1 a, T2 b) {

        return (a < b ? a : b);
    }

    /**
     * Compares and returns the maximum value given in parameters.
     *
     * @note Return type depend on rule of T1 and T2 cast rule. double > float > long int > int
     *
     * @tparam T1 type of first parameters that has to be totally ordered
     * @tparam T2 type of second parameters that has to be totally ordered
     * @param a element to compare
     * @param b element to compare
     * @return maximum value between the first and second parameters
     */
    template<typename T1, typename T2>
    requires std::equality_comparable<T1> and std::equality_comparable<T2>
    auto max(T1 a, T2 b) {

        return (a > b ? a : b);
    }

    /**
     * Sleep for us microseconds
     *
     * @param us number of microseconds to sleep
     */
    void sleep_micros(uint64_t us);

    /**
     * Sleep for ms milliseconds
     *
     * @param ms number of milliseconds to sleep
     */
    void sleep_millis(uint32_t ms);

    /**
     * Class that is used to pack and unpack data types.
     * Values can be unpacked to another native c++ types or to a buffer for them to be send over
     * a communication wire, protocol ...
     *
     * @code{cpp}
     * TypesSerializer ts{};
     * uint8_t buffer[ts::buffer_size];
     * ts << 3.141f // Pack a float
     * ts >> buffer; // Unpack it into buffer
     * @endcode
     *
     */
    class TypeSerializer {
    public:

        TypeSerializer() : m_value{} {}
        TypeSerializer(const TypeSerializer &other) : m_value{other.m_value} {}
        TypeSerializer(TypeSerializer &&other) noexcept : m_value{other.m_value} { other.m_value.v64 = 0;}

        ~TypeSerializer()=default;

        TypeSerializer &operator=(const TypeSerializer &other) {
            if(this != &other) {
                m_value = other.m_value;
            }
            return *this;
        }

        TypeSerializer &operator=(TypeSerializer &&other) noexcept {
            if(this != &other) {
                m_value = other.m_value;

                other.m_value.v64 = 0;
            }
            return *this;
        }

        /**
         * Pack a value using buffer.
         * @ref hal::TypeSerialize::pack() "see pack".
         *
         * @tparam sz size of the buffer
         * @param buffer contains value to pack
         * @return instance of this class
         */
        template<const size_t sz>
        TypeSerializer &operator<<(uint8_t (&buffer)[sz]) {
            pack(buffer, sz);
            return *this;
        }

        /**
         * Unpack a value using buffer.
         * @ref hal::TypeSerialize::unpack() "see unpack".
         *
         * @tparam sz size of the buffer
         * @param buffer contains value to unpack
         * @return instance of this class
         */
        template<const size_t sz>
        TypeSerializer &operator>>(uint8_t (&buffer)[sz]) {
            unpack(buffer, sz);
            return *this;
        }

        /**
         * Operator to pack a uin8_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator<<(const uint8_t value) {

            m_value.v64 = 0;
            m_value.v8 = value;
            return *this;
        }

        /**
         * Operator to pack a uin16_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator<<(const uint16_t value) {

            m_value.v64 = 0;
            m_value.v16 = value;
            return *this;
        }

        /**
         * Operator to pack a uin32_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator<<(const uint32_t value) {

            m_value.v64 = 0;
            m_value.v32 = value;
            return *this;
        }

        /**
         * Operator to pack a uin64_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator<<(const uint64_t value) {

            m_value.v64 = 0;
            m_value.v64 = value;
            return *this;
        }

        /**
         * Operator to pack a float
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator<<(const float value) {

            m_value.v64 = 0;
            m_value.vf = value;
            return *this;
        }

        /**
         * Operator to pack a double
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator<<(const double value) {

            m_value.v64 = 0;
            m_value.vd = value;
            return *this;
        }

        /**
         * Operator to unpack a uint8_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator>>(uint8_t &value) {

            value = m_value.v8;
            return *this;
        }

        /**
         * Operator to unpack a uint16_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator>>(uint16_t &value) {

            value = m_value.v16;
            return *this;
        }

        /**
         * Operator to unpack a uint32_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator>>(uint32_t &value) {

            value = m_value.v32;
            return *this;
        }

        /**
         * Operator to unpack a uint64_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator>>(uint64_t &value) {

            value = m_value.v64;
            return *this;
        }

        /**
         * Operator to unpack a float
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator>>(float &value) {

            value = m_value.vf;
            return *this;
        }

        /**
         * Operator to unpack a double
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator>>(double &value) {

            value = m_value.vd;
            return *this;
        }

        /**
         * Clear the packed value
         */
        void clear() {

            m_value.v64 = 0; // Can also do a memset but this is faster
        }

        /**
         * Unpack a value and set it into buffer. Return the size of the unpacked value.
         *
         * @param buffer value to pack
         * @param sz sizeof of the value
         * @return size of the unpacked value
         */
        std::size_t unpack(uint8_t * const buffer, const size_t sz) const {

            memset(buffer, 0, sz);
            memcpy(buffer, &m_value, hal::min(sizeof(m_value), sz));

            return hal::min(sizeof(m_value), sz);
        }

        /**
         * Pack a value from buffer and return size packed.
         *
         * @param buffer value to pack
         * @param sz size of the value
         * @return size of the packed value
         */
        std::size_t pack(const uint8_t * const buffer, const std::size_t sz) {

            clear();
            memcpy(&m_value, buffer, hal::min(sizeof(m_value), sz));

            return hal::min(sizeof(m_value), sz);
        }

    protected:
        /**
         * Union that hold the values that can be packed.
         */
        typedef union {
            uint8_t v8;
            uint16_t v16;
            uint32_t v32;
            uint64_t v64;
            float vf;
            double vd;
        } type_serializer_value;

        /**
         * Holds the value packed.
         */
        type_serializer_value m_value;

    private:

    public:
        static constexpr size_t buffer_size{sizeof(type_serializer_value)};

    };

} // namespace hal

#endif //EMBEDDED_LIBRARY_COMMONS_H
