
#ifndef PROJEKT_ETAP2_STACK_H
#define PROJEKT_ETAP2_STACK_H

#include "Node.h"

struct Stack {
    Node** nodes;  // Dynamiczna tablica wskaźników na węzły
    int top, size;

    // Inicjalizacja stosu
    void init(int maxSize) {
        nodes = new Node*[maxSize];  // Dynamiczna alokacja dla tablicy wskaźników
        top = -1;  // Stos jest pusty
        size = maxSize;
    }

    // Sprawdzenie, czy stos jest pusty
    bool isEmpty() {
        return top == -1;
    }

    // Dodanie elementu do stosu
    void push(Node* node) {
        if (top < size - 1) {
            nodes[++top] = node;
        } else {
            // Możemy powiększyć stos, jeśli jest pełny
            resize(size * 2);
            nodes[++top] = node;
        }
    }

    // Pobranie elementu ze stosu
    Node* pop() {
        return nodes[top--];
    }

    // Zmienna do powiększenia rozmiaru stosu
    void resize(int newSize) {
        Node** newNodes = new Node*[newSize];
        for (int i = 0; i <= top; i++) {
            newNodes[i] = nodes[i];
        }
        delete[] nodes;
        nodes = newNodes;
        size = newSize;
    }

    // Destruktor
    ~Stack() {
        for (int i = 0; i <= top; i++) {
            delete nodes[i];  // Zwalniamy każdy węzeł
        }
        delete[] nodes;  // Zwalniamy tablicę wskaźników
    }
};


#endif //PROJEKT_ETAP2_STACK_H
