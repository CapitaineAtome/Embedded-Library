//
// Created by marmelade on 31/12/22.
//

#ifndef EXAMPLES_ARRAY_H
#define EXAMPLES_ARRAY_H

#include "../commons/commons.h"

namespace eml::etl {
    template<typename T, const std::size_t L>
    class Array {
    public:
        Array() : m_array{} {

        }

        Array(const T &init_val) {

            for (auto &elem_: *this) {

                elem_ = init_val;
            }
        }

        Array(const Array &other) {

            std::copy(other.begin(), other.end(), m_array);
        }

        Array(Array &&other) noexcept {

            swap(*this, other);
        }

        ~Array() = default;

        Array &operator=(Array other) {

            swap(*this, other);

            return *this;
        }

        Array &operator=(Array &&other) noexcept {

            swap(*this, other);

            return *this;
        }

        T &operator[](const std::size_t index) {
#ifdef EML_THREAD_SUPPORTED
            std::unique_lock lock_writing_{m_lock};
#endif

            return at(index);
        }

        T &at(const std::size_t index) {

#ifdef EML_THREAD_SUPPORTED
            std::unique_lock lock_writing_{m_lock};
#endif
            assert(index < L);

            if (index < L) {

                return m_array[index];
            }

            return T{};
        }

        T *begin() const noexcept {

            return m_array;
        }

        T *end() const noexcept {

            return m_array + L;
        }

        friend void swap(Array &first, Array &second) {

            using std::swap;

            swap(first.m_array, second.m_array);
        }

    protected:
#ifdef EML_THREAD_SUPPORTED
        std::shared_mutex m_lock;
#endif
        T m_array[L]; ///< The array

    private:
    };
}
#endif //EXAMPLES_ARRAY_H
