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
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res += vec;
        }
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(0.0f, 0.0f, 0.0f, 0.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = std::accumulate(testData.begin(), testData.end(), Eigen::Vector4f(0.0f, 0.0f, 0.0f, 0.0f));
        benchmark::ClobberMemory();
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
        benchmark::ClobberMemory();
        for (const auto& vec : testData) {
            res = res.cwiseProduct(vec);
        }
        benchmark::ClobberMemory();
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
        benchmark::ClobberMemory();
        res = std::accumulate(testData.begin(),
                              testData.end(),
                              Eigen::Vector4f(1.0f, 1.0f, 1.0f, 1.0f),
                              [](Eigen::Vector4f lhs, Eigen::Vector4f rhs) { return lhs.cwiseProduct(rhs);
        });
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

Eigen::Vector4f compute_1(float a, float b)
{

    Eigen::Vector4f const av(a, b, b, a);
    Eigen::Vector4f const bv(a, b, a, b);

    Eigen::Vector4f const cv(bv.cwiseProduct(av));
    Eigen::Vector4f const dv(av + cv);

    return dv;
}

Eigen::Vector4f compute_2(float a, float b)
{
    Eigen::Vector4f const c(b * a, b * a, b * a, b * a);
    Eigen::Vector4f const d = Eigen::Vector4f(a, a, a, a) + c;

    return d;
}

Eigen::Vector4f compute_3(Eigen::Vector4f a, Eigen::Vector4f b)
{
    return a.cwiseProduct(b) + a.cwiseProduct(b);
}

static void vec4_compute_1(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(1.0f, 1.0f, 1.0f, 1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_1(testData[0].x(), testData[1].y());
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_2(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(1.0f, 1.0f, 1.0f, 1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_2(testData[0].x(), testData[1].y());
        benchmark::ClobberMemory();
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_compute_3(benchmark::State& state) {
    const auto testData = prepare_test_data<Eigen::Vector4f>(state.range(0));

    Eigen::Vector4f res(1.0f, 1.0f, 1.0f, 1.0f);

    for (auto _ : state) {
        benchmark::ClobberMemory();
        res = compute_3(testData[0], testData[1]);
        benchmark::ClobberMemory();
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
BENCHMARK(vec4_compute_1)->Arg(2);
BENCHMARK(vec4_compute_2)->Arg(2);
BENCHMARK(vec4_compute_3)->Arg(2);

// Run the benchmark
BENCHMARK_MAIN();
