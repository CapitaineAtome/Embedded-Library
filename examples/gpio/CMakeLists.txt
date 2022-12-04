add_executable(Blinky
        blinky.cpp
        )

target_link_libraries(Blinky
        pico_stdlib
        )

pico_add_extra_outputs(Blinky)