#include "head.h"
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;

std::vector<Rectangle> generateTestData(int n, double minWidth, double maxWidth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution dis(minWidth, maxWidth);
    std::vector<Rectangle> rectangles;
    for (int i = 0; i < n; i++) {
        double width = dis(gen);
        double height = dis(gen);
        rectangles.push_back(Rectangle(width, height));
    }
    return rectangles;
}

void writeRectangleInfoToCSV(const string& algorithm, int n, const vector<Rectangle>& rectangles, double height, double time) {
    std::ofstream outputFile("../../pyDiagram/results.csv",ios::app);
    if (outputFile.is_open()) {
//        outputFile << "algorithm" << "," << "n" << "," << "height" << "," << "time" << "\n";
//        outputFile << algorithm << "," << n << "," << height << "," << time << "\n";
        outputFile << "Rectangle,Width,Height,X,Y\n";
        for (const auto& rect : rectangles) {
            outputFile << "R," << rect.width << "," << rect.height << "," << rect.x << "," << rect.y << "\n";
        }
        outputFile.close();
    } else {
        std::cout << "Unable to open the CSV file." << std::endl;
    }
}

int main(){
//    std::ofstream outputFile("results.csv");
//    std::ofstream outputFile("../../pyDiagram/results.csv");
//    outputFile << "algorithm,n,height,time\n";
    std::ofstream outputFile("../../pyDiagram/results.csv");
    outputFile.close();
    int n;
    cin >> n;
        auto rectangles = generateTestData(n, 0, 1);
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
//        outputFile << "FFDH," << n << "," << test1 << "," << diff.count() << "\n";
//
//        start = std::chrono::high_resolution_clock::now();
//        auto test2 = NFDH(rectangles, 100);
//        end = std::chrono::high_resolution_clock::now();
//        diff = end-start;
//        outputFile << "NFDH," << n << "," << test2 << "," << diff.count() << "\n";

        start = std::chrono::high_resolution_clock::now();
        double test3;
        auto test3R = SF(rectangles, 1, test3);
        end = std::chrono::high_resolution_clock::now();
        diff = end-start;
//        outputFile << "SF," << n << "," << test3 << "," << diff.count() << "\n";
        writeRectangleInfoToCSV("SF", n, test3R, test3, diff.count());

    return 0;
}
