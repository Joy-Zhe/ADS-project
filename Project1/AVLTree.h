#pragma once
#include <stdio.h>
#include <iostream>

class AVLTree {
public:
    void insertion(const int & val);
    void deletion(const int & val) {
        deletion(root, val);
    }
    void LevelOrderPrint(){
        LevelOrderPrint(root);
    }
    int JudgeBalance(){
        return cntImbalanced;
    }
    double getAvgDepth() {
        cnt = 0;
        cntDepth = 0;
        getTotalDepth(root, 0);
        return cntDepth * 1.0 / cnt;
    }
    ~AVLTree( ) {//clear the Tree after used
        clear();
    }
    void clear() {
        clear(root);
    }
private:
    struct AVLNode{
        int value;
        int h;
        AVLNode * son_l;
        AVLNode * son_r;
        AVLNode(const int & val, int h = 0, AVLNode *L = nullptr, AVLNode *R = nullptr) //initialization
            : value{val}, h{h}, son_l{L}, son_r{R} {}

    };
    int cnt = 0;
    int cntDepth = 0;
    AVLNode * root = nullptr;
    int cntImbalanced = 0;
    int getHL(AVLNode * & T);
    int getHR(AVLNode * & T);
    int getMax(const int & a, const int & b);
    void updateH(AVLNode * & T);
    void LRotate(AVLNode * & T);
    void RRotate(AVLNode * & T);
    void Leftcase(AVLNode * & T);
    void Rightcase(AVLNode * & T);
    void insertion(AVLNode * & T, const int & val);
    void deletion(AVLNode * & T, const int & val);
    void LevelOrderPrint(AVLNode * & T);
    void getTotalDepth(AVLNode *& T, int depthNow);
    void clear(AVLNode *& T){
        if(T != nullptr) {
            clear(T->son_l);
            clear(T->son_r);
            delete T;
        }
        T = nullptr;
    }
};


