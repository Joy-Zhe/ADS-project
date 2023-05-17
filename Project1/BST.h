#pragma once

#include <iostream>
using namespace std;
class BST;
typedef BST *NODE;
class BST
{
private:
    int key;
    NODE root = NULL;
    NODE left, right;

    NODE find(int val, NODE &pre_p);
    NODE find_left_right(NODE &leaf_parent);

public:
    BST();
    BST(int val);
    void insertion(int val);
    void deletion(int val);
    void LevelOrderPrint();
    NODE get_left();
    NODE get_right();
    int get_key();
    double getAvgDepth();
};