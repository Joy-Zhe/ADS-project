#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef vector<pair<int, int>> STATUS;

//感觉有点像前缀和

int newKnapsack(const vector<int> value, const vector<int>& weights, int capacity) {//价值 重量 容量
    int n = value.size();
    STATUS status; //总状态列表
    status.emplace_back(0, 0);
    for(int i = 0; i < n; i++) {
        STATUS newStatus;//每个物品的状态可能
        for(const auto& it:status) {//根据已有的状态合并新物品的状态
            int newWeight = it.first + weights[i];//更新该情况的总重
            int newValue = it.second + value[i];//更新该情况的总价值
            if(newWeight <= capacity) {//可用，加入总状态表
                newStatus.emplace_back(newWeight, newValue);
            }
        }

        for(const auto& newSt:newStatus) {//遍历该物品的状态表
            bool dominated = false;//没用
            for(auto& St:status) {//遍历总状态表，查找该物品的使用是否更优
                if(St.first <= newSt.first && St.second >= newSt.second) {//新状态总重大，价值小，丢了
                    dominated = true;
                    break;
                }
                if(St.first >= newSt.first && St.second <= newSt.second) {//总重小，价值大，要了
                    St = newSt;
                    dominated = true;
                    break;
                }
            }
            if(!dominated) {
                status.push_back(newSt); //add new status
            }
        }
    }
    int maxValue = -1;
    for(const auto& it:status) {
        maxValue = max(it.second, maxValue);
    }

    return maxValue;
}
