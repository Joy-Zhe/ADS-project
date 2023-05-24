#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Rectangle {
public:
    double width;
    double height;
    double x;
    double y;
    Rectangle(double w, double h) : width(w), height(h), x(-1), y(-1) {}
};

class Layer {
public:
    double width;
    double height;
    double x;
    double y;
    vector<Rectangle> rectangles;
    Layer(double w, double h, double X, double Y) : width(w), height(h), x(X), y(Y) {}
};

bool cmp (const Rectangle &t1, const Rectangle &t2) {
    return t1.height > t2.height;
}

vector<Layer> FFDH_(vector<Rectangle> &rectangles, const double &binWidth, const double &layerX, const double &layerY) {
    vector<Layer> layers;
    sort(rectangles.begin(), rectangles.end(), cmp);
//    T curX = 0;
    double curY = layerY;
    for(auto &r:rectangles) {
        bool f = false;
        for(auto &l:layers) {
            if(l.width + r.width <= binWidth && r.height <= l.height) {
                //set the position of this rectangle
                r.x = l.x + l.width;
                r.y = l.y;
                l.width += r.width; //can fit in, add the rectangle to this layer
                l.rectangles.push_back(r);
//                l.height = max(l.height, r.height); //update the height of the present layer
                f = true; //added
                break;
            }
        }
        if(!f){
            Layer tmpL = Layer(r.width, r.height, layerX, curY);
            r.x = layerX;
            r.y = curY;
            tmpL.rectangles.push_back(r);
            layers.push_back(tmpL); //cannot add, new a layer
            curY += r.height;
//            cout << r.width << " " << r.height << " " << r.x << " " << r.y << endl;
        }
    }
    return layers;
}

vector<Rectangle> SF(vector<Rectangle> &rectangles, double binWidth, double &ans) {
    vector<Rectangle> upperR;
    vector<Rectangle> lowerR;
    vector<Rectangle> ansR;
    double m = binWidth ;
    for(auto &r:rectangles) {
        m = min(m, 1.0 * binWidth / r.width);
    }
    for(auto &r:rectangles) {
        if(r.width > binWidth / (m + 1)) {
            upperR.push_back(r);
        } else {
            lowerR.push_back(r);
        }
    }
//no need to sort
    vector<Layer> layers = FFDH_(upperR, binWidth, 0, 0);//FFDH the larger rectangles
    double wideHeight = 0; //calculate the height cannot insert
    double narrowHeight = 0;
//    vector<Layer> rearrangedLayers;
    for(auto &l:layers) {
        if(l.width > binWidth * (m + 1) / (m + 2)) {
            l.y = wideHeight;
            wideHeight += l.height;
            for(auto &r:l.rectangles){
                r.y = l.y;
//                cout << r.width << " " << r.height << " " << r.x << " " << r.y << endl;
            }
        }
        else {
            narrowHeight += l.height; // 用narrowHeight来计算左边的空白
        }
    }
    double tmpWH = wideHeight;
    //update the left layers
    for(auto &l:layers) {
        if(l.width <= binWidth * (m + 1) / (m + 2)) {
            l.y = tmpWH;
            tmpWH += l.height;
            for(auto &r:l.rectangles){
                r.y = l.y;
            }
        }
    }
    vector<Rectangle> partR;
    auto it = lowerR.begin();
    while (it != lowerR.end()) {
//        cout << it->width << " " << it->height << " " << it->x << " " << it->y << endl;
        if (it->width <= binWidth / (m + 2) && it->height <= narrowHeight) {
                partR.push_back(*it);
                it = lowerR.erase(it);
        } else {
            it++;
        }
    }

    vector<Layer> LayerR = FFDH_(partR, binWidth, binWidth * (m + 1) / (m + 2), wideHeight);
    double heightR = 0;
    for (auto &l:LayerR) {
        heightR += l.height;
        if(heightR > narrowHeight) {
            for(auto &r:l.rectangles) {
                lowerR.push_back(r);
            }
        }
    }
    vector<Layer> LowerLayer = FFDH_(lowerR, binWidth, 0, wideHeight + narrowHeight);
    double h = 0;

    for(auto &l:LowerLayer) {
        h += l.height;
        for(auto &r:l.rectangles) {
            ansR.push_back(r);
        }
    }
    for(auto &l:LayerR) {
        for(auto &r:l.rectangles) {
            ansR.push_back(r);
        }
    }
    for(auto &l:layers) {
        h += l.height;
        for(auto &r:l.rectangles) {
            ansR.push_back(r);
        }
    }
    ans = h;
    return ansR;
}

vector<Rectangle> NFDH(vector<Rectangle> &rectangles, const double &binWidth, double &ans) {
    double h = 0;
    vector<Rectangle> ansR;
    sort(rectangles.begin(), rectangles.end(), cmp);
    Layer l(0, rectangles[0].height, 0, 0);
    for(auto &r:rectangles) {
        if(l.width + r.width <= binWidth) {
            r.x = l.width;
            r.y = h - l.height;
            ansR.push_back(r);
            l.width += r.width; //can fit in, add the rectangle to this layer
        }
        else{//cannot add, new layer
            r.x = 0;
            r.y = h;
            ansR.push_back(r);
            h += l.height;
            l.width = r.width;
            l.height = r.height;
        }
    }
    h += l.height;
    ans = h;
    return ansR;
}

vector<Rectangle> FFDH(vector<Rectangle> &rectangles, const double &binWidth, double &ans) {
    vector<Layer> layers=FFDH_(rectangles,binWidth, 0, 0);
    double h = 0;
    vector<Rectangle> ansR;
    for(auto &l:layers) {
        h += l.height;
        for(auto &r:l.rectangles) {
            ansR.push_back(r);
        }
    }
    ans = h;
    return ansR;
}