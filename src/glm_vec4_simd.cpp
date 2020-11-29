#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_SSE41

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

glm::vec4 compute_1(float a, float b)
{

    glm::vec4 const av(a, b, b, a);
    glm::vec4 const bv(a, b, a, b);

    glm::vec4 const cv(bv * av);
    glm::vec4 const dv(av + cv);

    return dv;
}

glm::vec4 compute_2(float a, float b)
{
    glm::vec4 const c(b * a);
    glm::vec4 const d(a + c);

    return d;
}

glm::vec4 compute_3(glm::vec4 a, glm::vec4 b)
{
    return a * b + a * b;
}

static void vec4_compute_1(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_1(testData[0].x, testData[1].y);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_2(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_2(testData[0].x, testData[1].y);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_3(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_3(testData[0], testData[1]);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}


// Register the function as a benchmark
BENCHMARK(vec4_add_simd)->Arg(2);
BENCHMARK(vec4_add_scalar_simd)->Arg(2);
BENCHMARK(vec4_add_loop_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_add_loop_scalar_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_add_accumulate_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_mult_simd)->Arg(2);
BENCHMARK(vec4_mult_scalar_simd)->Arg(2);
BENCHMARK(vec4_mult_loop_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_mult_loop_scalar_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_mult_accumulate_simd)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_compute_1)->Arg(2);
BENCHMARK(vec4_compute_2)->Arg(2);
BENCHMARK(vec4_compute_3)->Arg(2);

// Run the benchmark
BENCHMARK_MAIN();
