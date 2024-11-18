#include <fstream>
#include <iostream>
#include "FileReader.h"
#include <iomanip>

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

// Funkcja alokujaca pamiec dla tablicy o rozmiarze NxN
void FileReader::alocate(int N) {
    if (tab != NULL)dealocate(); // zwolnienie pamieci, jesli byla juz zaalokowana
    this->size = N; // przypisanie rozmiaru tablicy
    tab = new int* [N];
    for (int i = 0; i < N; ++i) {
        tab[i] = new int[N]; // utworzenie wierszy
    }
}

// zwalnianie pamieci
void FileReader::dealocate() {
    if (tab) {   // czy tablica istnieje
        for (int i = 0; i < size; ++i) {
            //delete[] tab[i];
        }
        //delete[] tab;
    }
}

// wyswietlanie tablicy
void FileReader::showTab() {
    if (tab != NULL) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (tab[i][j] != -1)
                    std::cout << std::setw(3) << tab[i][j] << " ";
                else std::cout << "   " << " ";
            }
            std::cout << std::endl;
        }
    }
}


// Funkcja generujaca losowe dane do tablicy NxN z wartosciami od 1 do sand
// zwraca tablice NxN
int** FileReader::loadRandomData(int N, int sand) {

    int* source = new int[N * N - N]; // tablica do przechowywania mozliwych wartosci
    ordertable(source, N * N - N); // inicjalizacja source wartosciami od 1 do N*N-N
    randomshuttle(source, N * N - N, 1, sand); // przemieszanie wartosci
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

// Funkcja wypelniajaca tablice kolejnymi liczbami od 1 do number
void FileReader::ordertable(int randtab[], int number) {
    for (int i = 0; i < number; i++) {
        randtab[i] = i + 1;
    }
}

// Funkcja przemieszczajaca elementy w tablicy
// testnumber i lpoj - parametry do generowania losowych liczb
void FileReader::randomshuttle(int randtab[], int number, int testnumber, int lpoj) {
    if (number == 0)return;
    srand((lpoj * 100 + testnumber) * 845);
    srand(time(NULL) + (lpoj * 51));

    for (int i = 0; i < number; i++) {
        int randomplace1 = rand() % number;
        randomplace1 = randomplace1 * rand() % number;
        int randomplace2 = rand() % number;
        randomplace2 = randomplace2 * rand() % number;
        int swap = randtab[randomplace1];
        randtab[randomplace1] = randtab[randomplace2];
        randtab[randomplace2] = swap;
    }
}