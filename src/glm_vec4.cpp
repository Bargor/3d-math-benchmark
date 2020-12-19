#define GLM_ENABLE_EXPERIMENTAL

#include <benchmark/benchmark.h>
#include <glm/glm.hpp>
#include <glm/gtx/type_aligned.hpp>

#include "prepare_test_data.h"

static void vec4_add(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1].x;
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res += vec;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res += vec.x;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(testData.begin(), testData.end(), glm::vec4(0.0f));
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1].y;
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res *= vec;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res *= vec.x;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::vec4>(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(
            testData.begin(), testData.end(), glm::vec4(1.0f), [](glm::vec4 lhs, glm::vec4 rhs) { return lhs * rhs; });
        benchmark::ClobberMemory();
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

static void vec4_add_aligned(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::aligned_f32vec4>(state.range(0));

    glm::aligned_f32vec4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res += vec;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate_aligned(benchmark::State& state) {
    const auto testData = prepare_test_data<glm::aligned_f32vec4>(state.range(0));

    glm::aligned_f32vec4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(testData.begin(), testData.end(), glm::aligned_f32vec4(0.0f));
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

// Register the function as a benchmark
BENCHMARK(vec4_add)->Arg(2);
BENCHMARK(vec4_add_scalar)->Arg(2);
BENCHMARK(vec4_add_loop)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_add_loop_scalar)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_add_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_mult)->Arg(2);
BENCHMARK(vec4_mult_scalar)->Arg(2);
BENCHMARK(vec4_mult_loop)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_mult_loop_scalar)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_mult_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_compute_1)->Arg(2);
BENCHMARK(vec4_compute_2)->Arg(2);
BENCHMARK(vec4_compute_3)->Arg(2);
BENCHMARK(vec4_add_aligned)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_add_accumulate_aligned)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);

// Run the benchmark
BENCHMARK_MAIN();
