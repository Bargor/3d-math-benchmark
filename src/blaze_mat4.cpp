#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <blaze/math/StaticMatrix.h>

using ::blaze::columnMajor;
using ::blaze::columnVector;

using MatrixType = ::blaze::StaticMatrix<float, 4, 4, columnVector>;

static void mat4_add(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data_init_list<MatrixType>(state.range(0));

    MatrixType res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data_init_list<MatrixType>(state.range(0));

    MatrixType res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data_init_list<MatrixType>(state.range(0));

    MatrixType res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        for (const auto& mat : testData) {
            res *= mat;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult_loop_accumulate(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data_init_list<MatrixType>(state.range(0));

    MatrixType res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(
            testData.begin(), testData.end(), MatrixType(1.0f), [](MatrixType lhs, MatrixType rhs) { return lhs * rhs; });
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