#include <benchmark/benchmark.h>
#include <mango/mango.hpp>

#include "prepare_test_data.h"

mango::float32x4 test_swizzle_1(mango::float32x4 a, mango::float32x4 b, mango::float32x4 c) {
    return a.wwww * b.xxyy + (c.xxzz - a).zzzz * b.w;
}

mango::float32x4 test_swizzle_2(mango::float32x4 a, mango::float32x4 b) {
    return a.xyyz * b.wxxw + a * b.w;
}

static void vec4_test_swizzle(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(3);

    mango::float32x4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = test_swizzle_1(testData[0], testData[1], testData[2]);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_test_swizzle_2(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(2);

    mango::float32x4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = test_swizzle_2(testData[0], testData[1]);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

BENCHMARK(vec4_test_swizzle)->Arg(3);
BENCHMARK(vec4_test_swizzle_2)->Arg(2);

// Run the benchmark
BENCHMARK_MAIN();