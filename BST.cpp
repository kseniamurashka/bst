#include "BST.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/////
void BinarySearchTree::print(Node* currentNode) {
    if (currentNode->left != nullptr)
        print(currentNode->left);

    std::cout << currentNode->keyValuePair.first << "(" << currentNode->keyValuePair.second << ")---";

    if (currentNode->right != nullptr)
        print(currentNode->right);
}

BinarySearchTree::Node* BinarySearchTree::return_root() {
    return _root;
}
////


BinarySearchTree::Node::Node(Key key_, Value value_, Node* parent_, Node* left_, Node* right_)
 : keyValuePair (key_, value_), parent (parent_), left (left_), right (right_) {}


BinarySearchTree::Node* BinarySearchTree::Node::deleteNode(BinarySearchTree::Node *root, Key key) {
    if (root == nullptr)
        return root;
    if (root->keyValuePair.first > key) {
        root->left = deleteNode(root->left, key);
        return root;
    }
    else if (root->keyValuePair.first < key) {
        root->right = deleteNode(root->right, key);
        return root;
    }

    if (root->left == nullptr && root->right == nullptr) {
        return nullptr;
    }
    else if (root->left == nullptr) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == nullptr) {
        Node* temp = root->left;
        delete root;
        return temp;
    }
    else {
        Node* tmp = root->right;
        while (tmp->left != nullptr) {
            tmp = tmp->left;
        }
        root->keyValuePair.first = tmp->keyValuePair.first;
        root->keyValuePair.second = tmp->keyValuePair.second;
        root->right = deleteNode(root->right, tmp->keyValuePair.first);
        return root;
    }
}
//constructors_____
BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) {
    if (other._root == nullptr) {
        return;
    }
    _size = other._size;
}

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &other) {
    if (this == &other) {
        return *this;
    }
    if (other._root != nullptr) {
        _root = new Node(*other._root);
        _size = other._size;
    }
    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept {
    _root = other._root;
    _size = other._size;
    other._root = nullptr;
}

BinarySearchTree &BinarySearchTree::operator=(BinarySearchTree &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    _root = other._root;
    _size = other._size;
    other._root = nullptr;
    return *this;
}
//_____


//____destructor___________
void BinarySearchTree::DestroyRecursive(Node* current_node) {
    if (current_node != nullptr)
    {
        DestroyRecursive(current_node->left);
        DestroyRecursive(current_node->right);
        delete current_node;
    }
}

BinarySearchTree::~BinarySearchTree() {
    DestroyRecursive(_root);
}
//______________


//________Iterator_______
BinarySearchTree::Iterator::Iterator(Node* node) {
    _node = node;
}

std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() {
    return _node->keyValuePair;
}

const std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() const {
    return _node->keyValuePair;
}

std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() {
    return &_node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() const {
    return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() {
    if (_node == nullptr) {
        return *this;
    }
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left != nullptr) {
            _node = _node->left;
        }
    }
    else {
        Node* parent_ = _node->parent;
        while (parent_ != nullptr && _node == parent_->right) {
            _node = parent_;
            parent_ = parent_->parent;
        }
        _node = parent_;
    }
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() {
    if (_node == nullptr) {
        return *this;
    }
    if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    }
    else {
        Node* parent_ = _node->parent;
        while (parent_ != nullptr && _node == parent_->left) {
            _node = parent_;
            parent_ = parent_->parent;
        }
        _node = parent_;
    }
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
}


bool BinarySearchTree::Iterator::operator==(const Iterator &other) const {
    return _node == other._node;
}
bool BinarySearchTree::Iterator::operator!=(const Iterator &other) const {
    return _node != other._node;
}

BinarySearchTree::Node* BinarySearchTree::Iterator::return_node() const {
    return _node;
}
//_______________


//_______ConstIterator_____
BinarySearchTree::ConstIterator::ConstIterator(const Node* node) {
    _node = node;
}

const std::pair<Key, Value>& BinarySearchTree::ConstIterator::operator*() const {
    return _node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::ConstIterator::operator->() const {
    return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++() {
    if (_node == nullptr) {
        return *this;
    }
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left != nullptr) {
            _node = _node->left;
        }
    }
    else {
        Node* parent_ = _node->parent;
        while (parent_ != nullptr && _node == parent_->right) {
            _node = parent_;
            parent_ = parent_->parent;
        }
        _node = parent_;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int) {
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() {
    if (_node == nullptr) {
        return *this;
    }
    if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    }
    else {
        Node* parent_ = _node->parent;
        while (parent_ != nullptr && _node == parent_->left) {
            _node = parent_;
            parent_ = parent_->parent;
        }
        _node = parent_;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int) {
    ConstIterator tmp = *this;
    --(*this);
    return tmp;
}

bool BinarySearchTree::ConstIterator::operator==(const Iterator &other) const {
    return _node == other.return_node();
}

bool BinarySearchTree::ConstIterator::operator!=(const Iterator &other) const {
    return _node != other.return_node();
}

bool BinarySearchTree::ConstIterator::operator==(const ConstIterator &other) const {
    return _node == other._node;
}

bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator &other) const {
    return _node != other._node;
}

//___________


void BinarySearchTree::insert(const Key& key, const Value& value) {
    if (_root == nullptr) {
        _root = new Node(key, value);
        _size++;
        return;
    }
    insert(key, value, _root);
}
void BinarySearchTree::insert(const Key &key, const Value &value, Node *node) {
    if (key > node->keyValuePair.first) {
        if (node->right) {
            insert(key, value, node->right);
        }
        else if (node->right == nullptr) {
            node->right = new Node(key, value, node);
        }
    }
    else if (key < node->keyValuePair.first){
        if (node->left) {
            insert(key, value, node->left);
        }
        else if (node->left == nullptr) {
            node->left = new Node(key, value, node);
        }
    }
    else if (value < node->keyValuePair.second) {
        if (node->left == nullptr) {
            node->left = new Node(key, value, node);
        }
        else {
            insert(key, value, node->left);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(key, value, node);
        }
        else {
            insert(key, value, node->right);
        }
    }
    _size++;
}

void BinarySearchTree::erase(const Key &key) {
    while (find(key)->first == key) {
        _size--;
        _root = _root->deleteNode(_root, key);
    }
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const {
    Node* temp = _root;
    while (temp != nullptr) {
        if (key < temp->keyValuePair.first) {
            temp = temp->left;
        }
        else if (key > temp->keyValuePair.first) {
            temp = temp->right;
        }
        else {
            break;
        }
    }
    if (temp == nullptr) {
        return cend();
    }
    return ConstIterator(temp);
}


BinarySearchTree::Iterator BinarySearchTree::find(const Key &key) {
    Node* temp = _root;
    while (temp != nullptr) {
        if (key < temp->keyValuePair.first) {
            temp = temp->left;
        }
        else if (key > temp->keyValuePair.first) {
            temp = temp->right;
        }
        else {
            break;
        }
    }
    if (temp == nullptr) {
        return BinarySearchTree::Iterator(temp);
    }
    return Iterator(temp);
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key) {
    Iterator start = find(key);
    Iterator temp = start;
    while (start->first == key) {
        temp++;
    }
    return make_pair(start, temp);
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const {
    ConstIterator start = find(key);
    ConstIterator temp = start;
    while (start->first == key) {
        temp++;
    }
    return make_pair(start, temp);
}


BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const {
    Node* temp = _root;
    while (temp != nullptr) {
        if (key < temp->keyValuePair.first) {
            temp = temp->left;
        } else if (key > temp->keyValuePair.first) {
            temp = temp->right;
        } else {
            break;
        }
    }
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    return BinarySearchTree::ConstIterator(temp);
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const {
    ConstIterator it = find(key);
    if (it == cend()) {
        return it;
    }
    ConstIterator t = it;
    t++;
    while (t->first == key && t != cend()) {
        it++;
        t++;
    }
    return it;
}

BinarySearchTree::ConstIterator BinarySearchTree::secondmax() const {
    Node* tmp = _root;
    while (tmp->right != nullptr) {
        tmp = tmp->right;
    }
    if (tmp->left != nullptr) {
        tmp = tmp->left;
        while (tmp->right != nullptr) {
            tmp = tmp->right;
        }
        ConstIterator it = find(tmp->keyValuePair.first);
        return it;
    }
    ConstIterator it = find(tmp->parent->keyValuePair.first);
    return it;
}

BinarySearchTree::Iterator BinarySearchTree::begin() {
    if (_root == nullptr || _root->left == nullptr){
        return Iterator(_root);
    }

    Node* temp = _root;
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    return Iterator(temp);
}

BinarySearchTree::Iterator BinarySearchTree::end() {
    if (_root == nullptr || _root->right == nullptr){
        return Iterator(_root);
    }

    Node* temp = _root;
    while (temp->right != nullptr) {
        temp = temp->right;
    }
    return Iterator(temp);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const {
    if (_root == nullptr || _root->left == nullptr){
        return ConstIterator(_root);
    }

    Node* temp = _root;
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    return ConstIterator(temp);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const {
    if (_root == nullptr || _root->right == nullptr){
        return ConstIterator(_root);
    }

    Node* temp = _root;
    while (temp->right != nullptr) {
        temp = temp->right;
    }
    return ConstIterator(temp);
}

size_t BinarySearchTree::size() const {
    return _size;
}

int BinarySearchTree::findHeight(Node* node) {
    if (node == nullptr) return 0;
    int left, right;
    if (node->left != nullptr) left = findHeight(node->left);
    else left = 0;
    if (node->right != nullptr) right = findHeight(node->right);
    else right = 0;

    int mx = left > right ? left : right;
    return mx + 1;
};

int BinarySearchTree::findDepth(Node* node) {
    if (node->parent == nullptr) return 0;
    return 1 + findDepth(node->parent);
}

bool BinarySearchTree::isAvlBalancedTree(Node* curNode) {
    if (curNode == nullptr) return true;
    if (isAvlBalancedTree(curNode->left) && isAvlBalancedTree(curNode->right) && (abs(findHeight(curNode->left) - findHeight(curNode->right)) <= 1)) return true;
    return false;
}

