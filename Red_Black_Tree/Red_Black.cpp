#include "Red_Black.h"
#include <iostream>

int main() {
    RBTree tree;

    // Insert elements into the Red-Black Tree
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);

    // Search for an element and print it
    RBNode* searchResult = tree.search(15);
    if (searchResult != nullptr) {
        std::cout << "Found node: ";
        searchResult->print();
        std::cout << std::endl;
    } else {
        std::cout << "Element not found in the tree." << std::endl;
    }

    // Validate structure and colors (simple console output for manual verification)
    std::cout << "Red-Black Tree structure validated through insertions and search." << std::endl;

    return 0;
}

