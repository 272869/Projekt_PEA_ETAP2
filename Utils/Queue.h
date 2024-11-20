//
// Created by pitko on 18.11.2024.
//

#ifndef PROJEKT_ETAP2_PRIORITYQUEUE_H
#define PROJEKT_ETAP2_PRIORITYQUEUE_H

#include <iostream>
#include "Node.h"
using namespace std;

struct Queue {
    Node** nodes;  // Dynamiczna tablica wskaźników na węzły
    int front, rear, size;

    // Inicjalizacja kolejki
    void init(int maxSize) {
        nodes = new Node*[maxSize];  // Dynamiczna alokacja dla tablicy wskaźników
        front = 0;
        rear = 0;
        size = maxSize;
    }
    // Sprawdzenie, czy kolejka jest pusta
    bool isEmpty() {
        return front == rear;
    }
    // Dodanie elementu do kolejki
    void enqueue(Node* node) {
        if (rear >= size) {
            // Jeśli kolejka jest pełna, możesz rozważyć zwiększenie jej rozmiaru
            // Przykładowe powiększenie o 2 razy
            resize(size * 2);
        }
        nodes[rear++] = node;
    }
    // Pobranie elementu z kolejki
    Node* dequeue() {
        return nodes[front++];
    }
    // Zwiększenie rozmiaru kolejki
    void resize(int newSize) {
        Node** newNodes = new Node*[newSize];
        int i = 0;
        // Kopiujemy elementy do nowej tablicy
        for (int j = front; j < rear; j++) {
            newNodes[i++] = nodes[j];
        }
        delete[] nodes;  // Zwalniamy starą tablicę
        nodes = newNodes; // Przypisujemy nową tablicę
        front = 0;
        rear = i;
        size = newSize;
    }
    // Destruktor
    ~Queue() {
        for (int i = front; i < rear; i++) {
            if (nodes[i] != nullptr) {
                delete nodes[i];  // Zwalniamy każdy węzeł tylko, jeśli nie jest nullptr
            }
        }
        delete[] nodes;  // Zwalniamy tablicę wskaźników
    }
};
#endif //PROJEKT_ETAP2_PRIORITYQUEUE_H
