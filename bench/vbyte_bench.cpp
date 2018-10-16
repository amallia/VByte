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


// 2018-10-16 03:07:18
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
// encode/1024         16018 ns      15960 ns      43754
// encode/4096         55327 ns      55183 ns      11825
// encode/32768       427390 ns     426373 ns       1632
// encode/262144     3487180 ns    3439903 ns        206
// encode/1048576   14013011 ns   13969592 ns         49
// decode/1024         11048 ns      10934 ns      64067
// decode/4096         31099 ns      30815 ns      23624
// decode/32768       209016 ns     208083 ns       3366
// decode/262144     1898773 ns    1891326 ns        371
// decode/1048576    8605324 ns    8574962 ns         78
