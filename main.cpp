#include <iostream>
#include "Utils/FileReader.h"
#include "Algorithms/BFS.h"
#include "Algorithms/DFS.h"
#include "Algorithms/BranchAndBound.h"

using namespace std;

void menu();

int main(){
    menu();
}

void menu() {
    FileReader fileReader;
    while (0 == 0) {
        cout << "1. Wczytaj z pliku\n";
        cout << "2. Wygeneruj dane losowe\n";
        cout << "3. Wyswietl dane\n";
        cout << "4. B&B\n";
        cout << "5. BFS\n";
        cout << "6. DFS\n";
        cout << "0. Zakoncz dzialanie\n";
        int choice = 0;
        int city_number = 0;

        BranchAndBound* bnb = nullptr;
        BFS* bfs = nullptr;
        DFS* dfs = nullptr;

        cin >> choice;
        switch (choice){
            case 1:{
                string path = "";
                cout << "Podaj nazwe pliku: ";
                cin >> path;
                fileReader.loadFromFile(path);
                city_number = fileReader.size;
                cout << "Wczytano z pliku\n";
                break;
            }
            case 2:{
                cout << "Liczba miast: ";
                cin >> city_number;
                fileReader.loadRandomData(city_number, 0);
                cout << "Wygenerowano dane losowe\n";
                break;
            }
            case 3:
                cout << "Ostatnio wczytane dane:\n";
                fileReader.showTab();
                break;
            case 4:{
                if (fileReader.size == 0) {
                    cout << "Wczytaj dane do obliczen.\n";
                    break;
                }
                cout << "B&B\n";
                bnb = new BranchAndBound(fileReader.size);
                cout << bnb->bnb_run(fileReader.tab,0) << endl;
                bnb->showTheShortestPath(fileReader.tab);
                break;
            }
            case 5:{
                if (fileReader.size == 0) {
                    cout << "Wczytaj dane do obliczen.\n";
                    break;
                }
                cout << "BFS\n";
                bfs = new BFS(fileReader.size);
                cout << bfs->bnb_bfs_run(fileReader.tab) << endl;
                bfs->showTheShortestPath(fileReader.tab);
                break;
            }
            case 6:{
                if (fileReader.size == 0) {
                    cout << "Wczytaj dane do obliczen.\n";
                    break;
                }
                cout << "DFS\n";
                dfs = new DFS(fileReader.size);
                cout << dfs->bnb_dfs_run(fileReader.tab) << endl;
                dfs->showTheShortestPath(fileReader.tab);
                break;
            }
            case 0:
                fileReader.dealocate();
                return;
            default:
                break;
        }
    }
}
