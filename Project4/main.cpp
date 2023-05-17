#include <iostream>
#include <random>
#include <chrono>
#include "base.h"
#include "listBasedUpgrade.h"
using namespace std::chrono;

int main() {
    const int num_instances = 100;
    const int max_value = 1000;
    const int max_weight = 1000;
    const int num_items = 5000;
    const int capacity = 1000;

    // 使用随机数生成器生成价值和重量
    default_random_engine generator;
    uniform_int_distribution<int> value_distribution(1, max_value);
    uniform_int_distribution<int> weight_distribution(1, max_weight);

    for (int instance = 1; instance <= num_instances; instance++) {
        vector<int> values(num_items), weights(num_items);
        for (int i = 0; i < num_items; ++i) {
            values[i] = value_distribution(generator);
            weights[i] = weight_distribution(generator);
        }

        auto start_dp = high_resolution_clock::now();
        int max_value_dp = knapsack(values, weights, capacity);
        auto end_dp = high_resolution_clock::now();
        auto duration_dp = duration_cast<milliseconds>(end_dp - start_dp).count();

        auto start_improved = high_resolution_clock::now();
        int max_value_improved = newKnapsack(values, weights, capacity);
        auto end_improved = high_resolution_clock::now();
        auto duration_improved = duration_cast<milliseconds>(end_improved - start_improved).count();

        cout << "Entity" << instance << ":\n";
        cout << "Origin:" << duration_dp << " ms, maxValue: " << max_value_dp << endl;
        cout << "Upgrade:" << duration_improved << " ms, maxValue: " << max_value_improved << endl;
        cout << "------" << endl;
    }

    return 0;
}







