.. role:: cpp(code)
    :language: c++

=======
Commons
=======

Enums
=====

.. doxygennamespace:: eml::hal::peripherals

.. doxygenenum:: eml::hal::Error

Classes
=======

.. doxygenclass:: eml::etl::TypeSerializer
    :members:
    :protected-members:

Functions
=========

.. doxygenfunction:: eml::set_bit

.. doxygenfunction:: eml::clear_bit

.. doxygenfunction:: eml::toggle_bit

.. doxygenfunction:: eml::check_bit

.. doxygenfunction:: eml::set_bits_pos

.. doxygenfunction:: eml::set_bits

.. doxygenfunction:: eml::clear_bits

.. doxygenfunction:: eml::toggle_bits

.. doxygenfunction:: eml::check_bits

.. doxygenfunction:: eml::sizeof_array

To Be Implemented
=================

.. warning::
    | The function :cpp:`eml::hal::sleep_micros(uint64_t us)` and :cpp:`eml::hal::sleep_millis(uint32_t ms)` have to be implemented in their implementation file.
    | The function :cpp:`eml::hal::pin()` have to be implemented as long as the :cpp:`struct pin_t`.
