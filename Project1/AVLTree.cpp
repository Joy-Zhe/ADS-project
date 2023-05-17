#include "AVLTree.h"
void AVLTree::insertion(const int &val) {
    insertion(root, val);
}

int AVLTree::getHL(AVLTree::AVLNode *&T) { //get the height of the left subtree
    return (T == nullptr) ? -1 : ((T->son_l != nullptr) ? T->son_l->h : 0);
}

int AVLTree::getHR(AVLTree::AVLNode *&T) { //get the height of the right subtree
    return (T == nullptr) ? -1 : ((T->son_r != nullptr) ? T->son_r->h : 0);
}

int AVLTree::getMax(const int & a, const int & b) { // get the maximum between a and b
    if(a > b)
        return a;
    return b;
}

void AVLTree::updateH(AVLTree::AVLNode *&T) { // update height of subTree T
    T->h = getMax(getHL(T), getHR(T));
    T->h++;
    return;
}

void AVLTree::LRotate(AVLTree::AVLNode *&T) {//left rotation
    AVLNode * tmp = T->son_r;
    T->son_r = tmp->son_l;
    tmp->son_l = T;
    T = tmp;
    updateH(T->son_l);//update the height of the rotated root
    updateH(T);//update the height of the new root
}

void AVLTree::RRotate(AVLTree::AVLNode *&T) {//right rotation
    AVLNode * tmp = T->son_l;
    T->son_l = tmp->son_r;
    tmp->son_r = T;
    T = tmp;
    updateH(T->son_r);//update the height of the rotated root
    updateH(T);//update the height of the new root
}

void AVLTree::Rightcase(AVLTree::AVLNode *&T) { // RR and RL conditions
    if(getHL(T) - getHR(T) <= -2) {
        if (getHL(T->son_r) > getHR(T->son_r))//RL, 2rotations
            RRotate(T->son_r);
        LRotate(T);
        cntImbalanced++;
    }
}

void AVLTree::Leftcase(AVLTree::AVLNode *&T) { // LL and LR conditions
    if(getHL(T) - getHR(T) >= 2){//L
        if(getHL(T->son_l) < getHR(T->son_l)){//LR, 2rotations
            LRotate(T->son_l);
        }
        RRotate(T);
        cntImbalanced++;
    }
}

void AVLTree::insertion(AVLTree::AVLNode *&T, const int &val) {
    if(T == nullptr) {
        T = new AVLNode(val, 1, nullptr, nullptr);
    }else if(T->value > val){ //smaller than the present root, insert in the left
        insertion(T->son_l, val);
    }else if(T->value < val){ //larger than the present root, insert in the right
        insertion(T->son_r, val);
    }
    updateH(T); //update height of the tree after insertion
    Leftcase(T); //check balance
    Rightcase(T); //check balance
//    LevelOrderPrint();
    return;
}

void AVLTree::LevelOrderPrint(AVLTree::AVLNode *&T) {//level order print
    AVLNode *tmp[10000];
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

void AVLTree::deletion(AVLTree::AVLNode *&T, const int &val) {
    if(!T){ //null tree, nothing to delete
        return;
    }
    if(T->value > val){ //not find, in the left subtree
        if(T->son_l != nullptr){
            deletion(T->son_l, val); //delete
            updateH(T); //update the height of the root of the subtree
            Leftcase(T); //check balance
            Rightcase(T); //check balance
        }
        else{//reach nullptr, not find
//            std::cout << "Not Found!" << std::endl;
            return;
        }
    }else if(T->value < val){ //not find, in the right subtree
        if(T->son_r != nullptr){
            deletion(T->son_r, val);
            updateH(T);
            Leftcase(T);
            Rightcase(T);
        }
        else{
//            std::cout << "Not Found!" << std::endl;
            return;
        }
    }else{//find the node which need to be deleted
        if(T->son_l == nullptr && T->son_r == nullptr) {//leaf deletion
            T = nullptr;
        }else if(T->son_l == nullptr && T->son_r != nullptr){ //only right child
            T = T->son_r;
        }else if(T->son_r == nullptr && T->son_l != nullptr){ //only left child
            T = T->son_l;
        }else{ //2 children
            AVLNode *tmp = T->son_l;
            while(tmp->son_r) //find the maximum in the left subtree
                tmp = tmp->son_r;
            T->value = tmp->value; //change it as the new root of the subtree
            deletion(T->son_l, tmp->value);
            updateH(T);
            Leftcase(T);
            Rightcase(T);
        }
    }
}

void AVLTree::getTotalDepth(AVLTree::AVLNode *&T, int depthNow) {
    if(T == nullptr) // no more elements, return nullptr
        return;
    cntDepth += depthNow; //sum up
    cnt++;//calculate the nodes
    getTotalDepth(T->son_l, depthNow + 1); //deeper by 1
    getTotalDepth(T->son_r, depthNow + 1); //deeper by 1
}




