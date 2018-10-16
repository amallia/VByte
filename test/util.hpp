#pragma once
#include <vector>
#include <random>

// Run on (4 X 2400 MHz CPU s)
// CPU Caches:
//   L1 Data 32K (x2)
//   L1 Instruction 32K (x2)
//   L2 Unified 262K (x2)
//   L3 Unified 3145K (x1)
// ------------------------------------------------------
// Benchmark               Time           CPU Iterations
// ------------------------------------------------------
// encode/1024         17841 ns      17791 ns      37858
// encode/4096         57985 ns      57882 ns      10389
// encode/32768       445033 ns     441555 ns       1595
// encode/262144     3515639 ns    3503136 ns        199
// encode/1048576   17368479 ns   17310684 ns         38
// decode/1024         10837 ns      10758 ns      64093
// decode/4096         35875 ns      33481 ns      22402
// decode/32768       244209 ns     230140 ns       2983
// decode/262144     1864286 ns    1812599 ns        372
// decode/1048576    9243612 ns    9184225 ns         71


std::vector<uint32_t> generate_random_vector(size_t n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<uint32_t> values(n);
    std::uniform_int_distribution<> dis(uint32_t(0));
    std::generate(values.begin(), values.end(), [&](){ return dis(gen); });
    return values;
}