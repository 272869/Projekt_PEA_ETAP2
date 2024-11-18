#include <vector>
#include <iostream>
#include "BranchAndBound.h"
#include "../Utils/PriorityQueue.h"


int BranchAndBound::calculateBound(Node *node, int **dist, int N) {
    int bound = node->cost;
    bool* visited = new bool[N];  // Alokujemy dynamicznie tablicę odwiedzin
    for (int i = 0; i < N; i++) visited[i] = false;

    // Oznacz miasta już odwiedzone
    for (int i = 0; i <= node->level; i++) {
        visited[node->path[i]] = true;
    }

    // Dodaj minimalny koszt krawędzi wychodzących z nieodwiedzonych miast
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int min_cost = INT_MAX;
            for (int j = 0; j < N; j++) {
                if (i != j && !visited[j]) {
                    min_cost = std::min(min_cost, dist[i][j]);
                }
            }
            if(min_cost == INT_MAX){
                min_cost = 0;
            }
            bound += min_cost;
        }
    }

    delete[] visited;  // Zwalniamy pamięć tablicy odwiedzin
    return bound;
}

Result BranchAndBound::branchAndBound(int** dist, int N, int start) {
    PriorityQueue pq(1000);

    bestCost = INT_MAX;
    bestNode = nullptr;

    Node* root = new Node(N);
    root->path[0] = start;
    root->cost = 0;
    root->level = 0;
    root->bound = calculateBound(root, dist, N);

    pq.enqueue(root);

    while (!pq.isEmpty()) {
        Node* current = pq.dequeue();

        if (current->level == N - 1) {
            int last_to_start = dist[current->path[current->level]][start];
            int total_cost = current->cost + last_to_start;

            if (total_cost < bestCost) {
                bestCost = total_cost;
                if (bestNode != nullptr) {
                    delete bestNode;
                }
                bestNode = current;
            } else {
                delete current;
            }
            continue;
        }

        for (int i = 0; i < N; i++) {
            bool alreadyVisited = false;

            for (int j = 0; j <= current->level; j++) {
                if (current->path[j] == i) {
                    alreadyVisited = true;
                    break;
                }
            }

            if (!alreadyVisited && current->level < N - 1) {
                Node* child = new Node(N);
                for (int j = 0; j <= current->level; j++) {
                    child->path[j] = current->path[j];
                }
                child->level = current->level + 1;
                child->path[child->level] = i;

                child->cost = current->cost + dist[current->path[current->level]][i];
                child->bound = calculateBound(child, dist, N);

                if (child->bound < bestCost) {
                    pq.enqueue(child);
                } else {
                    delete child;
                }
            }
        }

        delete current;
    }

    Result result;
    result.cost = bestCost;

    if (bestNode != nullptr) {
        result.path = new int[N + 1];
        for (int i = 0; i <= bestNode->level; i++) {
            result.path[i] = bestNode->path[i];
        }
        result.path[bestNode->level + 1] = start;
        delete bestNode;
    } else {
        result.path = nullptr;
    }

    return result;
}

Result BranchAndBound::startFromEachVertex(int** dist, int N) {
    Result bestResult;
    bestResult.cost = INT_MAX;
    bestResult.path = nullptr;

    for (int start = 0; start < N; start++) {
        Result currentResult = branchAndBound(dist, N, start);

        if (currentResult.cost < bestResult.cost) {
            if (bestResult.path != nullptr) {
                delete[] bestResult.path;
            }
            bestResult = currentResult;
        } else {
            delete[] currentResult.path;
        }
    }

    return bestResult;
}


///wyświetlenie cyklu rozwiązania
void BranchAndBound::showPath(const Result& result, int pathsize) {
    if (result.path != nullptr) {
        std::cout << "Najlepsza trasa: ";

        // Używamy size do iterowania po ścieżce
        for (int i = 0; i < pathsize; i++) {
            std::cout << result.path[i] << " -> ";
        }

        std::cout << result.path[0] << std::endl; // Powrót do miasta startowego
        std::cout << "Minimalny koszt: " << result.cost << std::endl;
    } else {
        std::cout << "Brak znalezionego rozwiązania." << std::endl;
    }
}




