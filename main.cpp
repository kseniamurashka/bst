#include <iostream>
#include "BST.h"

using namespace std;

int main() {
    BinarySearchTree test;

    test.insert(1, 1.2345);
    test.insert(0, 1.9876);
    test.insert(5, 2.930);
    test.insert(3, 2.930);
    test.insert(3, 2.6430);
    test.insert(5, 100.6430);
    BinarySearchTree::Node* root = test.return_root();
    cout << test.findHeight(root) << endl;
    test.print(root);

    return 0;
}
