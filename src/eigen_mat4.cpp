#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <Eigen/Dense>

static void mat4_add(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data_eigen<Eigen::Matrix4f>(state.range(0));

    Eigen::Matrix4f res = Eigen::Matrix4f::Zero();

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data_eigen<Eigen::Matrix4f>(state.range(0));

    Eigen::Matrix4f res = Eigen::Matrix4f::Zero();

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data_eigen<Eigen::Matrix4f>(state.range(0));

    Eigen::Matrix4f res = Eigen::Matrix4f::Zero();

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
    const auto testData = prepare_mat4_test_data_eigen<Eigen::Matrix4f>(state.range(0));

    Eigen::Matrix4f res = Eigen::Matrix4f::Zero();

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(
            testData.begin(), testData.end(), Eigen::Matrix4f(), [](const Eigen::Matrix4f& lhs, const Eigen::Matrix4f& rhs) { return lhs * rhs; });
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