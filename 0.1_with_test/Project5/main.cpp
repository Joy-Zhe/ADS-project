#include "head.h"
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;

template <typename T>
std::vector<Rectangle<T>> generateTestData(int n, T minWidth, T maxWidth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dis(minWidth, maxWidth);
    std::vector<Rectangle<T>> rectangles;
    for (int i = 0; i < n; i++) {
        T width = dis(gen);
        T height = dis(gen);
        rectangles.push_back(Rectangle<T>(width, height));
    }
    return rectangles;
}


int main(){
    std::ofstream outputFile("../../pyDiagram/results.csv");
    outputFile << "algorithm,n,height,time\n";
    for (int n = 10; n <= 10000; n += 100) {
        auto rectangles = generateTestData<double>(n, 1, 100);

        auto start = std::chrono::high_resolution_clock::now();
        auto test1 = FFDH<double>(rectangles, 100);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
        outputFile << "FFDH," << n << "," << test1 << "," << diff.count() << "\n";

        start = std::chrono::high_resolution_clock::now();
        auto test2 = NFDH<double>(rectangles, 100);
        end = std::chrono::high_resolution_clock::now();
        diff = end-start;
        outputFile << "NFDH," << n << "," << test2 << "," << diff.count() << "\n";

        start = std::chrono::high_resolution_clock::now();
        auto test3 = SF<double>(rectangles, 100);
        end = std::chrono::high_resolution_clock::now();
        diff = end-start;
        outputFile << "SF," << n << "," << test3 << "," << diff.count() << "\n";
    }
    outputFile.close();
    return 0;
}
