#include "SkipList.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

void test(const int &size, std::ofstream &outputFile) {
    srand(time(nullptr));

    SkipList skipList;

    const int largeSize = size;

    // test insertion
    std::vector<int> insertData;
    srand(time(nullptr));
    for (int i = 0; i < largeSize; i++) {
        insertData.push_back(rand() % largeSize);
    }

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < insertData.size(); i++) {
        skipList.insert(insertData[i]);
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputFile << size << "," << duration.count();

    // test deletion
    std::vector<int> removeData;
    srand(time(nullptr));
    for (int i = 0; i < largeSize; i++) {
        removeData.push_back(rand() % largeSize);
    }

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < removeData.size(); i++) {
        skipList.remove(removeData[i]);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputFile << "," << duration.count();

    // test search
    std::vector<int> searchData;
    srand(time(nullptr));
    for (int i = 0; i < largeSize; i++) {
        searchData.push_back(rand() % largeSize);
    }

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < searchData.size(); i++) {
        skipList.search(searchData[i]);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputFile << "," << duration.count() << std::endl;
}

int main() {
    std::ofstream outputFile("result.csv");
    outputFile << "DataSize,InsertionTime,RemovalTime,SearchTime" << std::endl;
    int step = 10;
    for (int i = 10; i < 1000000; i += step) {
        if(i / step >= 10)
            step *= 10;
        if(step >= 1000)
            step = 1000;
        test(i, outputFile);
    }

    outputFile.close();

    return 0;
}
