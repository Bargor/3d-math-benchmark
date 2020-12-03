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

inline VectorType compute_1(float a, float b)
{

    VectorType const av({a, b, b, a});
    VectorType const bv({a, b, a, b});

    VectorType const cv(bv * av);
    VectorType const dv(av + cv);

    return dv;
}

inline VectorType compute_2(float a, float b)
{
    VectorType const c(b * a);
    VectorType const d(a + c);

    return d;
}

inline VectorType compute_3(VectorType a, VectorType b)
{
    return a * b + a * b;
}

static void vec4_compute_1(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_1(testData[0][0], testData[1][1]);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_2(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_2(testData[0][0], testData[1][1]);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_3(benchmark::State& state) {
    const auto testData = prepare_test_data_init_list<VectorType>(state.range(0));

    VectorType res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_3(testData[0], testData[1]);
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

// Run the benchmark
BENCHMARK_MAIN();
