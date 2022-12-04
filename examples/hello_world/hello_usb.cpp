//
// Created by marmelade on 28/11/22.
//

#include <cstdio>

#ifdef LIB_PICO_PLATFORM
#include <pico/stdlib.h>
#endif

int main() {

#ifdef LIB_PICO_PLATFORM
    stdio_init_all();
#endif

    while(true) {

        printf("Hello, World!\n");
    }
}
