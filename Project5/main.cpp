#include <iostream>
#include "SF.h"

int main() {
    // Create a vector of rectangles
    std::vector<Rectangle<double>> rectangles;
    rectangles.emplace_back(4, 2);
    rectangles.emplace_back(2, 6);
    rectangles.emplace_back(4, 4);
    rectangles.emplace_back(6, 3);
    rectangles.emplace_back(3, 2);

    // The width of the bin
    double W = 6.0;


    // Test the Coffman et al. algorithm
    double ans = SF(rectangles, W);
    std::cout << ans << std::endl;
    return 0;
}
