//
// Created by marmelade on 27/12/22.
//

#ifndef EMBEDDEDLIBRARY_SSD1306_H
#define EMBEDDEDLIBRARY_SSD1306_H

#include "peripherals/I2C.h"

namespace eml::devices {

    // TODO: Penser à créer une interface screen ?
    // Check: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf#%5B%7B%22num%22%3A2326%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C0%2C842%2Cnull%5D

    class SSD1306 {
    public:

        typedef struct [[nodiscard]] {

            uint8_t start_page;
            uint8_t end_page;

            uint8_t start_column;
            uint8_t end_column;

        } render_area_t;

        enum Mode : uint8_t {

            WRITE = 0xFE,
            READ = 0xFF,
        };

        enum Registers : uint8_t {

            CONTRAST_CONTROL = 0x81,
            ENTIRE_DISPLAY_ON_CONTROL = 0xA4,
            DISPLAY_NORMAL_CONTROL = 0xA6,
            DISPLAY_ON_CONTROL = 0xAE,
            HORIZONTAL_SCROLLING_CONTROL = 0x26,
            VERTICAL_HORIZONTAL_SCROLLING_CONTROL = 0x29,
            VERTICAL_SCROLLING_CONTROL = 0xA3,
            START_SCROLLING_CONTROL = 0x2F,
            STOP_SCROLLING_CONTROL = 0x2E,
            MEMORY_ADDRESSING_MODE_CONTROL = 0x20,
            COLUMN_ADDRESS_COLUMN = 0x21,
            PAGE_ADDRESS_CONTROL = 0x22,
            PAGE_ADDRESSING_MODE_CONTROL = 0xB0,
        };

        enum HorizontalScrollingInterval : uint8_t {

            FRAMES_2 = 0b111,
            FRAMES_3 = 0b100,
            FRAMES_4 = 0b101,
            FRAMES_5 = 0b000,
            FRAMES_25 = 0b110,
            FRAMES_64 = 0b001,
            FRAMES_128 = 0b010,
            FRAMES_256 = 0b011,
        };

        enum MemoryAddressingMode : uint8_t {

            HORIZONTAL_ADDRESSING_MODE = 0b00,
            Vertical_ADDRESSING_MODE = 0b01,
            PAGE_ADDRESSING_MODE = 0b10,
        };

        explicit SSD1306(const hal::peripherals::I2CInstance instance, /*const render_area_t &render_area,*/ const uint8_t width = 128, const uint8_t height = 32, uint8_t address = 0x3C)
        : m_i2c_inst{hal::peripherals::i2c::I2C::getInstance(instance)}, /*m_render_area{render_area},*/ num_pages{static_cast<uint8_t>(height / 8)}, m_height{height}, m_width{width}, m_addr{address} {

            m_buffer_len = num_pages * width;

            init();
        }

        explicit SSD1306(hal::peripherals::i2c::I2C &i2c_instance, /*const render_area_t &render_area,*/ const uint8_t width = 128, const uint8_t height = 32, uint8_t address = 0x3C)
        : m_i2c_inst{i2c_instance}, /*m_render_area{render_area},*/ num_pages{static_cast<uint8_t>(height / 8)}, m_height{height}, m_width{width}, m_addr{address} {

            m_buffer_len = num_pages * width;

            init();
        }

        ~SSD1306()=default;

        void send_command(const uint8_t command) const {

            uint8_t buffer_[] = {0x80, command};

            m_i2c_inst.write((m_addr & Mode::WRITE), buffer_, sizeof_array(buffer_), false);
        }

        void send_command(const std::initializer_list<uint8_t> command) const {

            /*
             * send_command(Registers::CONTRAST_CONTROL);
             * send_command(contrast_level);
             * ------------------------------------------
             * send_command({Registers::CONTRAST_CONTROL, contrast_level})
             */

            for(const auto &cmd_ : command) {

                uint8_t buffer_[] = {0x80, cmd_};
                m_i2c_inst.write((m_addr & Mode::WRITE), buffer_, sizeof_array(buffer_), false);
            }
        }

        void init() const {

            set_display(true);

            // Init
            // TODO: Implémenter

            stop_scrolling();
            set_display(false);
        }

        /*void define_render_area(const render_area_t &render_area) {

            m_render_area.start_page = render_area.start_page;
            m_render_area.end_page = render_area.end_page;

            m_render_area.start_column = render_area.start_column;
            m_render_area.end_column = render_area.end_column;
        }

        void define_render_page(const uint8_t start_page, const uint8_t end_page) {

            m_render_area.start_page = start_page;
            m_render_area.end_page = end_page;
        }

        void define_render_column(const uint8_t start_column, const uint8_t end_column) {

            m_render_area.start_column = start_column;
            m_render_area.end_column = end_column;
        }*/

        // ---------------- Fundamental commands ----------------

        /**
         * Set the contrast level of the screen. Value between [1; 255]
         *
         * @param contrast_level contrast level
         */
        void set_contrast_control(const uint8_t contrast_level = 0x7F) const {

            send_command({Registers::CONTRAST_CONTROL, contrast_level});
        }

