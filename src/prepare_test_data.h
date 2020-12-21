#include <numeric>
#include <random>
#include <vector>

template<typename T>
std::vector<T> prepare_test_data(std::size_t size) {
    std::vector<T> testData(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

    for (auto& vec : testData) {
        vec = T(distribution(gen), distribution(gen), distribution(gen), distribution(gen));
    }

    return testData;
}

template<typename T>
std::vector<T> prepare_test_data_init_list(std::size_t size) {
    std::vector<T> testData(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

    for (auto& vec : testData) {
        vec = T({distribution(gen), distribution(gen), distribution(gen), distribution(gen)});
    }

    return testData;
}

template<typename T>
std::vector<T> prepare_mat4_test_data(std::size_t size) {
    std::vector<T> testData(size);

    std::mt19937 gen;
    std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

    for (auto& vec : testData) {
        vec = T(distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen),
                distribution(gen));
    }

    return testData;
}

template<typename T>
std::vector<T> prepare_mat4_test_data_mango(std::size_t size) {
    std::vector<T> testData(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

    for (auto& vec : testData) {
        vec = T(distribution(gen));
    }

    return testData;
}

template<typename T>
std::vector<T> prepare_mat4_test_data_init_list(std::size_t size) {
    std::vector<T> testData(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

    for (auto& vec : testData) {
        vec = T({{distribution(gen), distribution(gen), distribution(gen), distribution(gen)},
                 {distribution(gen), distribution(gen), distribution(gen), distribution(gen)},
                 {distribution(gen), distribution(gen), distribution(gen), distribution(gen)},
                 {distribution(gen), distribution(gen), distribution(gen), distribution(gen)}});
    }

    return testData;
}

template<typename T>
std::vector<T> prepare_mat4_test_data_eigen(std::size_t size) {
    std::vector<T> testData(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

    for (auto& mat : testData) {
        mat << distribution(gen), distribution(gen), distribution(gen), distribution(gen), distribution(gen),
            distribution(gen), distribution(gen), distribution(gen), distribution(gen), distribution(gen),
            distribution(gen), distribution(gen), distribution(gen), distribution(gen), distribution(gen),
            distribution(gen);
    }

    return testData;
}
