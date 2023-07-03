#include "SkipList.h"
#include <chrono>
#include <vector>

int main() {
    /*srand(time(nullptr));

    SkipList skipList;

    // insert
    skipList.insert(5);
    skipList.insert(10);
    skipList.insert(3);
    skipList.insert(8);
    skipList.insert(1);
    skipList.insert(7);
    skipList.insert(4);
    skipList.insert(9);
    skipList.insert(2);
    skipList.insert(6);

    // print
    std::cout << "Skip List after insertion:" << std::endl;
    skipList.print();
    std::cout << std::endl;

    // search
    int searchValue = 4;
    std::cout << "Searching for " << searchValue << ": " << (skipList.search(searchValue) ? "Found" : "Not found") << std::endl;
    searchValue = 11;
    std::cout << "Searching for " << searchValue << ": " << (skipList.search(searchValue) ? "Found" : "Not found") << std::endl;
    std::cout << std::endl;

    // delete
    int removeValue = 3;
    std::cout << "Removing " << removeValue << " from the skip list." << std::endl;
    skipList.remove(removeValue);
    std::cout << "Skip List after removal:" << std::endl;
    skipList.print();
    std::cout << std::endl;

    // test
    skipList.insert(11);
    skipList.insert(15);
    skipList.insert(13);
    skipList.insert(12);
    skipList.insert(14);
    std::cout << "Skip List after additional insertions:" << std::endl;
    skipList.print();
    std::cout << std::endl;

    removeValue = 7;
    std::cout << "Removing " << removeValue << " from the skip list." << std::endl;
    skipList.remove(removeValue);
    std::cout << "Skip List after removal:" << std::endl;
    skipList.print();
    std::cout << std::endl;*/

    srand(time(nullptr));

    SkipList skipList;

    // test size
    const int smallSize = 1000;
    const int mediumSize = 10000;
    const int largeSize = 100000;

    // test insertion
    std::cout << "Testing insert operation:" << std::endl;

    std::vector<int> insertData;
    for (int i = 0; i < largeSize; i++) {
        insertData.push_back(rand() % largeSize);
    }

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < insertData.size(); i++) {
        skipList.insert(insertData[i]);
    }
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Insertion time for " << insertData.size() << " elements: " << duration.count() << " milliseconds" << std::endl;

    // test deletion
    std::cout << "Testing remove operation:" << std::endl;

    std::vector<int> removeData;
    for (int i = 0; i < largeSize; i++) {
        removeData.push_back(rand() % largeSize);
    }

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < removeData.size(); i++) {
        skipList.remove(removeData[i]);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Removal time for " << removeData.size() << " elements: " << duration.count() << " milliseconds" << std::endl;

    // test search
    std::cout << "Testing search operation:" << std::endl;

    std::vector<int> searchData;
    for (int i = 0; i < largeSize; i++) {
        searchData.push_back(rand() % largeSize);
    }

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < searchData.size(); i++) {
        skipList.search(searchData[i]);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Search time for " << searchData.size() << " elements: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
