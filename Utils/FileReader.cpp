#include <fstream>
#include <iostream>
#include "FileReader.h"
#include <iomanip>

//funkcja wczytywania z pliku
int** FileReader::loadFromFile(std::string path) {
    std::ifstream file(path);
    if (!file.good()) {
        std::cout << "Blednie podana nazwa pliku\n";
        return NULL;
    }
    int N = 0;
    file >> N;
    int word;
    alocate(N);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> word;
            tab[i][j] = word;
        }
    }
    return tab;
}

//funkcja alokujaca pamiec dla tablicy o rozmiarze NxN
void FileReader::alocate(int N) {
    this->size = N; // przypisanie rozmiaru tablicy
    tab = new int* [N];
    for (int i = 0; i < N; ++i) tab[i] = new int[N];
}


// wyswietlanie tablicy
void FileReader::showTab() {
    if (tab != NULL) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << std::setw(3) << tab[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}



// Funkcja generujaca losowe dane do tablicy NxN z wartosciami od 1 do sand
// zwraca tablice NxN
int** FileReader::loadRandomData(int N, int maxValue) {
    int* source = new int[N * N - N]; // tablica do przechowywania mozliwych wartosci
    ordertable(source, N * N - N); // inicjalizacja source wartosciami od 1 do N*N-N
    randomshuttle(source, N * N - N, 1, maxValue); // przemieszanie wartosci
    alocate(N); // alokacja pamieci dla tablicy NxN
    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                tab[i][j] = -1; // przekatna glowna -1
                continue;
            }
            tab[i][j] = source[k]; // przypisanie losowego kosztu z source
            k++;
        }
    }
    return tab;
}

int** FileReader::loadRandomSymetricData(int N, int maxValue) {
    int* source = new int[N * (N - 1) / 2]; // tablica na wartości dla górnego trójkąta macierzy
    ordertable(source, N * (N - 1) / 2);    // inicjalizacja source wartościami od 1 do N*(N-1)/2
    randomshuttle(source, N * (N - 1) / 2, 1, maxValue); // przemieszanie wartości
    alocate(N); // alokacja pamięci dla tablicy NxN

    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) tab[i][j] = -1; // przekątna główna -1
            else if (i < j) {
                tab[i][j] = source[k]; // przypisanie wartości z górnego trójkąta
                k++;
            } else tab[i][j] = tab[j][i]; // przypisanie wartości symetrycznej
        }
    }
    return tab;
}

void FileReader::ordertable(int randtab[], int number) {
    for (int i = 0; i < number; i++) randtab[i] = i + 1;
}

void FileReader::randomshuttle(int randtab[], int number, int testnumber, int lpoj) {
    if (number == 0) return;

    // Ustawienie ziarna generatora liczb losowych na podstawie czasu
    srand(time(NULL) + lpoj);

    for (int i = 0; i < number; i++) {
        // Losowanie dwóch indeksów
        int randomplace1 = rand() % number;
        int randomplace2 = rand() % number;

        // Zamiana elementów
        int swap = randtab[randomplace1];
        randtab[randomplace1] = randtab[randomplace2];
        randtab[randomplace2] = swap;
    }
}
