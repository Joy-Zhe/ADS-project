#pragma once
#include <iostream>
#include <stdio.h>

class SPlayTree{
public:
    void insertion(const int & val){
        root = insertion(root, val);
    }
    void deletion(const int & val){
        root = deletion(root, val);
    }
    void LevelOrderPrint() {
        LevelOrderPrint(root);
    }
    double getAvgDepth() {
        cnt = 0;
        cntDepth = 0;
        getTotalDepth(root, 0);
        return cntDepth * 1.0 / cnt;
    }
    ~SPlayTree() {//clear the Tree after used
        clear();
    }
    void clear() {
        clear(root);
    }
private:
    struct SplayNode{
        int value;
        SplayNode * father;
        SplayNode * son_l;
        SplayNode * son_r;
        SplayNode(const int & value, SplayNode * father = nullptr, SplayNode * L = nullptr, SplayNode * R = nullptr)//init node
                : value{value}, father{father}, son_l{L}, son_r{R} { }
    };
    SplayNode * root = nullptr;
    long long int cnt = 0;
    long long int cntDepth = 0;
    SplayNode * findKey(SplayNode * T, const int & val);
    SplayNode * LRotate(SplayNode * T);
    SplayNode * RRotate(SplayNode * T);
    SplayNode * Splay(SplayNode * T);
    SplayNode * insertion(SplayNode * T, const int & val);
    SplayNode * deletion(SplayNode * T, const int & val);
    void LevelOrderPrint(SplayNode *& T);
    void getTotalDepth(SplayNode *& T, int depthNow);
    void clear(SplayNode *& T){
        if(T != nullptr) {
            clear(T->son_l);
            clear(T->son_r);
            delete T;
        }
        T = nullptr;
    }
};

