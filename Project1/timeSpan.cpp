#include "timeSpan.h"

void Test::bstTest(BST &T, int n, int *p)
{
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    { // sequential mode
        if(p[i] > 0)
            T.insertion(p[i]);
        else
            T.deletion(-p[i]);
    }
    auto end = chrono::high_resolution_clock::now();
    output << "BST:"
           << endl
           << "total time cost: "
           << chrono::duration_cast<chrono::microseconds>(end - start).count()
           << " us"
           << endl
           << "Average depth of nodes: "
           << T.getAvgDepth()
           << endl;
}

void Test::AVLTest(AVLTree &T, int n, int *p)
{
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        if(p[i] > 0)
            T.insertion(p[i]);
        else
            T.deletion(-p[i]);
    }
    auto end = chrono::high_resolution_clock::now();
    output << "AVLTree:" << endl
           << "total time cost: "
           << chrono::duration_cast<chrono::microseconds>(end - start).count()
           << " us"
           << endl
           << "Average depth of nodes: "
           << T.getAvgDepth()
           << endl
           << "Imbalanced time during operations: "
           << T.JudgeBalance()
           << endl;
}

void Test::SplayTest(SPlayTree &T, int n, int *p)
{
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        if(p[i] > 0)
            T.insertion(p[i]);
        else
            T.deletion(-p[i]);
    }
    auto end = chrono::high_resolution_clock::now();
    output << "SplayTree:"
           << endl
           << "total time cost: "
           << chrono::duration_cast<chrono::microseconds>(end - start).count()
           << " us"
           << endl
           << "Average depth of nodes: "
           << T.getAvgDepth()
           << endl;
}

void Test::bbTest(BBalphaTree &T, int n, int *p)
{
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        if(p[i] > 0)
            T.insertion(p[i]);
        else
            T.deletion(-p[i]);
    }
    auto end = chrono::high_resolution_clock::now();
    output << "BBalpha Tree:" << endl
           << "total time cost: "
           << chrono::duration_cast<chrono::microseconds>(end - start).count()
           << " us"
           << endl
           << "Average depth of nodes: "
           << T.getAvgDepth()
           << endl
           << "Imbalanced times during operations: "
           << T.JudgeBalance()
           << endl;
}