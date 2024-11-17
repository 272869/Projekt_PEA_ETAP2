#include <iostream>
#include "BranchAndBound.h"


void BranchAndBound::reduceRow(int **matrixReduced, Node *node) {
    for (int i = 0; i < matrixWeights->getSize(); i++) {
        int min = INT_MAX;
        for (int j = 0; j < matrixWeights->getSize(); j++)
            min = std::min(matrixReduced[i][j], min);
        if (min != INT_MAX && min != 0) {
            node->cost += min;
            for (int j = 0; j < matrixWeights->getSize(); j++) {
                if (matrixReduced[i][j] != INT_MAX)
                    matrixReduced[i][j] -= min;
            }
        }
    }
    reduceColumn(matrixReduced, node);
}

void BranchAndBound::reduceColumn(int **matrixReduced, Node *node) {
    for (int i = 0; i < matrixWeights->getSize(); i++) {
        int min = INT_MAX;
        for (int j = 0; j < matrixWeights->getSize(); j++)
            min = std::min(matrixReduced[j][i], min);
        if (min != INT_MAX && min != 0) {
            node->cost += min;
            for (int j = 0; j < matrixWeights->getSize(); j++) {
                if (matrixReduced[j][i] != INT_MAX)
                    matrixReduced[j][i] -= min;
            }
        }
    }
}

void BranchAndBound::calculateCost(int **matrixReduced, Node *node) {
    reduceRow(matrixReduced, node);
}

void BranchAndBound::makeInfinity(Node *parent, Node *child) {
    child->copyMatrix(parent->matrixReduced);
    child->cost += child->matrixReduced[parent->vertex][child->vertex];
    child->matrixReduced[child->vertex][parent->vertex] = INT_MAX;
    std::fill_n(child->matrixReduced[parent->vertex], matrixWeights->getSize(), INT_MAX);
    for (int i = 0; i < matrixWeights->getSize(); i++) {
        child->matrixReduced[i][child->vertex] = INT_MAX;
    }
}

void BranchAndBound::branchAndBoundAlgorithm() {
    Node *node0 = new Node(0, matrixWeights->getSize());
    node0->copyMatrix(matrix);
    calculateCost(node0->matrixReduced, node0);
    node0->path[0] = 0;  // Set the starting vertex
    node0->pathSize = 1;  // Path size is now 1
    node0->level = 0;
    priorityQueue.push(node0);
    solveLevel();
}


void BranchAndBound::solveLevel() {
    int cost = INT_MAX;
    Node *nodeTop = nullptr;

    while (!priorityQueue.empty()) {
        nodeTop = priorityQueue.top();
        priorityQueue.pop();
        int vertexTop = nodeTop->vertex;

        if (nodeTop->level == matrixWeights->getSize()-1) {
            showPath(nodeTop->path, nodeTop->pathSize);
            break;
        }

        for (int j = 0; j < matrixWeights->getSize(); j++) {
            if (nodeTop->matrixReduced[vertexTop][j] != INT_MAX) {
                Node *child = new Node(j, matrixWeights->getSize());
                child->copyPath(nodeTop->path, nodeTop->pathSize);
                child->copyMatrix(nodeTop->matrixReduced);
                makeInfinity(nodeTop, child);
                child->level = nodeTop->level + 1;
                child->cost += nodeTop->cost;
                calculateCost(child->matrixReduced, child);
                priorityQueue.push(child);
                showPath(nodeTop->path, nodeTop->pathSize);
                printf("%d %d\n", nodeTop->cost, nodeTop->level + 1);
            }
        }
    }
    if (nodeTop) {
        std::cout << "Final cost: " << nodeTop->cost << "\n";
    }
    //delete nodeTop;
}


void BranchAndBound::showPath(int* path, int pathSize) {
    for (int i = 0; i < pathSize; ++i) {
        std::cout << path[i] << "->";
    }
    std::cout << path[0] << "\n";  // Dodanie 0 na końcu, aby zamknąć cykl
}


int **BranchAndBound::getMatrix() const {
    return matrix;
}

void BranchAndBound::printMatrixWages() {
    matrixWeights->showMatrixWages();
}




