
#include <iostream>
#include "Node.h"


class FIFOQueue {
private:
    Node** queue;  // Array to store the nodes
    int capacity;  // Maximum capacity of the queue
    int size;      // Current size of the queue
    int front;     // Index of the front element
    int rear;      // Index of the rear element

public:
    FIFOQueue(int capacity) {
        this->capacity = capacity;
        queue = new Node*[capacity];
        size = 0;
        front = 0;
        rear = -1;
    }

    ~FIFOQueue() {
        delete[] queue;
    }

    bool empty() const {
        return size == 0;
    }

    void push(Node* node) {
        if (size == capacity) {
            std::cerr << "FIFOQueue capacity exceeded!" << std::endl;
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = node;
        size++;
    }

    Node* frontElement() const {
        if (size == 0) {
            std::cerr << "FIFOQueue is empty!" << std::endl;
            return nullptr;
        }
        return queue[front];
    }

    void pop() {
        if (size == 0) {
            std::cerr << "FIFOQueue is empty!" << std::endl;
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }
};
