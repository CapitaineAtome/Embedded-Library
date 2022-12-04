//
// Created by marmelade on 06/10/22.
//

#include <gtest/gtest.h>

#include "commons/commons.h"
#include "etl/TypeSerializer.h"

#include <limits>

TEST(CommonsTest, set_bit) {

    uint8_t bitset;
    uint8_t pos;

    // --------------------------------
    bitset = 0xFF;
    pos = 1;
    commons::set_bit(bitset, pos);

    EXPECT_EQ(bitset, 0b11111111);

    // --------------------------------
    bitset = 0xF0;
    pos = 3;
    commons::set_bit(bitset, pos);
    EXPECT_EQ(bitset, 0b11111000);

    // --------------------------------
    bitset = 0x0F;
    pos = 12;
    commons::set_bit(bitset, pos);
    EXPECT_EQ(bitset, 0b00001111);

    // --------------------------------
    bitset = 0x00;
    pos = -4;
    commons::set_bit(bitset, pos);
    EXPECT_EQ(bitset, 0b00000000);
}

TEST(CommonsTest, clear_bit) {

    uint8_t bitset;
    uint8_t pos;

    // --------------------------------
    bitset = 0xFF;
    pos = 1;
    commons::clear_bit(bitset, pos);

    EXPECT_EQ(bitset, 0b11111101);

    // --------------------------------
    bitset = 0xF0;
    pos = 3;
    commons::clear_bit(bitset, pos);
    EXPECT_EQ(bitset, 0b11110000);

    // --------------------------------
    bitset = 0x0F;
    pos = 12;
    commons::clear_bit(bitset, pos);
    EXPECT_EQ(bitset, 0b00001111);

    // --------------------------------
    bitset = 0x00;
    pos = -4;
    commons::clear_bit(bitset, pos);
    EXPECT_EQ(bitset, 0b00000000);
}

TEST(CommonsTest, toggle_bit) {

    uint8_t bitset;
    uint8_t pos;

    // --------------------------------
    bitset = 0xFF;
    pos = 1;
    commons::toggle_bit(bitset, pos);

    EXPECT_EQ(bitset, 0b11111101);

    // --------------------------------
    bitset = 0xF0;
    pos = 6;
    commons::toggle_bit(bitset, pos);
    EXPECT_EQ(bitset, 0b10110000);

    // --------------------------------
    bitset = 0x0F;
    pos = 12;
    commons::toggle_bit(bitset, pos);
    EXPECT_EQ(bitset, 0b00001111);

    // --------------------------------
    bitset = 0x00;
    pos = -4;
    commons::toggle_bit(bitset, pos);
    EXPECT_EQ(bitset, 0b00000000);
}

TEST(CommonsTest, check_bit) {

    uint8_t bitset;
    uint8_t pos;

    // --------------------------------
    bitset = 0xFF;
    pos = 1;

    EXPECT_EQ(commons::check_bit(bitset, pos), true);

    // --------------------------------
    bitset = 0xF0;
    pos = 3;

    EXPECT_EQ(commons::check_bit(bitset, pos), false);

    // --------------------------------
    bitset = 0x0F;
    pos = 12;

    EXPECT_EQ(commons::check_bit(bitset, pos), false);

    // --------------------------------
    bitset = 0x00;
    pos = -4;

    EXPECT_EQ(commons::check_bit(bitset, pos), false);
}

TEST(CommonsTest, set_bit_pos) {

    uint8_t bitset;
    uint8_t pos;
    uint8_t value;

    // --------------------------------
    bitset = 0x0;
    pos = 2;
    value = 0xF;

    commons::set_bits_pos(bitset, pos, value);

    EXPECT_EQ(bitset, 0b00111100);

    // --------------------------------
    bitset = 0xFF;
    pos = 4;
    value = 0;

    commons::set_bits_pos(bitset, pos, value);

    EXPECT_EQ(bitset, bitset);

    // --------------------------------
    bitset = 0xF1;
    pos = 3;
    value = 1;

    commons::set_bits_pos(bitset, pos, value);

    EXPECT_EQ(bitset, 0b11111001);

    // --------------------------------
    bitset = 0x11;
    pos = 1;
    value = 3;

    commons::set_bits_pos(bitset, pos, value);

    EXPECT_EQ(bitset, 0b00010111);
}

TEST(CommonsTest, set_bits) {

    uint8_t bitset;
    uint8_t bitmask;

    // --------------------------------
    bitset = 0xFF;
    bitmask = 0;

    commons::set_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0xFF);

    // --------------------------------
    bitset = 0xF1;
    bitmask = 0x18;

    commons::set_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0xF9);

    // --------------------------------
    bitset = 0x0F;
    bitmask = 0xF0;

    commons::set_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0xFF);

    // --------------------------------
    bitset = 0x00;
    bitmask = 0x18;

    commons::set_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0x18);
}

