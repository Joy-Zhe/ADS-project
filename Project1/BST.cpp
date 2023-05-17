#include "BST.h"
BST::BST()
{
    this->left = nullptr;
    this->right = nullptr;
}
BST::BST(int key)
{
    this->left = nullptr;
    this->right = nullptr;
    this->key = key;
}
NODE BST::get_left()
{
    return this->left;
}
NODE BST::get_right()
{
    return this->right;
}
int BST::get_key()
{
    return key;
}
class Queue;
typedef Queue *Queue_node;
class Queue
{
private:
    NODE node;
    Queue_node next;
    int height;

public:
    Queue(NODE node, int height);
    int get_height();
    Queue_node get_next();
    int inqueue(Queue_node &tail); // print head, enqueue tail
};
double BST::getAvgDepth()
{
    if (root == nullptr)
        return 0;
    double sum = 0;
    int cnt = 0;
    Queue_node head = new Queue(root, 0);
    Queue_node tail = head;
    int curr_height = 0;
    while (head != nullptr)
    {
        if (head->get_height() == curr_height)
        {
            head->inqueue(tail);
            sum += head->get_height();
        }
        else
        {
            head->inqueue(tail);
            sum += head->get_height();
            curr_height++;
        }
        cnt++;
        head = head->get_next();
    }
    return sum / cnt;
}
NODE BST::find(int val, NODE &pre_p)
{ // if found, return node, else return nullptr, pre_p is the position to insert
    NODE p = this;
    while (p != nullptr)
    {
        if (val > p->get_key())
        {
            pre_p = p;
            p = p->get_right();
        }
        else if (val < p->get_key())
        {
            pre_p = p;
            p = p->get_left();
        }
        else
        { // find
            return p;
        }
    }
    return nullptr; // not find
}
void BST::insertion(int val)
{
    if (root == nullptr)
    {
        root = this;
        root->key = val;
        return;
    }
    NODE p = root;
    NODE pre_p = nullptr;
    if (p->find(val, pre_p))
    { // if found
//        cout << "can't insert an existed key" << endl;
        return;
    }
    NODE insert_node = new BST(val);
    if (pre_p->get_key() > val)
    {
        pre_p->left = insert_node;
    }
    else
        pre_p->right = insert_node;
}

void BST::deletion(int val)
{
    NODE p = this, pre_p = nullptr;
    if ((p = p->find(val, pre_p)) == nullptr)
    {
//        cout << "the delete key doesn't exist" << endl;
        return;
    }
    if (p->get_left() && p->get_right())
    { // 2's node
        NODE leaf_parent = nullptr;
        NODE leaf = p->find_left_right(leaf_parent);
        p->key = leaf->key;
        p = leaf; // exchange
        pre_p = leaf_parent;
    }

    if (p->get_left())
    { // have left child,no right key
        if (pre_p == nullptr)
        {
            root = p->get_left();
            return;
        }
        if (pre_p->get_left() == p)
            pre_p->left = p->get_left();
        else
            pre_p->right = p->get_left();
    }
    else if (p->get_right())
    { // have right child,no left key
        if (pre_p == nullptr)
        {
            root = p->get_right();
            return;
        }
        if (pre_p->get_left() == p)
            pre_p->left = p->get_right();
        else
            pre_p->right = p->get_right();
    }
    else
    { // 0's node
        if (pre_p->get_left() == p)
            pre_p->left = nullptr;
        else
            pre_p->right = nullptr;
    }
}
NODE BST::find_left_right(NODE &leaf_parent)
{ // return the maximum of the left subtree, change its parent
    NODE p = this;
    leaf_parent = p;
    p = p->get_left();
    while (p->get_right())
    {
        leaf_parent = p;
        p = p->get_right();
    }
    return p;
}

void BST::LevelOrderPrint()
{ // print
    if (root == nullptr)
    {
        return;
    }
    Queue_node head = new Queue(root, 0);
    Queue_node tail = head;
    int curr_height = 0;
    while (head != nullptr)
    {
        if (head->get_height() == curr_height)
            cout << head->inqueue(tail) << " ";
        else
        {
            cout << endl
                 << head->inqueue(tail) << " ";
            curr_height++;
        }
        head = head->get_next();
    }
    cout << endl;
}
Queue::Queue(NODE node, int height)
{
    this->node = node;
    this->height = height;
    this->next = nullptr;
}
int Queue::get_height()
{
    return this->height;
}
Queue_node Queue::get_next()
{
    return this->next;
}
int Queue::inqueue(Queue_node &tail)
{ // print head, enqueue tail
    if (this->node->get_left() != nullptr && this->node->get_right() != nullptr)
    {
        tail->next = new Queue(node->get_left(), height + 1);
        tail->next->next = new Queue(node->get_right(), height + 1);
        tail = tail->next->next;
    }
    else if (this->node->get_right() != nullptr)
    {
        tail->next = new Queue(node->get_right(), height + 1);
        tail = tail->next;
    }
    else if (this->node->get_left() != nullptr)
    {
        tail->next = new Queue(node->get_left(), height + 1);
        tail = tail->next;
    }
    return this->node->get_key();
}
