#include "prepare_test_data.h"

#include <benchmark/benchmark.h>
#include <math.h>
#include <mathfu/vector.h>

using mathfu::Vector;

static void vec4_add(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] + testData[1].x;
        benchmark::ClobberMemory();
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
        benchmark::ClobberMemory();
        res = testData[0] * testData[1];
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_scalar(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = testData[0] * testData[1].x;
        benchmark::ClobberMemory();
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

Vector<float, 4> compute_1(float a, float b)
{

    Vector<float, 4> const av(a, b, b, a);
    Vector<float, 4> const bv(a, b, a, b);

    Vector<float, 4> const cv(bv * av);
    Vector<float, 4> const dv(av + cv);

    return dv;
}

Vector<float, 4> compute_2(float a, float b)
{
    Vector<float, 4> const c(b * a);
    Vector<float, 4> const d(a + c);

    return d;
}

Vector<float, 4> compute_3(Vector<float, 4> a, Vector<float, 4> b)
{
    return a * b + a * b;
}

static void vec4_compute_1(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_1(testData[0].x, testData[1].y);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_2(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_2(testData[0].x, testData[1].y);
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_3(benchmark::State& state) {
    const auto testData = prepare_test_data<Vector<float, 4>>(state.range(0));

    Vector<float, 4> res(1.0f);

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
