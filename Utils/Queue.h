#ifndef PROJEKT_ETAP2_PRIORITYQUEUE_H
#define PROJEKT_ETAP2_PRIORITYQUEUE_H

#include <iostream>
#include "Node.h"

struct Queue {
    Node** nodes;
    int start;
    int end;
    int capacity;

    void initialize(int initialSize) {
        nodes = new Node*[initialSize];
        start = 0;
        end = 0;
        capacity = initialSize;
    }

    void adjustSize(int newCapacity) {
        Node** tempArray = new Node*[newCapacity];
        int index = 0;
        for (int i = start; i < end; i++) tempArray[index++] = nodes[i];
        delete[] nodes;
        nodes = tempArray;
        start = 0;
        end = index;
        capacity = newCapacity;
    }

    bool isQueueEmpty() {
        return start == end;
    }

    void add(Node* node) {
        if (end >= capacity) adjustSize(capacity * 2);
        nodes[end++] = node;
    }

    Node* remove() {
        return nodes[start++];
    }

    ~Queue() {
        for (int i = start; i < end; i++) if (nodes[i] != nullptr) delete nodes[i];
        delete[] nodes;
    }
};
#endif //PROJEKT_ETAP2_PRIORITYQUEUE_H
