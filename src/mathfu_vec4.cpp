#define GLM_ENABLE_EXPERIMENTAL

#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <math.h>
#include <mathfu/vector.h>

using mathfu::Vector;

static void vec4_add(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        res = testData[0] + testData[1];
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        res = testData[0] + testData[1].x;
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res += vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res += vec.x;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f);

    for (auto _ : state) {
        res = std::accumulate(testData.begin(), testData.end(), Vector<float, 4>(0.0f));
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        res = testData[0] * testData[1];
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        res = testData[0] * testData[1].x;
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res *= vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res *= vec.x;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(1.0f);

    for (auto _ : state) {
        res = std::accumulate(testData.begin(),
                              testData.end(),
                              Vector<float, 4>(1.0f),
                              [](Vector<float, 4> lhs, Vector<float, 4> rhs) { return lhs * rhs; });
    }
    benchmark::DoNotOptimize(res);
}

// Register the function as a benchmark
BENCHMARK(vec4_add)->Arg(2);
BENCHMARK(vec4_mult_scalar)->Arg(2);
BENCHMARK(vec4_add_loop)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_add_loop_scalar)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_add_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_mult)->Arg(2);
BENCHMARK(vec4_mult_scalar)->Arg(2);
BENCHMARK(vec4_mult_loop)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_mult_loop_scalar)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);
BENCHMARK(vec4_mult_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12);

// Run the benchmark
BENCHMARK_MAIN();