/**
 * Copyright 2018-present Antonio Mallia
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

#include "vbyte/vbyte.hpp"
#include "util.hpp"

using namespace vb;
using ::testing::ContainerEq;


TEST(vbyte, empty) {
    std::vector<uint8_t> buf;
    std::vector<uint32_t> empty_vector;
    vbyte::encode(buf, empty_vector);

    EXPECT_EQ(buf.size(), 0);
}

TEST(vbyte, single_value) {
    {
        std::vector<uint8_t> buf;
        auto value = uint32_t(0);
        vbyte::encode(buf, value);
        EXPECT_EQ(buf.size(), 1);

        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
        EXPECT_EQ(decoded_values[0], value);
    }
    {
        std::vector<uint8_t> buf;
        auto value = uint32_t(1);
        vbyte::encode(buf, value);
        EXPECT_EQ(buf.size(), 1);

        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
        EXPECT_EQ(decoded_values[0], value);
    }
    {
        std::vector<uint8_t> buf;
        auto value = uint32_t(127);
        vbyte::encode(buf, value);
        EXPECT_EQ(buf.size(), 1);

        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
        EXPECT_EQ(decoded_values[0], value);
    }
    {
        std::vector<uint8_t> buf;
        auto value = uint32_t(128);
        vbyte::encode(buf, value);
        EXPECT_EQ(buf.size(), 2);

        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
        EXPECT_EQ(decoded_values[0], value);
    }
    {
        std::vector<uint8_t> buf;
        auto value = uint32_t(500);
        vbyte::encode(buf, value);
        EXPECT_EQ(buf.size(), 2);

        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
        EXPECT_EQ(decoded_values[0], value);
    }
    {
        std::vector<uint8_t> buf;
        auto value = uint32_t(16383);
        vbyte::encode(buf, value);
        EXPECT_EQ(buf.size(), 2);

        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
        EXPECT_EQ(decoded_values[0], value);
    }
    {
        std::vector<uint8_t> buf;
        auto value = uint32_t(16384);
        vbyte::encode(buf, value);
        EXPECT_EQ(buf.size(), 3);

        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
        EXPECT_EQ(decoded_values[0], value);
    }
    {
        std::vector<uint8_t> buf;
        auto value = uint32_t(268435455);
        vbyte::encode(buf, value);
        EXPECT_EQ(buf.size(), 4);

        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
        EXPECT_EQ(decoded_values[0], value);
    }
    {
        std::vector<uint8_t> buf;
        auto value = uint32_t(-1);
        vbyte::encode(buf, value);
        EXPECT_EQ(buf.size(), 5);

        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
        EXPECT_EQ(decoded_values[0], value);
    }
}

TEST(vbyte, fuzzy) {
    std::vector<uint8_t> buf;
    std::vector<uint32_t> values = generate_random_vector(10000);
    vbyte::encode(buf, values);
    std::vector<uint32_t> decoded_values;
    vbyte::decode(decoded_values, buf);
    EXPECT_EQ(decoded_values.size(), values.size());
    EXPECT_THAT(decoded_values, ContainerEq(values));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
