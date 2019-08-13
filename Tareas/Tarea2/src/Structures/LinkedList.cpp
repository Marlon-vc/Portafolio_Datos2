#include "Node.cpp"
#include <iostream>
using namespace std;

class LinkedList {
    public:
        LinkedList();
        void insertStart(int value);
        void deleteStart();
        void modify(int value, int index);
        int get(int index);
        int getSize();
        void print();
    private:
        Node *head, *tail;
        int size;
        Node *getNode(int index);
};

LinkedList::LinkedList() {
    size = 0;
    head = NULL;
    tail = NULL;
}

void LinkedList::insertStart(int value) {
    Node *newNode = new Node(value);
    if (size > 0) {
        newNode->setNext(head);
    }
    head = newNode;
    size++;
}

void LinkedList::deleteStart() {
    if (size > 0) {
        Node *temp = head;
        head = head->getNext();
        delete temp;
        size--;
    }
}

Node *LinkedList::getNode(int index) {
    if (index >= 0 && index < size) {
        Node *temp = head;
        int c = 0;
        while (c != index) {
            temp = temp->getNext();
            c++;
        }
        return temp;
    }
    return NULL;
}

void LinkedList::modify(int value, int index) {
    if (index >= 0 && index < size) {
        Node *temp = getNode(index);
        temp->setValue(value);
    }
}

int LinkedList::get(int index) {
    if (index < 0 || index >= size) {
        return -1;
    } else {
        // Node *temp = head;
        // int c = 0;
        // while (c != index) {
        //     temp = temp->getNext();
        //     c++;
        // }
        Node *temp = getNode(index);
        return temp->getValue();
    }
}

int LinkedList::getSize() {
    return size;
}

void LinkedList::print() {
    Node *temp = head;
    cout << "[";
    int c = 0;
    while (c != size) {
        cout << temp->getValue();
        temp = temp->getNext();
        c++;
        if (c != size) {
            cout << ", ";
        }
    }
    cout << "]\n";
}
