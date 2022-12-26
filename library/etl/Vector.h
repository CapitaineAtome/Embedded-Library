//
// Created by marmelade on 04/12/22.
//

#ifndef EMBEDDEDLIBRARY_VECTOR_H
#define EMBEDDEDLIBRARY_VECTOR_H

#include "../library/traits/NonCopyable.h"
#include "../commons/commons.h"

#include <cstddef>

#ifdef EML_THREAD_SUPPORTED
#include <shared_mutex>
#include <mutex>
#endif

namespace eml::etl {

    template<typename T, const size_t L>
    class Vector : public traits::NonCopyable<Vector<T, L>> {
    public:

        Vector() : m_vector{} {};

        Vector(const Vector &other)  {

            std::copy(other.begin(), other.end(), m_vector);

            m_current_length = other.m_current_length;
        }

        /**
         * Provide a default move constructor.
         */
        Vector(Vector &&other) noexcept : Vector() {

            swap(*this, other);
        }

        /**
         * Provide a default copy assignment operator.
         *
         * @return *this
         */
        Vector &operator=(Vector other) {

            swap(*this, other);

            return *this;
        }

        /**
         * Provide a default move assignment operator.
         *
         * @return *this
         */
        Vector &operator=(Vector &&other) noexcept {

            swap(*this, other);

            return *this;
        }

        /**
         * Same as @ref Vector::at().
         * @param index index of the element to reach
         * @return element
         */
        [[nodiscard]] T &operator[](const size_t index) {

            return at(index);
        }

        /**
         * Return the element at the index provided
         * @param index index of the element to reach
         * @return element
         */
        [[nodiscard]] T &at(const size_t index) {

#ifdef EML_THREAD_SUPPORTED
            std::unique_lock lock_writing_{m_lock};
#endif

            assert(index < m_current_length);

            if(index < m_current_length) {

                return m_vector[index];
            }

            return T{};
        }

        T *begin() {

            return m_vector;
        }

        T *end() {

            return m_vector + L;
        }

        /**
         * Check if a new element can be added, if true, add it then returns true. Returns false otherwise
         *
         * @note This function is thread safe only when EML_THREAD_SUPPORTED is defined. i.e If locking mechanisms from standard library are supported
         * @warning Unless conditions were specified, this function isn't thread safe
         * @param element to add
         * @return
         */
        bool push_back(const T & element) {

#ifdef EML_THREAD_SUPPORTED
            std::unique_lock lock_writing_{m_lock};
#endif

            if(m_current_length < L) {

                m_vector[m_current_length++] = element;

                return false;
            }

            return true;
        }

        /**
         * Check if a new element can be added, if true, add it then returns true. Returns false otherwise
         *
         * @note This function is thread safe only when EML_THREAD_SUPPORTED is defined. i.e If locking mechanisms from standard library are supported
         * @warning Unless conditions were specified, this function isn't thread safe
         *
         * @param element to add
         *
         * @return
         */
        bool push_back(const T && element) {

#ifdef EML_THREAD_SUPPORTED
            std::unique_lock lock_writing_{m_lock};
#endif

            if(m_current_length < L) {

                m_vector[m_current_length++] = std::move(element);

                return false;
            }

            return true;
        }

        /**
         * Remove the last element from the vector.
         *
         * @note This function is thread safe only when EML_THREAD_SUPPORTED is defined. i.e If locking mechanisms from standard library are supported
         * @warning Unless conditions were specified, this function isn't thread safe
         */
        void pop_back() noexcept {

#ifdef EML_THREAD_SUPPORTED
            std::unique_lock lock_writing_{m_lock};
#endif

            m_current_length = m_current_length > 0 ? --m_current_length : m_current_length;
        }

        /**
         * Current length of the vector. Length can go up to @ref max_length.
         *
         * @return current vector length
         */
        size_t length() const noexcept {

            return m_current_length;
        }

        /**
         * Maximum length of the vector. @ref length cannot exceed this value.
         *
         * @return maximum vector length
         */
        size_t max_length() const noexcept {

            return L;
        }

        friend void swap(Vector &first, Vector &second) {

            using std::swap;

            swap(first.m_vector, second.m_vector);
            swap(first.m_current_length, second.m_current_length);
        }
    protected:
#ifdef EML_THREAD_SUPPORTED
        std::shared_mutex m_lock;
#endif
        T m_vector[L]; ///< The vector
        size_t m_current_length{}; ///< Current length of the vector. This value can change when pushing and popping.

    private:
    };

} // namespace eml::etl

#endif //EMBEDDEDLIBRARY_VECTOR_H
