

#include "Node.h"

class PriorityQueue {
private:
    Node** heap;
    int capacity;
    int size;

    void heapifyUp(int index) {
        while (index > 0 && heap[index]->cost < heap[(index - 1) / 2]->cost) {
            std::swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left]->cost < heap[smallest]->cost) {
            smallest = left;
        }
        if (right < size && heap[right]->cost < heap[smallest]->cost) {
            smallest = right;
        }
        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    PriorityQueue(int capacity) {
        this->capacity = capacity;
        heap = new Node*[capacity];
        size = 0;
    }

    ~PriorityQueue() {
        for (int i = 0; i < size; ++i) {
            delete heap[i];
        }
        delete[] heap;
    }


    bool empty() const {
        return size == 0;
    }

    void push(Node* node) {
        if (size == capacity) {
            expandCapacity();
        }
        heap[size] = node;
        heapifyUp(size);
        size++;
    }

    void expandCapacity() {
        capacity *= 2;
        Node** newHeap = new Node*[capacity];
        for (int i = 0; i < size; ++i) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
    }

    Node* top() const {
        if (size == 0) {
            std::cerr << "PriorityQueue is empty!" << std::endl;
            return nullptr;
        }
        return heap[0];
    }

    void pop() {
        if (size == 0) {
            std::cerr << "PriorityQueue is empty!" << std::endl;
            return;
        }
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
    }
};
