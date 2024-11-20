//
// Created by pitko on 20.11.2024.
//

#ifndef PROJEKT_ETAP2_PRIORITYQUEUE_H
#define PROJEKT_ETAP2_PRIORITYQUEUE_H

#include "Node.h"
#include <climits>
#include <iostream>

// Struktura kolejki priorytetowej
struct PriorityQueue {
    Node** heap;   // Tablica dynamiczna przechowująca węzły
    int size;      // Bieżący rozmiar kolejki
    int capacity;  // Pojemność kolejki

    // Inicjalizacja kolejki priorytetowej
    PriorityQueue(int cap) {
        capacity = cap;
        size = 0;
        heap = new Node*[capacity];
    }

    // Destruktor kolejki priorytetowej
    ~PriorityQueue() {
        for (int i = 0; i < size; i++) {
            delete heap[i];
        }
        delete[] heap;
    }

    // Dodawanie elementu do kolejki priorytetowej
    void enqueue(Node* node) {
        if (size == capacity) {
            resize(); // Zwiększamy rozmiar, gdy kolejka jest pełna
        }

        heap[size] = node;
        int index = size;
        size++;

        heapifyUp(index);
    }

    // Usuwanie elementu (o najmniejszym koszcie) z kolejki
    Node* dequeue() {
        if (isEmpty()) {
            return nullptr;
        }

        Node* minNode = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);

        return minNode;
    }

    // Sprawdzanie, czy kolejka jest pusta
    bool isEmpty() const {
        return size == 0;
    }

    // Funkcja powiększająca tablicę heap, gdy jest pełna
    void resize() {
        capacity *= 2; // Podwajamy pojemność
        Node** newHeap = new Node*[capacity];

        // Kopiujemy elementy do nowej tablicy
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }

        delete[] heap; // Zwolnienie starej tablicy
        heap = newHeap; // Przypisanie nowej tablicy
    }

private:
    // Utrzymywanie porządku w kopcu przy dodawaniu elementu
    void heapifyUp(int index) {
        int parentIndex = (index - 1) / 2;
        while (index > 0 && (heap[index]->cost + heap[index]->bound) < (heap[parentIndex]->cost + heap[parentIndex]->bound)) {
            std::swap(heap[index], heap[parentIndex]);
            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }
    }

    // Utrzymywanie porządku w kopcu przy usuwaniu elementu
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && (heap[leftChild]->cost + heap[leftChild]->bound) < (heap[smallest]->cost + heap[smallest]->bound)) {
            smallest = leftChild;
        }
        if (rightChild < size && (heap[rightChild]->cost + heap[rightChild]->bound) < (heap[smallest]->cost + heap[smallest]->bound)) {
            smallest = rightChild;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }
};



#endif //PROJEKT_ETAP2_PRIORITYQUEUE_H
