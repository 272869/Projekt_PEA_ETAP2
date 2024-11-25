#ifndef PROJEKT_ETAP2_PRIORITYQUEUE_H
#define PROJEKT_ETAP2_PRIORITYQUEUE_H

#include <iostream>
#include "Node.h"

struct Queue {
    Node** nodes; // dynamiczna tablica wskaźników na obiekty typu Node
    int start; // indeks początku kolejki
    int end; // indeks końca kolejki
    int capacity; // indeks pojemności

    // inicjalizujemy kolejkę
    void initialize(int initialSize) {
        nodes = new Node*[initialSize]; // Alokujemy tablicę wskaźników
        start = 0;
        end = 0;
        capacity = initialSize;
    }

    // poszerzenie kolejki
    void adjustSize(int newCapacity) {
        Node** tempArray = new Node*[newCapacity];  // Tworzymy nową tablicę
        int index = 0;
        for (int i = start; i < end; i++) tempArray[index++] = nodes[i]; //przypisujemy elementy
        delete[] nodes; //zwalniamy starą tablicę
        nodes = tempArray; //przypisujemy nową tablicę jako główna tablica
        start = 0;
        end = index;
        capacity = newCapacity;
    }

    // sprawdzenie czy kolejka jest pusta
    bool isQueueEmpty() {
        return start == end;
    }

    // dodanie do kolejki
    void enqueue(Node* node) {
        if (end >= capacity) adjustSize(capacity * 2); // rozszerzamy rozmiar * 2
        nodes[end++] = node; // przesuwamy wskaźnik końca kolejki na nowy element
    }

    // pobranie elementu z kolejki
    Node* dequeue() {
        return nodes[start++]; // Pobieramy element z przodu kolejki i przesuwamy wskaźnik start
    }

    ~Queue() {
        for (int i = start; i < end; i++) if (nodes[i] != nullptr) delete nodes[i]; // Zwalniamy pamięć każdego elementu
        delete[] nodes;
    }
};
#endif //PROJEKT_ETAP2_PRIORITYQUEUE_H
