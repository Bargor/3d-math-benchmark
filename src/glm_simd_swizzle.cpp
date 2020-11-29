#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_SSE41

#include <benchmark/benchmark.h>
#include <glm/glm.hpp>

#include "prepare_test_data.h"

glm::vec4 test_swizzle_1(glm::vec4 a, glm::vec4 b, glm::vec4 c) {
    return a.wwww() * b.xxyy() + (c.xxzz() - a).zzzz() * b.w;
}

glm::vec4 test_swizzle_2(glm::vec4 a, glm::vec4 b) {
    return a.xyyz() * b.wxxw() + a * b.w;
}

static void vec4_test_swizzle(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(3);

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = test_swizzle_1(testData[0], testData[1], testData[2]);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_test_swizzle_2(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(2);

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

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
