//
// Created by marmelade on 04/12/22.
//

#ifndef EMBEDDEDLIBRARY_TYPESERIALIZER_H
#define EMBEDDEDLIBRARY_TYPESERIALIZER_H

#include "../commons/commons.h"

#include <cstdint>
#include <cstddef>
#include <cstring>

namespace eml::etl {

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
        TypeSerializer(TypeSerializer &&other) noexcept : TypeSerializer() { swap(*this, other); }

        ~TypeSerializer()=default;

        TypeSerializer &operator=(TypeSerializer other) {

            swap(*this, other);

            return *this;
        }

        TypeSerializer &operator=(TypeSerializer &&other) noexcept {

            swap(*this, other);

            return *this;
        }

        /**
         * Pack a value using buffer.
         * @ref eml::etl::TypeSerialize::pack() "see pack".
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
         * @ref eml::etl::TypeSerialize::unpack() "see unpack".
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

            m_value.v64 = 0 | value;
            return *this;
        }

        /**
         * Operator to pack a uin16_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator<<(const uint16_t value) {

            m_value.v64 = 0 | value;
            return *this;
        }

        /**
         * Operator to pack a uin32_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator<<(const uint32_t value) {

            m_value.v64 = 0 | value;
            return *this;
        }

        /**
         * Operator to pack a uin64_t
         *
         * @param value to serialize
         * @return instance of this class
         */
        TypeSerializer &operator<<(const uint64_t value) {

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
            memcpy(buffer, &m_value, std::min(sizeof(m_value), sz));

            return std::min(sizeof(m_value), sz);
        }

        /**
         * Pack a value from buffer and return the size packed.
         *
         * @param buffer value to pack
         * @param sz size of the value
         * @return size of the packed value
         */
        std::size_t pack(const uint8_t * const buffer, const std::size_t sz) {

            clear();
            memcpy(&m_value, buffer, std::min(sizeof(m_value), sz));

            return std::min(sizeof(m_value), sz);
        }

        friend void swap(TypeSerializer &first, TypeSerializer &second) {

            using std::swap;

            swap(first.m_value, second.m_value);
        }

    protected:
        /**
         * Union that hold the values that can be packed.
         */
        typedef union [[nodiscard]]  {
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

} // namespace eml::etl

#endif //EMBEDDEDLIBRARY_TYPESERIALIZER_H
