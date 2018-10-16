#include "benchmark/benchmark.h"
#include "vbyte/vbyte.hpp"
#include "test/util.hpp"

using namespace vb;

static void encode(benchmark::State &state) {

    while (state.KeepRunning()) {
        state.PauseTiming();
        std::vector<uint32_t> values = generate_random_vector(state.range(0));
        state.ResumeTiming();
        std::vector<uint8_t>  buf;
        vbyte::encode(buf, values);
    }
}
BENCHMARK(encode)->Range(1<<10, 1<<20);

static void decode(benchmark::State &state) {
    while (state.KeepRunning()) {
        state.PauseTiming();
        std::vector<uint8_t>  buf;
        std::vector<uint32_t> values = generate_random_vector(state.range(0));
        vbyte::encode(buf, values);
        state.ResumeTiming();
        std::vector<uint32_t> decoded_values;
        vbyte::decode(decoded_values, buf);
    }
}

BENCHMARK(decode)->Range(1<<10, 1<<20);

BENCHMARK_MAIN();


// 2018-10-16 02:11:54
// Running ./bench/vbyte_bench
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
//
