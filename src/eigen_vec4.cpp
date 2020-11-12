#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <Eigen/core>

static void vec4_add(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        res = testData[0] + testData[1];
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res += vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        res = std::accumulate(testData.begin(), testData.end(), Eigen::Vector4f(0.0f, 0.0f, 0.0f, 0.0f));
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        res = testData[0] * testData[1];
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(1.0f, 1.0f, 1.0f, 1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res *= vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(1.0f, 1.0f, 1.0f, 1.0f);

    for (auto _ : state) {
        res = std::accumulate(testData.begin(),
                              testData.end(),
                              Eigen::Vector4f(1.0f, 1.0f, 1.0f, 1.0f),
                              [](Eigen::Vector4f lhs, Eigen::Vector4f rhs) {
            return lhs * rhs;
        });
    }
    benchmark::DoNotOptimize(res);
}
// Register the function as a benchmark
BENCHMARK(vec4_add)->Arg(2);
BENCHMARK(vec4_add_loop)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);
BENCHMARK(vec4_add_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);
BENCHMARK(vec4_mult)->Arg(2);
BENCHMARK(vec4_mult_loop)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);
BENCHMARK(vec4_mult_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);

// Run the benchmark
BENCHMARK_MAIN();