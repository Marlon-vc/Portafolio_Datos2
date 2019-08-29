#include "TreeNode.cpp"
#include <iostream>

class BinaryTree {
    public:
        BinaryTree();
        void insert(int value);
        void remove(int value);
        void print();
        std::string getString();
    private:
        TreeNode *root;
        int size;
        int smallest(TreeNode *current);
        TreeNode *insert(TreeNode *current, int element);
        TreeNode *remove(TreeNode *current, int element);
        void traverse(TreeNode *current);
        void traverse(TreeNode *current, std::string &buffer);
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
    if (!current) {
        return nullptr;
    } else if (current->getValue() < element) {
        current->setRight(remove(current->getRight(), element));
    } else if (current->getValue() > element) {
        current->setLeft(remove(current->getLeft(), element));
    }

    if (current->getValue() == element) {
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
    } else {
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

std::string BinaryTree::getString() {
    std::string buffer;
    traverse(root, buffer);
    return buffer;
}

void BinaryTree::traverse(TreeNode *current, std::string &buffer) {
    if (current) {
        buffer.append(" ");
        buffer.append(std::to_string(current->getValue()));
        traverse(current->getLeft(), buffer);
        traverse(current->getRight(), buffer);
    }
}

void BinaryTree::traverse(TreeNode *current) {
    if (current != nullptr) {
        std::cout << " " << current->getValue();
        traverse(current->getLeft());
        traverse(current->getRight());
    }
}
