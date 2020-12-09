#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <math.h>
#include <mathfu/matrix.h>

using mathfu::Matrix;

static void mat4_add(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data<Matrix<float, 4, 4>>(state.range(0));

    Matrix<float, 4, 4> res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data<Matrix<float, 4, 4>>(state.range(0));

    Matrix<float, 4, 4> res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void mat4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_mat4_test_data<Matrix<float, 4, 4>>(state.range(0));

    Matrix<float, 4, 4> res(0.0f);

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
    const auto testData = prepare_mat4_test_data<Matrix<float, 4, 4>>(state.range(0));

    Matrix<float, 4, 4> res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(testData.begin(),
                              testData.end(),
                              Matrix<float, 4, 4>(1.0f),
                              [](const Matrix<float, 4, 4>& lhs, const Matrix<float, 4, 4>& rhs) { return lhs * rhs; });
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