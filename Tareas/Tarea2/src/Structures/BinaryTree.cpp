#include "TreeNode.cpp"
#include <iostream>

class BinaryTree {
    public:
        BinaryTree();
        void insert(int value);
        void remove(int value);
        void print();
    private:
        TreeNode *root;
        int size;
        int smallest(TreeNode *current);
        TreeNode *insert(TreeNode *current, int element);
        TreeNode *remove(TreeNode *current, int element);
        void traverse(TreeNode *current);
};

BinaryTree::BinaryTree() {
    size = 0;
    root = nullptr;
}

void BinaryTree::insert(int value) {
    root = insert(root, value);
}

TreeNode *BinaryTree::insert(TreeNode *current, int element) {
    if (current == nullptr) {
        return new TreeNode(element);
    } else if (current->getValue() < element) {
        current->setRight(insert(current->getRight(), element));
    } else if (current->getValue() > element) {
        current->setLeft(insert(current->getLeft(), element));
    }
    return current;
}

void BinaryTree::remove(int value) {
    root = remove(root, value);
}

TreeNode *BinaryTree::remove(TreeNode *current, int element) {
    if (current == nullptr) {
        return nullptr;
    } else if (current->getValue() < element) {
        current->setRight(remove(current->getRight(), element));
    } else if (current->getValue() > element) {
        current->setLeft(remove(current->getLeft(), element));
    }
    if (current->getLeft() == nullptr && current->getRight() == nullptr) {
        return nullptr;
    } else if (current->getLeft() == nullptr) {
        return current->getRight();
    } else if (current->getRight() == nullptr) {
        return current->getLeft();
    } else {
        int small = smallest(current->getRight());
        current->setValue(small);
        current->setRight(remove(current->getRight(), small));
        return current;
    }
}

int BinaryTree::smallest(TreeNode *current) {
    return (current->getLeft() == nullptr) ? current->getValue() : smallest(current->getLeft());
}

void BinaryTree::print() {
    traverse(root);
    std::cout << "\n";
}

void BinaryTree::traverse(TreeNode *current) {
    if (current != nullptr) {
        std::cout << " " << current->getValue();
        traverse(current->getLeft());
        traverse(current->getRight());
    }
}

int main() {
    BinaryTree *tree = new BinaryTree();
    tree->insert(10);
    tree->insert(6);
    tree->insert(21);
    tree->print();
}

