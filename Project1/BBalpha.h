#pragma once


#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
inline int max( const int & a, const int & b){//get the maximum between a and b
    if(a >= b) return a;
    else return b;
}

class BBalphaTree{
private:

    class BBaNode{//node of the tree
    private:
        int element;
        BBaNode * left;
        BBaNode * right;

        bool del;//if the node is deleted, del is true, else del is false

        int size;

    public:

        BBaNode(): left{ nullptr }, right{ nullptr }, size{ 0 }, del{ 0 } {}//default constructor for a node
        BBaNode( const int & rhs ): element{ rhs }, left{ nullptr }, right {nullptr}, size{ 1 }, del{ 0 }{}
        BBaNode( int && rhs ): element{ move( rhs ) }, left{ nullptr }, right {nullptr}, size{ 1 }, del{ 0 } {}

        friend class BBalphaTree;//BBalphaTree can access the private members of BBaNode
    };

    BBaNode * root;//root of the tree

    double alpha;//the alpha value of the tree, default is 0.75

    int rebulidTimes;//the times of rebuild, for test

    void getTree( BBaNode * & t, vector<BBaNode*> & v );
    int getSize( BBaNode * & t );
    bool contain( const int & rhs, BBaNode * & t );
    void rebuild( BBaNode * & t, const vector<BBaNode*> & v, const int & a, const int & b );
    void rebuild( BBaNode * & t );
    void balance( BBaNode * & t, BBaNode ** & s );
    void insert( const int & rhs, BBaNode * & t, BBaNode ** & s );
    void remove( const int & rhs, BBaNode * & t, BBaNode ** & s );
    void clear( BBaNode * t );
    void printTree( BBaNode * t );
    void getAvgDepth( BBaNode * t, int & sum, double & totaldepth, int & depth );

public:

    BBalphaTree(): root{ nullptr }, alpha{ 0.75 }, rebulidTimes{ 0 } {}
    BBalphaTree( const double & a ): root{ nullptr }, alpha{ a }, rebulidTimes{ 0 } {}
    BBalphaTree( double && a  ): root{ nullptr }, alpha{ move( a ) }, rebulidTimes{ 0 } {}
    ~BBalphaTree(){
        clear( root );
    }

    bool contain( const int & rhs ){
        return contain( rhs, root );
    }

    void insertion( const int & rhs ){
        if( !contain( rhs ) ){//if the tree does not contain the element, insert it
            BBaNode ** nobalance{nullptr};//store the not balanced node,initially null
            insert( rhs, root, nobalance );
            if( nobalance != nullptr ){//if the node is not balanced, rebuild the tree
                rebuild( *nobalance );//rebuild the tree that is not balanced
                rebulidTimes++;//increment the times of rebuild
            }
        }
    }

    void deletion( const int & rhs ){
        if( contain( rhs ) ){//if the tree contains the element, delete it
            BBaNode ** nobalance{nullptr};
            remove( rhs, root, nobalance );
            if( nobalance != nullptr ){//if the node is not balanced, rebuild the tree
                rebuild( *nobalance );
                rebulidTimes++;
            }
        }
    }

    void printTree(){
        printTree( root );
        cout << endl;
    }

    void lPrintTree(){
        queue<BBaNode*> q;
        BBaNode* t = root;
        q.push(t);
        while( !q.empty() ){
            t = q.front();
            if ( t->left != nullptr ) q.push(t->left);
            if( t->right != nullptr ) q.push(t->right);
            cout << t->element << " ";
            q.pop();
        }

        cout << endl;
    }

    double getAvgDepth(){
        int sum = 0;
        double totaldepth = 0;
        int depth = -1;
        getAvgDepth( root, sum, totaldepth, depth );

        if( sum != 0 ) return totaldepth/sum;//return the average depth of the nodes
        else return 0;
    }

    int JudgeBalance(){
        return rebulidTimes;//return the times of rebuild
    }

};
