#include "SPlayTree.h"

SPlayTree::SplayNode * SPlayTree::LRotate(SPlayTree::SplayNode *T) {
    if(T == nullptr)
        return nullptr;
    SplayNode * father = T->father; //get father
    SplayNode * grandpa = father->father; //get grandfather
    father->son_r = T->son_l; //update the new child of father
    if(T->son_l != nullptr) //not null, update the son's father
        T->son_l->father = father;
    T->son_l = father; //rotate T
    father->father = T; //update the father's father
    T->father = grandpa; //update rotated T's father
    if(grandpa != nullptr) {//if father is root
        if(grandpa->son_l == father)
            grandpa->son_l = T;
        else
            grandpa->son_r = T;
    }
    return T;
}

SPlayTree::SplayNode * SPlayTree::RRotate(SPlayTree::SplayNode *T) {
    if(T == nullptr)
        return nullptr;
    SplayNode * father = T->father;
    SplayNode * grandpa = father->father;
    father->son_l = T->son_r; //update the new child of father
    if(T->son_r != nullptr) //not null, update the son's father
        T->son_r->father = father;
    T->son_r = father; //rotate T
    father->father = T; //update the father's father
    T->father = grandpa; //update rotated T's father
    if(grandpa != nullptr) {//if father is root
        if(grandpa->son_l == father)
            grandpa->son_l = T;
        else
            grandpa->son_r = T;
    }
    return T;
}

SPlayTree::SplayNode * SPlayTree::Splay(SPlayTree::SplayNode * T) {
    if(T == nullptr)
        return nullptr;
    if(T->father->value < T->value){
        if(T->father->father == nullptr) { //the child of the root
            T = LRotate(T);
        }
        else {
            if (T->father->value > T->father->father->value) { //zag-zag
                T = LRotate(T->father);
                T = LRotate(T->son_r);
            }
            else { //zag-zig
                T = LRotate(T);
                T = RRotate(T);
            }
        }
    }//R
    else{
        if(T->father->father == nullptr){ // the child of the root
            T = RRotate(T);
        }
        else {
            if (T->father->value < T->father->father->value) { //zig-zig
                T = RRotate(T->father);
                T = RRotate(T->son_l);
            } else { //zig-zag
                T = RRotate(T);
                T = LRotate(T);
            }
        }
    }
    return T;
}

SPlayTree::SplayNode * SPlayTree::insertion(SPlayTree::SplayNode *T, const int &val) {
    T = findKey(root, val); // find the insertion position
    if(T == nullptr) // root
        T = new SplayNode(val, nullptr, nullptr, nullptr);
    else {
        if (T->value > val) {
            T->son_l = new SplayNode(val, nullptr, nullptr, nullptr);
            T->son_l->father = T; //update father
            //splay to the root
            T = Splay(T->son_l);
            while (T->father != nullptr)
                T = Splay(T);
        } else if (T->value < val) {
            T->son_r = new SplayNode(val, nullptr, nullptr, nullptr);
            T->son_r->father = T; //update father
            //splay to the root
            T = Splay(T->son_r);
            while (T->father != nullptr)
                T = Splay(T);
        } else {//already exists, splay to the root
            while (T->father != nullptr)
                T = Splay(T);
            return T;
        }
    }
//    LevelOrderPrint();
    return T;
}


SPlayTree::SplayNode * SPlayTree::deletion(SPlayTree::SplayNode *T, const int &val) {
    T = findKey(root, val); // find the key to delete
    if (T == nullptr)
        return root;
    if (T->value != val) { // not found
//        std::cout << "Not Found!" << std::endl;
        return root;
    }
//    LevelOrderPrint();
    while (T->father != nullptr) // splay the key to the root
        T = Splay(T);
    SplayNode * tmp;
    //delete the root and merge the 2 children of the root
    if(T->son_l != nullptr)
        tmp = T->son_l;
    else {
        tmp = T->son_r;
        T = tmp;
        return T;
    }
    if(T->son_r != nullptr)
        T->son_r->father = tmp;
    tmp->son_r = T->son_r;
    tmp->father = nullptr;
    T = tmp;
    return T;
}

void SPlayTree::LevelOrderPrint(SPlayTree::SplayNode *&T) {
    SplayNode *tmp[10000];
    int in = 0;
    int out = 0;
    tmp[in++] = T;  //save the root
    while (in > out) {
        if (tmp[out]) {
            std::cout << tmp[out]->value << " ";//dequeue
            tmp[in++] = tmp[out]->son_l; //enqueue the left son
            tmp[in++] = tmp[out]->son_r; //enqueue the right son
        }
        out++;
    }
    std::cout << std::endl;
}

SPlayTree::SplayNode *SPlayTree::findKey(SPlayTree::SplayNode *T, const int &val) {
    while(T != nullptr) {// not found, go on
        if(T->value > val) {
            if(T->son_l != nullptr)
                T = T->son_l;
            else // not found
                return T;
        }
        else if(T->value < val) {
            if(T->son_r != nullptr)
                T = T->son_r;
            else //not found
                return T;
        }
        else // found
            return T;
    }
    return nullptr;
}

void SPlayTree::getTotalDepth(SPlayTree::SplayNode *&T, int depthNow) {
    if(T == nullptr) // no more elements, return nullptr
        return;
    cntDepth += depthNow; //sum up
    cnt++;//calculate the nodes
    getTotalDepth(T->son_l, depthNow + 1); //deeper by 1
    getTotalDepth(T->son_r, depthNow + 1); //deeper by 1
}
