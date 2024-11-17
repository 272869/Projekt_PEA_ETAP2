#include "FileReader.h"
#include <iostream>

//załadowanie pliku grafu
bool FileReader::openFile(){
    std::string nameOfFile;

    std::cout << "Podaj nazwe pliku" << std::endl;
    std::cin >> nameOfFile;
    std::cout << "\n";
    file.open(nameOfFile);
    if(!file.is_open()) {
        std::cout << "Nie ma takiego pliku\n";
        return false;
    }
    else {
        std::cout << "Otworzono plik " << nameOfFile <<"\n";
        return true;
    }
}
//pobieranie liczb z plików
int FileReader::getDataFromFile() {
    int number;
    file >> number;
    return number;
}