.. role:: cpp(code)
    :language: c++

=======
Commons
=======

Enums
=====

.. doxygennamespace:: hal::peripherals

.. doxygenenum:: hal::Error

Classes
=======

.. doxygenclass:: hal::TypeSerializer
    :members:
    :protected-members:

Functions
=========

.. doxygenfunction:: hal::set_bit

.. doxygenfunction:: hal::clear_bit

.. doxygenfunction:: hal::toggle_bit

.. doxygenfunction:: hal::check_bit

.. doxygenfunction:: hal::set_bits_pos

.. doxygenfunction:: hal::set_bits

.. doxygenfunction:: hal::clear_bits

.. doxygenfunction:: hal::toggle_bits

.. doxygenfunction:: hal::check_bits

.. doxygenfunction:: hal::sizeof_array

To Be Implemented
=================

.. warning::
    The function :cpp:`hal::sleep(uint64_t us)` and :cpp:`hal::sleep(uint32_t ms)` have to be implemented in their implementation file.


