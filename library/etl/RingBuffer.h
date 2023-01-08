//
// Created by marmelade on 04/12/22.
//

#ifndef EMBEDDEDLIBRARY_RINGBUFFER_H
#define EMBEDDEDLIBRARY_RINGBUFFER_H

#include "../commons/commons.h"

#ifdef EML_THREAD_SUPPORTED
#include <shared_mutex>
#include <mutex>
#endif

namespace eml::etl {

    template<typename T, const std::size_t L>
    class RingBuffer {
    public:

        explicit RingBuffer() : m_ring{} {};

        /**
         * Provide a copy constructor.
         */
        RingBuffer(const RingBuffer &other) {

            std::copy(other.begin(), other.end(), m_ring);

            m_read_pos = other.m_read_pos;
            m_write_pos = other.m_write_pos;
        }

        /**
         * Provide a move constructor.
         */
        RingBuffer(RingBuffer &&other) noexcept {

            swap(*this, other);
        }

        ~RingBuffer()=default;

        /**
         * Provide a default move assignment operator.
         *
         * @return *this
         */
        RingBuffer &operator=(RingBuffer &&other) noexcept {

            swap(*this, other);

            return *this;
        }

        /**
         * Provide a default move assignment operator.
         *
         * @return *this
         */
        RingBuffer &operator=(RingBuffer other) {

            swap(*this, other);

            return *this;
        }

        /**
         * Same as @ref write.
         *
         * @param value value to read
         * @return *this
         */
        RingBuffer &operator<<(const T &value) noexcept {

            write(value);

            return *this;
        }

        /**
         * Same as @ref read()
         *
         * @param value variable in which to store
         * @return *this
         */
        RingBuffer &operator>>(T &value) noexcept {

            value = read();

            return *this;
        }

        T *begin() const noexcept {

            return m_ring;
        }

        T *end() const noexcept {

            return m_ring + L;
        }

        /**
         * Moves the write position and write the element into the buffer.
         *
         * @note This function is thread safe only when EML_THREAD_SUPPORTED is defined. i.e If locking mechanisms from standard library are supported
         * @warning Unless conditions were specified, this function isn't thread safe
         *
         * @param element to write
         */
        void write(const T &element) noexcept {

#ifdef EML_THREAD_SUPPORTED
            std::unique_lock lock_writing_{m_lock};
#endif

            m_ring[(m_write_pos %= L)++] = element;
        }

        /**
         * Read the oldest element on the buffer and increment the reading position.
         *
         * @note This function is thread safe only when EML_THREAD_SUPPORTED is defined. i.e If locking mechanisms from standard library are supported
         * @warning Unless conditions were specified, this function isn't thread safe
         *
         * @return oldest element
         */
        [[nodiscard]] T &read() noexcept {

#ifdef EML_THREAD_SUPPORTED
            std::shared_lock lock_reading_{m_lock};
#endif

            return m_ring[(m_read_pos %= L)++];
        }

        void clear() noexcept {

            reset();

            for(auto &elem : *this) {

                elem = T{};
            }
        }

        void reset() noexcept {

            m_read_pos = std::max(m_read_pos, m_write_pos);
            m_write_pos = m_read_pos;
        }

        bool empty() const noexcept {

            return length() == 0;
        }

        std::size_t length() const noexcept {

            return std::max(m_read_pos, m_write_pos) - std::min(m_read_pos, m_write_pos);
        }

        std::size_t max_length() const noexcept {

            return L;
        }

        std::size_t size() const noexcept {

            return sizeof(T) * L;
        }

        friend void swap(RingBuffer &first, RingBuffer &second) {

            using std::swap;

            swap(first.m_ring, second.m_ring);
            swap(first.m_read_pos, second.m_read_pos);
            swap(first.m_write_pos, second.m_write_pos);
        }

    protected:
#ifdef EML_THREAD_SUPPORTED
        std::shared_mutex m_lock;
#endif
        T m_ring[L]; ///< The ring
        std::size_t m_read_pos{}; ///< Position on the read sequence
        std::size_t m_write_pos{}; ///< Position on the write sequence

    private:
    };

} // namespace eml::etl

#endif //EMBEDDEDLIBRARY_RINGBUFFER_H