        /**
         * Set the entire display on. Parameter to resume on ram content or not.
         *
         * @param ignore_ram whether to print data from ram
         */
        void set_entire_display_on(const bool ignore_ram = true) const {

            send_command(Registers::ENTIRE_DISPLAY_ON_CONTROL | ignore_ram);
        }

        /**
         * Set the display printing mode.
         *
         * @param inverse whether to inverse display
         */
        void set_display_mode(const bool inverse = true) const {

            send_command(Registers::DISPLAY_NORMAL_CONTROL | inverse);
        }

        /**
         * Set the display on or off.
         *
         * @param on whether to set display on
         */
        void set_display(const bool on) const {

            send_command(Registers::DISPLAY_ON_CONTROL | on);
        }

        // ---------------- Scrolling commands ----------------

        void start_scrolling() const {

            send_command(Registers::START_SCROLLING_CONTROL);
        }

        void stop_scrolling() const {

            send_command(Registers::STOP_SCROLLING_CONTROL);
        }

        /**
         * Configure the horizontal scrolling of the screen.
         *
         * @param left_scrolling whether to scroll from the left
         * @param start_page page to start scrolling
         * @param end_page page to end scrolling
         * @param interval frame frequency
         */
        void configure_horizontal_scrolling(const bool left_scrolling, const uint8_t start_page, const uint8_t end_page, const HorizontalScrollingInterval interval) const {

            send_command(Registers::HORIZONTAL_SCROLLING_CONTROL | left_scrolling);
            send_command(0x00); // Dummy bytes
            send_command(start_page); // Define start page address
            send_command(interval); // Time interval between each scrolls
            send_command(end_page); // Define end page address
            send_command(0x00); // Dummy byte as 0x00
            send_command(0xFF); // Dummy byte as 0xFF
        }

        /**
         * Configure the vertical scrolling of the screen.
         *
         * @param top_area top area to start vertical scrolling
         * @param bottom_area bottom_area to start vertical scrolling
         */
        void configure_vertical_scrolling(const uint8_t top_area = 0, const uint8_t bottom_area = 0xFF) const {

            send_command(Registers::VERTICAL_SCROLLING_CONTROL);
            send_command(top_area); // Top area to start scrolling
            send_command(bottom_area & m_height); // Bottom area to start scrolling
        }

        /**
         * Configure the vertical and horizontal scrolling of the screen.
         *
         * @param start_page page to start scrolling
         * @param end_page page to end scrolling
         * @param interval frame frequency
         * @param left_scrolling whether to set horizontal scrolling from the left
         * @param vertical_offset offset of the vertical scrolling
         */
        void configure_vertical_horizontal_scrolling(const uint8_t start_page, const uint end_page, const HorizontalScrollingInterval interval, const bool left_scrolling, const uint8_t vertical_offset) const {

            send_command(Registers::VERTICAL_HORIZONTAL_SCROLLING_CONTROL | (left_scrolling ? 0b10 : 0b01));
            send_command(0x00); // Dummy byte
            send_command(start_page); // Define start page address
            send_command(interval); // Interval
            send_command(end_page); // Define end page address
            send_command(vertical_offset); // Define vertical scrolling offset
        }

        // ---------------- Addressing Setting commands ----------------

        /**
         * Set the lower nibble of the column start address register for page addressing mode.
         *
         * @note This command is only for page addressing mode
         *
         * @param start_address starting address
         */
        void set_lower_column_address(const uint8_t start_address = 0x00) const {

            send_command(start_address);
        }

        /**
         * Set the higher nibble of the column start address register for page addressing mode.
         *
         * @note This command is only for page addressing mode
         *
         * @param start_address starting address
         */
        void set_higher_columns_address(const uint8_t start_address = 0x00) const {

            send_command(start_address);
        }

        /**
         * Set the addressing mode of the memory.
         *
         * @param mem_addressing_mode @ref eml::hal::device::SSD1306::Registers::MemoryAddressingMode "see"
         */
        void set_memory_addressing(const MemoryAddressingMode mem_addressing_mode = MemoryAddressingMode::PAGE_ADDRESSING_MODE) const {

            send_command(Registers::MEMORY_ADDRESSING_MODE_CONTROL);
            send_command(mem_addressing_mode);
        }

        /**
         * Setup the column start and end address.
         *
         * @note This command is only for horizontal addressing mode
         *
         * @param start_column column start address
         * @param end_column column end address
         */
        void set_column_address(const uint8_t start_column = 0, const uint8_t end_column = 127) const {

            send_command(COLUMN_ADDRESS_COLUMN);
            send_command(start_column);
            send_command(end_column);
        }

        void set_page_address(const uint8_t start = 0, const uint8_t end = 7u) const {

            send_command(PAGE_ADDRESS_CONTROL);
            send_command(start);
            send_command(end);
        }

        void set_page_address_mode(const uint8_t page_addressing_start) const {

            send_command(PAGE_ADDRESSING_MODE_CONTROL | (page_addressing_start & 0b111));
        }

    protected:
        hal::peripherals::i2c::I2C &m_i2c_inst;
        uint16_t m_buffer_len;
        // render_area_t m_render_area;
        uint8_t m_height;
        uint8_t m_width;
        uint8_t m_addr;
        uint8_t num_pages;

    private:
    };
}
#endif // EMBEDDEDLIBRARY_SSD1306_H
