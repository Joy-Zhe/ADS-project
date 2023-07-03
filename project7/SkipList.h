#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <cstring>

#define MAX_LEVEL 16
// maximum level

class SkipNode {
public:
    int value;
    SkipNode** forward; // forward ptr

    SkipNode(int level, int value) {
        this->value = value;
        forward = new SkipNode*[level + 1];
        memset(forward, 0, sizeof(SkipNode*) * (level + 1));
    }

    ~SkipNode() {
        delete[] forward;
    }
};

class SkipList {
private:
    SkipNode* head;
    int level; // maximum value

public:
    SkipList() {
        head = new SkipNode(MAX_LEVEL, 0);
        level = 0;
    }

    ~SkipList() {
        delete head;
    }

    // randomize number of values
    int randomLevel() {
        int level = 0;
        while (rand() % 2 == 0 && level < MAX_LEVEL) {
            level++;
        }
        return level;
    }

    // search
    bool search(int value) {
        SkipNode* current = head;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];

        return current != nullptr && current->value == value;
    }

    // insert
    void insert(int value) {
        SkipNode* current = head;
        SkipNode* update[MAX_LEVEL + 1];
        memset(update, 0, sizeof(SkipNode*) * (MAX_LEVEL + 1));

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];

        if (current == nullptr || current->value != value) {
            int newLevel = randomLevel();
            if (newLevel > level) {
                for (int i = level + 1; i <= newLevel; i++) {
                    update[i] = head;
                }
                level = newLevel;
            }

            SkipNode* newNode = new SkipNode(newLevel, value);
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    // delete
    void remove(int value) {
        SkipNode* current = head;
        SkipNode* update[MAX_LEVEL + 1];
        memset(update, 0, sizeof(SkipNode*) * (MAX_LEVEL + 1));

        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];

        if (current != nullptr && current->value == value) {
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != current)
                    break;
                update[i]->forward[i] = current->forward[i];
            }
            delete current;

            while (level > 0 && head->forward[level] == nullptr) {
                level--;
            }
        }
    }

    // print
    void print() {
        for (int i = level; i >= 0; i--) {
            SkipNode* current = head->forward[i];
            std::cout << "Level " << i << ": ";
            while (current != nullptr) {
                std::cout << current->value << " ";
                current = current->forward[i];
            }
            std::cout << std::endl;
        }
    }
};