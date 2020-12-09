#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_SSE41

#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <glm/glm.hpp>
#include <glm/gtx/type_aligned.hpp>

static void mat4_add(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data<glm::mat4>(state.range(0));

    glm::mat4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data<glm::mat4>(state.range(0));

    glm::mat4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data<glm::mat4>(state.range(0));

    glm::mat4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res *= vec;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult_loop_accumulate(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data<glm::mat4>(state.range(0));

    glm::mat4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(
            testData.begin(), testData.end(), glm::mat4(1.0f), [](glm::mat4 lhs, glm::mat4 rhs) { return lhs * rhs; });
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

BENCHMARK(mat4_add)->Arg(2);
BENCHMARK(mat4_mult)->Arg(2);
BENCHMARK(mat4_mult_loop)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(mat4_mult_loop_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);

// Run the benchmark
BENCHMARK_MAIN();