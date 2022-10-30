/**
 * @file NonMovable.h
 * @brief Provide a base class that is non move constructible or move assignable.
 *
 * The class @ref NonMovable "NonMovable" is a class that cannot be move constructed
 * nor can it be move assigned.
 *
 * @code{cpp}
 * #include <iostream>
 *
 * class A : public NonMovable<A> {
 *  A()=default;
 *  ~A() override =default;
 *
 * };
 *
 * int main() {
 *
 *     A a{}; // Ok: default construction
 *
 *     A b{std::move(a)}; // Error: move construction
 *
 *     A c{b}; // Ok: copy construction
 *
 *     A d{};
 *     d = std::move(c); // Error: move assignment
 *
 *     return 0;
 * }
 * @endcode
 */

#ifndef EMBEDDEDLIBRARY_NONMOVABLE_H
#define EMBEDDEDLIBRARY_NONMOVABLE_H

namespace hal::traits {

    template<typename T>
    class NonMovable {
    public:
        NonMovable()=default;
        virtual ~NonMovable()=default;

        /**
         * Provide a default copy constructor.
         */
        NonMovable(const NonMovable &)=default;

        /**
         * Provide a default copy assignment operator.
         *
         * @return *this
         */
        NonMovable &operator=(const NonMovable &)=default;

        /**
         * Disable move constructor.
         * Prevent an object to be move constructed at compile time.
         */
        NonMovable(NonMovable &&)=delete;

        /**
         * Disable move assignment.
         * Prevent an object to be move assigned at compile time.
         *
         * @return cannot return anything
         */
        NonMovable &operator=(NonMovable &&)=delete;
    };
} // hal::traits
#endif //EMBEDDEDLIBRARY_NONMOVABLE_H