TEST(CommonsTest, clear_bits) {

    uint8_t bitset;
    uint16_t bitmask;

    // --------------------------------
    bitset = 0x18;
    bitmask = 0x18;

    commons::clear_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0b00000000);

    // --------------------------------
    bitset = 0xFF;
    bitmask = 0x0F;

    commons::clear_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0xF0);

    // --------------------------------
    bitset = 0xFF;
    bitmask = 0xFF0;

    commons::clear_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0x0F);

    // --------------------------------
    bitset = 0x00;
    bitmask = 0xFF;

    commons::clear_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0);
}

TEST(CommonsTest, toggle_bits) {

    uint8_t bitset;
    uint8_t bitmask;

    // --------------------------------
    bitset = 0xFF;
    bitmask = 0x1;

    commons::toggle_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0xFE);

    // --------------------------------
    bitset = 0xF0;
    bitmask = 0x0F;

    commons::toggle_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0xFF);

    // --------------------------------
    bitset = 0x0F;
    bitmask = 0x0F;

    commons::toggle_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0);

    // --------------------------------
    bitset = 0x18;
    bitmask = 0x81;

    commons::toggle_bits(bitset, bitmask);

    EXPECT_EQ(bitset, 0x99);
}

TEST(CommonsTest, check_bits) {

    uint8_t bitset;
    uint8_t bitmask;

    // --------------------------------
    bitset = 0xFF;
    bitmask = 0x18;

    EXPECT_EQ(commons::check_bits(bitset, bitmask), true);

    // --------------------------------
    bitset = 0xF0;
    bitmask = 0x00;

    commons::check_bits(bitset, bitmask);

    EXPECT_EQ(commons::check_bits(bitset, bitmask), true);

    // --------------------------------
    bitset = 0x0F;
    bitmask = 0xFF;

    EXPECT_EQ(commons::check_bits(bitset, bitmask), false);

    // --------------------------------
    bitset = 0x99;
    bitmask = 0x11;

    EXPECT_EQ(commons::check_bits(bitset, bitmask), true);
}

TEST(CommonsTest, sizeof_array) {

    constexpr size_t array_size{25};

    uint8_t     array8[array_size];
    uint16_t    array16[array_size];
    uint32_t    array32[array_size];
    uint64_t    array64[array_size];
    float       arrayf[array_size];
    double      arrayd[array_size];

    EXPECT_EQ(commons::sizeof_array(array8), array_size);
    EXPECT_EQ(commons::sizeof_array(array16), array_size);
    EXPECT_EQ(commons::sizeof_array(array32), array_size);
    EXPECT_EQ(commons::sizeof_array(array64), array_size);
    EXPECT_EQ(commons::sizeof_array(arrayf), array_size);
    EXPECT_EQ(commons::sizeof_array(arrayd), array_size);
}

TEST(TypeSerializer, set_get) {

    uint8_t     base_value8{123};
    uint8_t     value8{};

    uint16_t    base_value16{12345};
    uint16_t    value16{};

    uint32_t    base_value32{1234567890U};
    uint32_t    value32{};

    uint64_t    base_value64{12345678901234567890ULL};
    uint64_t    value64{};

    float       base_valuef{123.123f};
    float       valuef{};

    double      base_valued{1234567890123456789.1234567890123456789};
    double      valued{};

    etl::TypeSerializer ts{};

    ts << base_value8;
    ts >> value8;

    EXPECT_EQ(value8, base_value8);

    ts << base_value16;
    ts >> value16;

    EXPECT_EQ(value16, base_value16);

    ts << base_value32;
    ts >> value32;

    EXPECT_EQ(value32, base_value32);

    ts << base_value64;
    ts >> value64;

    EXPECT_EQ(value64, base_value64);

    ts << base_valuef;
    ts >> valuef;

    EXPECT_EQ(valuef, base_valuef);

    ts << base_valued;
    ts >> valued;

    EXPECT_EQ(valued, base_valued);

}

TEST(TypeSerializer, clear) {

    uint8_t     base_value8{123};
    uint8_t     value8{};

    uint16_t    base_value16{12345};
    uint16_t    value16{};

    uint32_t    base_value32{1234567890U};
    uint32_t    value32{};

    uint64_t    base_value64{12345678901234567890ULL};
    uint64_t    value64{};

    float       base_valuef{123456789.123456789f};
    float       valuef{};

    double      base_valued{1234567890123456789.1234567890123456789};
    double      valued{};

    etl::TypeSerializer ts{};

    ts << base_value8;
    ts.clear();
    ts >> value8;

    EXPECT_EQ(value8, 0);

    ts << base_value16;
    ts.clear();
    ts >> value16;

    EXPECT_EQ(value16, 0);

    ts << base_value32;
    ts.clear();
    ts >> value32;

    EXPECT_EQ(value32, 0);

    ts << base_value64;
    ts.clear();
    ts >> value64;

    EXPECT_EQ(value64, 0);

    ts << base_valuef;
    ts.clear();
    ts >> valuef;

    EXPECT_EQ(valuef, 0);

    ts << base_valued;
    ts.clear();
    ts >> valued;

    EXPECT_EQ(valued, 0);

}
// TODO: Write tests for operator pack and unpack

