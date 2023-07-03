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

void writeRectangleInfoToCSV(const string& algorithm, int n, const vector<Rectangle>& rectangles) {
    std::ofstream outputFile("../../pyDiagram/" + algorithm + ".csv",ios::app);
    if (outputFile.is_open()) {
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
    std::ofstream outputFile("../../pyDiagram/SF.csv");
    outputFile.close();
    std::ofstream outputFile1("../../pyDiagram/FFDH.csv");
    outputFile1.close();
    std::ofstream outputFile2("../../pyDiagram/NFDH.csv");
    outputFile2.close();
    int n;
    double w;
    cout << "The number of rectangles:";
    cin >> n;
    cout << "MAX Width:";
    cin >> w;
    n = 12;
    auto rectangles = generateTestData(n, 0, w);
//    vector<Rectangle> rectangles;
//    rectangles.push_back(Rectangle(0.99, 0.2));
//    rectangles.push_back(Rectangle(0.7, 0.3));
//    rectangles.push_back(Rectangle(0.4, 0.6));
//    rectangles.push_back(Rectangle(0.3, 0.15));
//    rectangles.push_back(Rectangle(0.2, 0.2));
//    rectangles.push_back(Rectangle(0.1, 0.1));
//    rectangles.push_back(Rectangle(0.05, 0.2));
//    rectangles.push_back(Rectangle(0.15, 0.25));
//    rectangles.push_back(Rectangle(0.45, 0.3));
//    rectangles.push_back(Rectangle(0.6, 0.6));
//    rectangles.push_back(Rectangle(0.25, 0.15));
//    rectangles.push_back(Rectangle(0.25, 0.15));

    double test1;
    auto test1R = FFDH(rectangles, 1, test1);
    writeRectangleInfoToCSV("FFDH", n, test1R);

    double test2;
    auto test2R = NFDH(rectangles, 1, test2);
    writeRectangleInfoToCSV("NFDH", n, test2R);

    double test3;
    auto test3R = SF(rectangles, 1, test3);
    writeRectangleInfoToCSV("SF", n, test3R);

    std::ofstream outputResults("../../pyDiagram/results.csv");
    outputResults << "algorithm,n,height,time\n";
    for (int i = 10; i <= 10000; i += 10) {
        auto rectangle = generateTestData(i, 0, w);

        auto start = std::chrono::high_resolution_clock::now();
        double testFFDH;
        auto _testFFDH = FFDH(rectangle, 1, testFFDH);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
        outputResults << "FFDH," << i << "," << testFFDH << "," << diff.count() << "\n";
//        outputResults << "FFDH," << i << "," << testFFDH << "," << diff.count() / (i * i) << "\n";

        start = std::chrono::high_resolution_clock::now();
        double testNFDH;
        auto _testNFDH = NFDH(rectangle, 1, testNFDH);
        end = std::chrono::high_resolution_clock::now();
        diff = end-start;
        outputResults << "NFDH," << i << "," << testNFDH << "," << diff.count() << "\n";
//        outputResults << "NFDH," << i << "," << testNFDH << "," << diff.count() / (i * log(i)) << "\n";

        // Test the Coffman et al. algorithm
        double testSF;
        start = std::chrono::high_resolution_clock::now();
        auto _testSF  = SF(rectangle, 1, testSF);
        end = std::chrono::high_resolution_clock::now();
        diff = end-start;
        outputResults << "SF," << i << "," << testSF << "," << diff.count() << "\n";
//        outputResults << "SF," << i << "," << testSF << "," << diff.count() / (i * i) << "\n";
    }
    outputResults.close();
    return 0;
}
