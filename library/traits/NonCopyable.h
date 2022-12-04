/**
 * @file NonCopyable.h
 * @brief Provide a base class that is non copy constructible or copy assignable.
 *
 * The class @ref NonCopyable "NonCopyable" is a class that cannot be copy constructed
 * nor can it be copy assigned.
 *
 * @code{cpp}
 * #include <iostream>
 *
 * class A : public NonCopyable<A> {
 *  A()=default;
 *  ~A() override =default;
 *
 * };
 *
 * int main() {
 *     A a{}; // Ok: default construction
 *
 *     A b{std::move(a)}; // Ok: move construction
 *
 *     A c{b}; // Error: copy construction
 *
 *     A d{};
 *     d = b; // Error: copy assignment
 *
 *     return 0;
 * }
 * @endcode
 */

#ifndef EMBEDDEDLIBRARY_NONCOPYABLE_H
#define EMBEDDEDLIBRARY_NONCOPYABLE_H

namespace eml::traits {

    template<typename T>
    class NonCopyable {
    public:
        NonCopyable()=default;
        virtual ~NonCopyable()=default;

        /**
         * Provide a default move constructor.
         */
        NonCopyable(NonCopyable &&) noexcept =default;

        /**
         * Provide a default move assignment operator.
         *
         * @return *this
         */
        NonCopyable &operator=(NonCopyable &&) noexcept = default;

        /**
         * Disable copy constructor.
         * Prevent an object to be copy constructed at compile time.
         */
        NonCopyable(const NonCopyable &)=delete;

        /**
         * Disable copy assignment.
         * Prevent an object to be copy assigned at compile time.
         *
         * @return cannot return anything
         */
        NonCopyable &operator=(const NonCopyable &)=delete;

    protected:

    private:
    };

} // eml::traits

#endif //EMBEDDEDLIBRARY_NONCOPYABLE_H
