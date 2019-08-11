#include <iostream>

class Node {
    public:
        Node(int value);
        void setValue(int value);
        int getValue();
        void setNext(Node *next);
        Node *getNext();
    private:
        int value;
        Node *next = NULL;
};

Node::Node(int value) {
    this->value = value;
}

void Node::setValue(int value) {
    this->value = value;
}

int Node::getValue() {
    return value;
}

void Node::setNext(Node *next) {
    this->next = next;
}

Node *Node::getNext() {
    return next;
}