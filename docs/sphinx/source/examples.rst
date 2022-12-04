.. role:: cpp(code)
    :language: c++

========
Examples
========

Hello World!
============

| Hello World through uart.
.. literalinclude:: ../../../examples/hello_world/hello_uart.cpp
    :language: c++
    :linenos:

| Hello World through usb.
.. literalinclude:: ../../../examples/hello_world/hello_usb.cpp
    :language: c++
    :linenos:

| The difference between standard output from usb and uart on raspberry pi pico is located in the CMakeLists.
.. literalinclude:: ../../../examples/hello_world/CMakeLists.txt
    :language: cmake
    :linenos:
    :emphasize-lines: 11, 12, 26, 27

GPIO
====

| Example for blinking a LED every few milliseconds.
.. literalinclude:: ../../../examples/gpio/blinky.cpp
    :language: c++
    :linenos:
