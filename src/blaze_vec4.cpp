#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <blaze/math/StaticVector.h>

using ::blaze::columnMajor;
using ::blaze::columnVector;

using VectorType = ::blaze::StaticVector<float, 4UL, columnVector>;

static void vec4_add(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1][1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(0.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res += vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(0.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res += vec[1];
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(0.0f);

    for (auto _ : state) {
        res = std::accumulate(testData.begin(), testData.end(), VectorType(0.0f));
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1][1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            benchmark::ClobberMemory();
            res *= vec;
            benchmark::ClobberMemory();
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            benchmark::ClobberMemory();
            res *= vec[1];
            benchmark::ClobberMemory();
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(1.0f);

    for (auto _ : state) {
        res = std::accumulate(testData.begin(), testData.end(), VectorType(1.0f), [](VectorType lhs, VectorType rhs) {
            return lhs * rhs;
        });
    }
    benchmark::DoNotOptimize(res);
}
// Register the function as a benchmark
BENCHMARK(vec4_add)->Arg(2);
BENCHMARK(vec4_add_scalar)->Arg(2);
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