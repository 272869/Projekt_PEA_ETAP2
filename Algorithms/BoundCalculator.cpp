////
//// Created by pitko on 18.11.2024.
////
//#include <climits>
//#include <algorithm>
//#include "BoundCalculator.h"
//using namespace std;
//
//
//
//int BoundCalculator::calculateBound(Node *node, int **dist, int N) {
//    int bound = node->cost;
//    bool* visited = new bool[N];  // Alokujemy dynamicznie tablicę odwiedzin
//    for (int i = 0; i < N; i++) visited[i] = false;
//
//    // Oznacz miasta już odwiedzone
//    for (int i = 0; i <= node->level; i++) {
//        visited[node->path[i]] = true;
//    }
//
//    // Dodaj minimalny koszt krawędzi wychodzących z nieodwiedzonych miast
//    for (int i = 0; i < N; i++) {
//        if (!visited[i]) {
//            int min_cost = INT_MAX;
//            for (int j = 0; j < N; j++) {
//                if (i != j && !visited[j]) {
//                    min_cost = std::min(min_cost, dist[i][j]);
//                }
//            }
//            if(min_cost == INT_MAX){
//                min_cost = 0;
//            }
//            bound += min_cost;
//        }
//    }
//
//    delete[] visited;  // Zwalniamy pamięć tablicy odwiedzin
//    return bound;
//}
