#define GLM_ENABLE_EXPERIMENTAL

#include <benchmark/benchmark.h>
#include <glm/glm.hpp>
#include <glm/gtx/type_aligned.hpp>
#include <numeric>
#include <random>

std::vector<glm::vec4> prepare_test_data(std::size_t size) {
    std::vector<glm::vec4> testData(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

    for (auto& vec : testData) {
        vec = glm::vec4(distribution(gen), distribution(gen), distribution(gen), distribution(gen));
    }

    return testData;
}

std::vector<glm::aligned_f32vec4> prepare_test_aligned_data(std::size_t size) {
    std::vector<glm::aligned_f32vec4> testData(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

    for (auto& vec : testData) {
        vec = glm::aligned_f32vec4(distribution(gen), distribution(gen), distribution(gen), distribution(gen));
    }

    return testData;
}

static void vec4_add(benchmark::State& state) {
    const auto testData = prepare_test_data(state.range(0));

    glm::vec4 res(0.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res += vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data(state.range(0));

    glm::vec4 res(0.0f);

    for (auto _ : state) {
        res = std::accumulate(testData.begin(), testData.end(), glm::vec4(0.0f));
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult(benchmark::State& state) {
    const auto testData = prepare_test_data(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res *= vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_mult_accumulate(benchmark::State& state) {
    const auto testData = prepare_test_data(state.range(0));

    glm::vec4 res(1.0f);

    for (auto _ : state) {
        res = std::accumulate(
            testData.begin(), testData.end(), glm::vec4(1.0f), [](glm::vec4 lhs, glm::vec4 rhs) { return lhs * rhs; });
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_aligned(benchmark::State& state) {
    const auto testData = prepare_test_aligned_data(state.range(0));

    glm::aligned_f32vec4 res(0.0f);

    for (auto _ : state) {
        for (const auto& vec : testData) {
            res += vec;
        }
    }
    benchmark::DoNotOptimize(res);
}

static void vec4_add_accumulate_aligned(benchmark::State& state) {
    const auto testData = prepare_test_aligned_data(state.range(0));

    glm::aligned_f32vec4 res(0.0f);

    for (auto _ : state) {
        res = std::accumulate(testData.begin(), testData.end(), glm::aligned_f32vec4(0.0f));
    }
    benchmark::DoNotOptimize(res);
}

// Register the function as a benchmark
BENCHMARK(vec4_add)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);
BENCHMARK(vec4_add_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);
BENCHMARK(vec4_mult)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);
BENCHMARK(vec4_mult_accumulate)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);
BENCHMARK(vec4_add_aligned)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);
BENCHMARK(vec4_add_accumulate_aligned)->Arg(2)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(1 << 12)->Arg(1 << 16)->Arg(1 << 20);

// Run the benchmark
BENCHMARK_MAIN();