
class TreeNode {
    public:
        TreeNode(int value);
        int getValue();
        void setValue(int value);
        TreeNode *getLeft();
        void setLeft(TreeNode *left);
        TreeNode *getRight();
        void setRight(TreeNode *right);
    private:
        int value;
        TreeNode *left, *right;
};

TreeNode::TreeNode(int value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
}

int TreeNode::getValue() {
    return value;
}

void TreeNode::setValue(int value) {
    this->value = value;
}

TreeNode *TreeNode::getLeft() {
    return left;
}

void TreeNode::setLeft(TreeNode *left) {
    this->left = left;
}

TreeNode *TreeNode::getRight() {
    return right;
}

void TreeNode::setRight(TreeNode *right) {
    this->right = right;
}