TEST(TypeSerializer, unpack) {

    uint8_t     base_value8{123};
    uint8_t     value8{};

    uint16_t    base_value16{12345};
    uint16_t    value16{};

    uint32_t    base_value32{1234567890U};
    uint32_t    value32{};

    uint64_t    base_value64{12345678901234567890ULL};
    uint64_t    value64{};

    float       base_valuef{123456789.123456789f};
    float       valuef{};

    double      base_valued{1234567890123456789.1234567890123456789};
    double      valued{};

    // Big buffer just in case
    uint8_t buffer[16]{};

    etl::TypeSerializer ts{};

    ts << base_value8;
    ts.unpack(buffer, commons::sizeof_array(buffer));

    EXPECT_EQ(*reinterpret_cast<uint8_t*>(buffer), base_value8);

    ts << base_value16;
    ts.unpack(buffer, commons::sizeof_array(buffer));

    EXPECT_EQ(*reinterpret_cast<uint16_t*>(buffer), base_value16);

    ts << base_value32;
    ts.unpack(buffer, commons::sizeof_array(buffer));

    EXPECT_EQ(*reinterpret_cast<uint32_t*>(buffer), base_value32);

    ts << base_value64;
    ts.unpack(buffer, commons::sizeof_array(buffer));

    EXPECT_EQ(*reinterpret_cast<uint64_t*>(buffer), base_value64);

    ts << base_valuef;
    ts.unpack(buffer, commons::sizeof_array(buffer));

    EXPECT_EQ(*reinterpret_cast<float*>(buffer), base_valuef);

    ts << base_valued;
    ts.unpack(buffer, commons::sizeof_array(buffer));

    EXPECT_EQ(*reinterpret_cast<double*>(buffer), base_valued);
}

TEST(TypeSerializer, pack) {

    uint8_t     base_value8{123};
    uint8_t     value8{};

    uint16_t    base_value16{12345};
    uint16_t    value16{};

    uint32_t    base_value32{1234567890U};
    uint32_t    value32{};

    uint64_t    base_value64{12345678901234567890ULL};
    uint64_t    value64{};

    float       base_valuef{123456789.123456789f};
    float       valuef{};

    double      base_valued{1234567890123456789.1234567890123456789};
    double      valued{};

    // Big buffer just in case
    uint8_t buffer[8]{};
    uint8_t tmp_buff[8]{};

    etl::TypeSerializer ts{};

    memcpy(buffer, &base_value8, sizeof(base_value8));
    ts.pack(buffer, commons::sizeof_array(buffer));
    ts.unpack(tmp_buff, commons::sizeof_array(tmp_buff));

    EXPECT_EQ(memcmp(buffer, tmp_buff, commons::sizeof_array(buffer)), 0);

    memcpy(buffer, &base_value16, sizeof(base_value16));
    ts.pack(buffer, commons::sizeof_array(buffer));
    ts.unpack(tmp_buff, commons::sizeof_array(tmp_buff));

    EXPECT_EQ(memcmp(buffer, tmp_buff, commons::sizeof_array(buffer)), 0);

    memcpy(buffer, &base_value32, sizeof(base_value32));
    ts.pack(buffer, commons::sizeof_array(buffer));
    ts.unpack(tmp_buff, commons::sizeof_array(tmp_buff));

    EXPECT_EQ(memcmp(buffer, tmp_buff, commons::sizeof_array(buffer)), 0);

    memcpy(buffer, &base_value64, sizeof(base_value64));
    ts.pack(buffer, commons::sizeof_array(buffer));
    ts.unpack(tmp_buff, commons::sizeof_array(tmp_buff));

    EXPECT_EQ(memcmp(buffer, tmp_buff, commons::sizeof_array(buffer)), 0);

    memcpy(buffer, &base_valuef, sizeof(base_valuef));
    ts.pack(buffer, commons::sizeof_array(buffer));
    ts.unpack(tmp_buff, commons::sizeof_array(tmp_buff));

    EXPECT_EQ(memcmp(buffer, tmp_buff, commons::sizeof_array(buffer)), 0);

    memcpy(buffer, &base_valued, sizeof(base_valued));
    ts.pack(buffer, commons::sizeof_array(buffer));
    ts.unpack(tmp_buff, commons::sizeof_array(tmp_buff));

    EXPECT_EQ(memcmp(buffer, tmp_buff, commons::sizeof_array(buffer)), 0);
}