#ifndef NODE_H
#define NODE_H

struct Node {

    int* path;   // Dynamiczna tablica reprezentująca ścieżkę (odwiedzone miasta)
    int cost;    // Koszt bieżącej ścieżki
    int level;   // Poziom w drzewie, ile miast zostało odwiedzonych
    int bound;   // Dolne ograniczenie kosztu

    // Konstruktor
    explicit Node(int N) : cost(0), level(0), bound(0) {
        path = new int[N];
        for (int i = 0; i < N; i++) {
            path[i] = -1;  // Inicjalizujemy wszystkie elementy, np. na -1
        }
    }

    // Konstruktor kopiujący
    Node(const Node& other, int N) : cost(other.cost), level(other.level), bound(other.bound) {
        path = new int[N];
        for (int i = 0; i < N; i++) {
            path[i] = other.path[i];  // Kopiujemy wartości ze źródła
        }
    }


    // Destruktor
    ~Node() {
//        std::cout << "Destruktor dla Node o adresie " << this << std::endl;
        delete[] path;
        path = nullptr;  // Ustawienie wskaźnika na nullptr, aby uniknąć podwójnego zwalniania
    }
};

#endif