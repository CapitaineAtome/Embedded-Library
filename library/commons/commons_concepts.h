/**
 * @file commons_concepts.h
 * @brief Provide concepts for the API
 *
 * Provide common concepts that are used throughout the API.
 * These concepts are used to constrain template definition such as in commons.h file
 */

#ifndef EMBEDDED_LIBRARY_COMMONS_CONCEPTS_H
#define EMBEDDED_LIBRARY_COMMONS_CONCEPTS_H

#include <concepts>

namespace hal::concepts {
    /**
	 *	Concept that check if the type T is serializable.
	 *
	 * @tparam T type to check
	 * @returns Whether T is serializable
	 */
    template<typename T>
    concept is_serializable = requires(T) {
        { std::is_integral<T>::value };
    };

    /**
     * Concept that check if the type T can be used with bitwise operands
     *
     * @tparam T type to check
     * @returns Whether T can be used with bitwise operands
     */
    template<typename T>
    concept is_bitwiseable = requires(T) {
        { std::is_integral<T>::value };
    };

} // namespace hal::concepts

#endif //EMBEDDED_LIBRARY_COMMONS_CONCEPTS_H
