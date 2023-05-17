#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include "BST.h"
#include "AVLTree.h"
#include "SPlayTree.h"
#include "BBalpha.h"
#include <cstdlib>
#include <ctime>

class Test
{ // include three test mode for four trees
public:
    void sequenceTest(const int &n)
    {                        // sequential test with 1-n
        int *p = new int[n]; // get the array to store the sequence
        for (int i = 0; i < n; i++)
            p[i] = i + 1;
        input.open("./Input/sequentialDataIn.txt", ios::out); // open file with the out mode
        for(int i = 0; i < n; i++)
            input << p[i] << " ";
        output.open("./Output/testInfo.txt", ios::out); // open file with the out mode
        output << "test in sequential mode with " << n << " nodes" << endl;
        bstTest(bst, n, p); // use test mode1: sequential
        AVLTest(avlTree, n, p);
        SplayTest(sPlayTree, n, p);
        bbTest(bbAlphaTree, n, p);
        output.close();
        input.close();
        delete[] p;
    }
    void randomTest(const int &n, const int &m) //store the minus one to represent deletion
    {
        int *p = new int[n]; // get the array to store the sequence
        int *d = new int[n]; // store the deletion sequence
        srand((unsigned)time(0));
        for (int i = 0; i < n; i++) // generate random number within [1:n];
        {
            p[i] = i + 1;
            d[i] = i + 1;
        }
        for (int i = n - 1; i > 0; i--)
        {
            swap(p[i], p[rand() % i]); // randomize by swap randomly
            srand(time(0));
            swap(d[i], d[rand() % i]);
//            cout << p[i] << " " << d[i] << endl;
        }
        int cnt_ins = 0;
        int cnt_del = 0;
        int flag = 0;
        for(int i = 0; i < n; i++)
        {
            flag = rand() % 100; //1 represents deletion
            if(flag > 50/* && cnt_ins > cnt_del */&& cnt_del <= n - m) { // no more deletion than insertion
                p[i] = -d[i]; //let deletion < 0 to mark it
                cnt_del++;
            }else
                cnt_ins++;
        }
        input.open("./Input/randomDataIn.txt", ios::out); // open file with the out mode
        for(int i = 0; i < n; i++)
            input << p[i] << " ";
        output.open("./Output/testInfo.txt", ios::out); // open file with the out mode
        output << "test in sequential mode with " << n << " nodes" << endl;
        bstTest(bst, n, p); // use test mode2: random number
        AVLTest(avlTree, n, p);
        SplayTest(sPlayTree, n, p);
        bbTest(bbAlphaTree, n, p);
        output.close();
        input.close();
        delete[] p;
    }
    void diyTest(const int &n)
    {
        int *p = new int[n]; // get the array to store the sequence
        for (int i = 0; i < n; i++)
        { // get number from input
            cin >> p[i];
        }
        output.open("./Output/testInfo.txt", ios::out); // open file with the out mode
        output << "test in sequential mode with " << n << " nodes" << endl;
        bstTest(bst, n, p); // use test mode2: diy number
        AVLTest(avlTree, n, p);
        SplayTest(sPlayTree, n, p);
        bbTest(bbAlphaTree, n, p);
        output.close();
        delete[] p;
    }
private:
    BST bst;
    AVLTree avlTree;
    SPlayTree sPlayTree;
    BBalphaTree bbAlphaTree;
    ofstream output, input;

    void bstTest(BST &T, int n, int *p);
    void AVLTest(AVLTree &T, int n, int *p);
    void SplayTest(SPlayTree &T, int n, int *p);
    void bbTest(BBalphaTree &T, int n, int *p);
};
