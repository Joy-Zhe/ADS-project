#include "BBalpha.h"

void BBalphaTree::getTree(BBalphaTree::BBaNode *&t, vector<BBaNode *> &v) {//get the tree in order, and store it in vector v
    if( t != nullptr ){//if t is not nullptr, then get the left subtree, then get the right subtree recursively
        getTree( t->left, v );
        if( t->del == 0 ) v.push_back(t);//if the node is not deleted, then push it into the vector
        getTree( t->right, v );

        if( t->del == 1 ){//if the node is deleted, then delete it(release the memory)
            delete t;
            t = nullptr;
        }
    }
}

int BBalphaTree::getSize(BBalphaTree::BBaNode *&t) {
    if( t == nullptr ) return 0;
    else return t->size;
}

bool BBalphaTree::contain(const int &rhs, BBalphaTree::BBaNode *&t) {//if the tree contains the element rhs, then return true, else return false
    if( t == nullptr ) return 0;//search all,not found
    else if( rhs == t->element ) return !t->del;//found, return true if the node is not deleted, else return false
    else if( rhs > t->element ) return contain( rhs, t->right );//search the right subtree recursively
    else if( rhs < t->element ) return contain( rhs, t->left );//search the left subtree recursively

    return 0;
}

void BBalphaTree::rebuild(BBalphaTree::BBaNode *&t, const vector<BBaNode *> &v, const int &a, const int &b) {
    if( a <= b ){
        int m = (a+b)/2;
        t = v[m];//get the middle element of the vector, and make it the root of the subtree
        t->left = nullptr;
        t->right = nullptr;
        rebuild( t->left, v, a, m-1 );//rebuild the left subtree recursively
        rebuild( t->right, v, m+1, b );//rebuild the right subtree recursively
        t->size = getSize(t->left) + getSize(t->right) + 1;
    }
}

void BBalphaTree::rebuild(BBalphaTree::BBaNode *&t) {//rebuild the tree that is inbalanced
    vector<BBaNode*> v;
    getTree( t, v );//get the nodes of tree in order, and store it in vector v
    rebuild( t, v, 0, v.size()-1 );
}

void BBalphaTree::balance(BBalphaTree::BBaNode *&t, BBalphaTree::BBaNode **&s) {
    if( t != nullptr ){
        if( t->del == 0 ) t->size = getSize(t->left) + getSize(t->right) + 1;//if the node is not deleted, then add 1 to its size
        else t->size = getSize(t->left) + getSize(t->right);//if the node is deleted

        if( !( getSize(t->left) <= alpha*getSize(t) && getSize(t->right) <= alpha*getSize(t) ) ) s = &t;// if the node is not balanced, then store it in s
    }
}

void BBalphaTree::insert(const int &rhs, BBalphaTree::BBaNode *&t, BBalphaTree::BBaNode **&s) {
    if( t == nullptr ) t = new BBaNode( rhs );
    else if( rhs > t->element ) insert( rhs, t->right, s );// insert it into the right subtree
    else if( rhs < t->element ) insert( rhs, t->left, s );// insert it into the left subtree

    balance( t, s );// balance the tree
}

void BBalphaTree::remove(const int &rhs, BBalphaTree::BBaNode *&t, BBalphaTree::BBaNode **&s) {//remove the node that contain element rhs from the tree
    if( t == nullptr ) return;
    else if( rhs == t->element ){//if the node is found, then delete it
        t->del = 1;
        t->size--;
    }
    else if( rhs > t->element ) remove( rhs, t->right, s );//search the right subtree recursively
    else if( rhs < t->element ) remove( rhs, t->left, s );//search the left subtree recursively

    balance( t, s );//get the node that is not balanced and store in s

}

void BBalphaTree::clear(BBalphaTree::BBaNode *t) {
    if( t != nullptr ){
        clear( t->left );
        clear( t->right );
        delete t;
    }
    t = nullptr;
}

void BBalphaTree::printTree(BBalphaTree::BBaNode *t) {
    if( t != nullptr )
    {
        printTree( t->left );
        if( t->del == 0 )
            cout << t->element << " ";
        printTree( t->right );
    }

}

void BBalphaTree::getAvgDepth(BBalphaTree::BBaNode *t, int &sum, double &totaldepth, int &depth) {//in_order traversal to get the total depth
    if( t != nullptr ){
        depth++;//next level
        totaldepth += depth;
        sum++;
        getAvgDepth( t->left, sum, totaldepth, depth );
        getAvgDepth( t->right, sum, totaldepth, depth );
        depth--;
    }
}


