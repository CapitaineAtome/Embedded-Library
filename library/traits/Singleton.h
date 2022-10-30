//
// Created by marmelade on 16/10/22.
//

#ifndef EMBEDDEDLIBRARY_SINGLETON_H
#define EMBEDDEDLIBRARY_SINGLETON_H

#include "NonCopyable.h"

namespace hal::traits {

    class Singleton : public NonCopyable<Singleton>, public NonMovable<Singleton> {
    public:
        ~Singleton() override=default;

        /**
         * Return an instance of a Singleton.
         * Although this function isn't defined here, it must be
         * defined and implemented by the concrete class.
         *
         * @param instance the instance to return
         * @return on error set error accordingly
         */
        // static Singleton &getInstance(const uint8_t instance);

    protected:
        Singleton()=default;

    private:

    };

} // hal::traits

#endif //EMBEDDEDLIBRARY_SINGLETON_H
