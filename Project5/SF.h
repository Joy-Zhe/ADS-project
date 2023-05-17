#pragma once

#include <algorithm>
#include <vector>
using namespace std;
struct Rectangle {
    int width;
    int height;

    Rectangle(int width, int height) : width(width), height(height) {}
};

struct Bin{
    int maxWidth;
    int nowHeight;
    int remainWidth;

    Bin(int w) : maxWidth(w), nowHeight(0), remainWidth(w) {}

    void addRec(Rectangle &r) {
        remainWidth -= r.width;
        nowHeight = max(nowHeight, r.height);
    }

    bool canFit(Rectangle &r) {
        if(r.width <= remainWidth)
            return true;
        return false;
    }
};
bool cmp (Rectangle t1, Rectangle t2) {
    int tmp1 = t1.height;
    int tmp2 = t2.height;
    return tmp1 > tmp2;
}
int SFPack(vector<Rectangle>& rectangles, int WBin, int m) { // m maybe set to 2?(half)
    vector<Rectangle> upperHalf;
    vector<Rectangle> lowerHalf;
    for(auto& it:rectangles) {
        if(it.width > WBin / m)
            upperHalf.push_back(it);
        else
            lowerHalf.push_back(it);
    }
    sort(upperHalf.begin(), upperHalf.end(), cmp);
    sort(lowerHalf.begin(), lowerHalf.end(), cmp);
    vector<Bin> bin;
    //pack larger ones
    for(auto& r:upperHalf) {
        bin.push_back(Bin(WBin));
        //every big rectangle are going to have a new bin because of it width
        bin.back().addRec(r);
        for(auto tmp = lowerHalf.begin(); tmp != lowerHalf.end();) {
            if(bin.back().canFit(*tmp)) {
                bin.back().addRec(*tmp);
                tmp = lowerHalf.erase(tmp); //added, delete
            } else {
                tmp++;
            }
        }
    }
    //pack smaller ones
    for(auto& r:lowerHalf) {
        bool f = false;
        for(auto& it:bin) {
            if(it.canFit(r)) {
                it.addRec(r);
                f = true;
                break;
            }
        }
        if(!f) {
            bin.push_back(Bin(WBin)); //cannot store in any bins, new bin
            bin.back().addRec(r);
        }
    }
    int ans = 0;
    for(auto &it:bin)
        ans = max(ans, it.nowHeight);
    return ans;
}