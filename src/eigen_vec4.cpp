#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <Eigen/Dense>

static void vec4_add(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
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
        benchmark::ClobberMemory();
        res = testData[0].cwiseProduct(testData[1]);
        benchmark::ClobberMemory();
    }
        
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1].y();
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(1.0f, 1.0f, 1.0f, 1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res = res.cwiseProduct(vec);
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(1.0f, 1.0f, 1.0f, 1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res *= vec[1];
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
                              [](Eigen::Vector4f lhs, Eigen::Vector4f rhs) { return lhs.cwiseProduct(rhs);
        });
    }
    benchmark::DoNotOptimize(res);
}
// Register the function as a benchmark
BENCHMARK(vec4_add)->Arg(2);
BENCHMARK(vec4_add_loop)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_add_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_mult)->Arg(2);
BENCHMARK(vec4_mult_scalar)->Arg(2);
BENCHMARK(vec4_mult_loop)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_mult_loop_scalar)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);
BENCHMARK(vec4_mult_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(1 << 10);

// Run the benchmark
BENCHMARK_MAIN();