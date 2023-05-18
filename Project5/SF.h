#pragma once

#include <algorithm>
#include <vector>
using namespace std;

template<typename T>
class Rectangle {
public:
    T width;
    T height;
    Rectangle(T w, T h) : width(w), height(h) {}
};

template<typename T>
class Layer {
public:
    T width;
    T height;
    Layer(T w, T h) : width(w), height(h) {}
};

template<typename T>
bool cmp (const Rectangle<T> &t1, const Rectangle<T> &t2) {
    return t1.height > t2.height;
}

template<typename T>
[[maybe_unused]] vector<Layer<T>> FFDH(vector<Rectangle<T>> &rectangles, T binWidth) {
    vector<Layer<T>> layers;
    sort(rectangles.begin(), rectangles.end(), cmp<T>);
    for(auto &r:rectangles) {
        bool f = false;
        for(auto &l:layers) {
            if(l.width + r.width <= binWidth) {
                l.width += r.width; //can fit in, add the rectangle to this layer
                l.height = max(l.height, r.height); //update the height of the present layer
                f = true; //added
                break;
            }
        }
        if(!f)
            layers.push_back(Layer<T>(r.width, r.height)); //cannot add, new a layer
    }

    return layers;
}

template<typename T>
T SF(vector<Rectangle<T>> &rectangles, T binWidth) {
    T height;
    vector<Rectangle<T>> upperR;
    vector<Rectangle<T>> lowerR;
    double m = 0;
    for(auto &r:rectangles) {
        m = max(m, 1.0 * binWidth / r.width);
    }
    for(auto &r:rectangles) {
        if(r.width > binWidth / m) {
            upperR.push_back(r);
        } else {
            lowerR.push_back(r);
        }
    }
//    sort(upperR.begin(), upperR.end(), cmp);
//    sort(lowerR.begin(), lowerR.end(), cmp);
//no need to sort
    vector<Layer<T>> layers = FFDH(upperR, binWidth);//FFDH the larger rectangles
    vector<Layer<T>> leftSpace = FFDH(lowerR, binWidth / ( m + 2 ));//FFDH the smaller rectangles
    //no need to rearrange the layers, to calculate the height, just need compare(maybe)
    T wideHeight = 0; //calculate the height cannot insert
    T narrowHeight = 0;
    for(auto &l:layers) {
        if(l.width > binWidth * (m + 1) / (m + 2)) {
            wideHeight += l.height;
        } else {
            narrowHeight += l.height;
        }
    }
    cout << wideHeight << " " << narrowHeight << endl;
    T h = 0;
    for(auto &l:leftSpace) {
        h += l.height;
    }
    cout << h << endl;
    if(h > narrowHeight)
        return (wideHeight + h);
    return (narrowHeight + wideHeight);
}