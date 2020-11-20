#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_AVX

#include <benchmark/benchmark.h>
#include <glm/glm.hpp>

#include "prepare_test_data.h"

static void vec4_add_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_scalar_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1].x;
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res += vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop_scalar_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res += vec.x;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f);

    for (auto _ : state) {
        res = std::accumulate(testData.begin(), testData.end(), glm::vec4(0.0f));
    }
    benchmark::DoNotOptimize(res);
}


static void vec4_mult_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_scalar_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1].x;
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res *= vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop_scalar_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res *= vec.x;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_accumulate_simd(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        res = std::accumulate(
            testData.begin(), testData.end(), glm::vec4(1.0f), [](glm::vec4 lhs, glm::vec4 rhs) { return lhs * rhs; });
    }
    benchmark::DoNotOptimize(res);
}
// Register the function as a benchmark
BENCHMARK(vec4_add_simd)->Arg(2);
BENCHMARK(vec4_add_scalar_simd)->Arg(2);
BENCHMARK(vec4_add_loop_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_add_loop_scalar_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_add_accumulate_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_mult_simd)->Arg(2);
BENCHMARK(vec4_mult_scalar_simd)->Arg(2);
BENCHMARK(vec4_mult_loop_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_mult_loop_scalar_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_mult_accumulate_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);

// Run the benchmark
BENCHMARK_MAIN();