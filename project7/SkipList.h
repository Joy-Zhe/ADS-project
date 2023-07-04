#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <cstring>
#include <random>
#define MAX_LEVEL 32
#define RAND_P 0.25
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
        srand(time(nullptr)); // Initialize random seed
    }

    ~SkipList() {
        SkipNode* current = head->forward[0];
        while (current != nullptr) {
            SkipNode* next = current->forward[0];
            delete current;
            current = next;
        }
        delete head;
    }

    // randomize number of levels
    int randomLevel() {
        int r_level = 0;
        while (rand() < RAND_P * RAND_MAX && r_level < MAX_LEVEL) {
            r_level++;
        }
        return r_level;
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

            adjustBalance();
        }
    }

    // balance adjustment
    void adjustBalance() {
        while (level > 0 && head->forward[level] == nullptr) {
            level--;
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
