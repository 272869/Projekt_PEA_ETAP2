//
// Created by pitko on 18.11.2024.
//

#ifndef PROJEKT_ETAP2_RESULT_H
#define PROJEKT_ETAP2_RESULT_H

#include <climits>

struct Result {
    int cost;  // Najlepszy koszt
    int* path; // Najlepsza ścieżka
    Result() : cost(INT_MAX), path(nullptr) {} // Inicjalizacja
};


#endif //PROJEKT_ETAP2_RESULT_H
