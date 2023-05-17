#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(const vector<int>& value, const vector<int>& weights, int capacity) {
    int n = value.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= capacity; j++) {
            if(weights[i - 1] <= j)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + value[i - 1]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][capacity];
}
