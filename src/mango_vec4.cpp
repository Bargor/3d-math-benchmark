#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <mango/mango.hpp>

static void vec4_add(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1].y;
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_loop(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(0.0f);

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
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res += vec.y;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(testData.begin(), testData.end(), mango::float32x4(0.0f));
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1].y;
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_loop(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(1.0f);

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
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res *= vec.y;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(testData.begin(),
                              testData.end(),
                              mango::float32x4(1.0f),
                              [](mango::float32x4 lhs, mango::float32x4 rhs) {
            return lhs * rhs;
        });
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

mango::float32x4 compute_1(float a, float b)
{

    mango::float32x4 const av(a, b, b, a);
    mango::float32x4 const bv(a, b, a, b);

    mango::float32x4 const cv(bv * av);
    mango::float32x4 const dv(av + cv);

    return dv;
}

mango::float32x4 compute_2(float a, float b)
{
    mango::float32x4 const c(b * a);
    mango::float32x4 const d(a + c);

    return d;
}

mango::float32x4 compute_3(mango::float32x4 a, mango::float32x4 b)
{
    return a * b + a * b;
}

static void vec4_compute_1(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_1(testData[0].x, testData[1].y);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_2(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_2(testData[0].x, testData[1].y);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_3(benchmark::State& state) {
    const auto testData = prepare_test_data<mango::float32x4>(state.range(0));

    mango::float32x4 res(1.0f);

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
