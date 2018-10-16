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
#pragma once

namespace vb {

class vbyte {

    static constexpr size_t MAX_VBYTE_LEN = 5;

   public:
    static void encode(std::vector<uint8_t> &out, uint32_t value) {
        out.reserve(MAX_VBYTE_LEN);
        while (value >= 128) {
            out.push_back(0x80 | (value & 0x7f));
            value >>= 7;
        }
        out.push_back(value);
    }

    /*
     * Encode a vector of values into the buffer
     */
    static void encode(std::vector<uint8_t> &out, const std::vector<uint32_t> &in) {
        out.reserve(in.size() * MAX_VBYTE_LEN);
        for (auto &&value : in) {
            encode(out, value);
        }
    }

    static const uint8_t *decode(std::vector<uint32_t> &out, const uint8_t *in, size_t n) {}

    /*
     * Decode
     */
    static void decode(std::vector<uint32_t> &out, const std::vector<uint8_t> &in) {
        size_t n = 0;
        while (in.size() - n >= MAX_VBYTE_LEN) {
            uint8_t  c     = in[n];
            uint32_t value = (c & 0x7F);
            if (c < 128) {
                out.push_back(value);
                n += 1;
                continue;
            }

            c = in[n + 1];
            value |= (c & 0x7F) << 7;
            if (c < 128) {
                out.push_back(value);
                n += 2;
                continue;
            }

            c = in[n + 2];
            value |= (c & 0x7F) << 14;
            if (c < 128) {
                out.push_back(value);
                n += 3;
                continue;
            }

            c = in[n + 3];
            value |= (c & 0x7F) << 21;
            if (c < 128) {
                out.push_back(value);
                n += 4;
                continue;
            }

            c = in[n + 4];
            value |= (c & 0x7F) << 28;
            if (c < 128) {
                out.push_back(value);
                n += 5;
                continue;
            }
        }
        while (n < in.size()) {
            size_t   shift = 0;
            uint32_t value = 0;
            while (true) {
                uint8_t c = in[n];
                value |= (c & 0x7f) << shift;
                shift += 7;
                n += 1;
                if (c < 128) {
                    out.push_back(value);
                    break;
                }
            }
        }
    }
};

} // namespace vb