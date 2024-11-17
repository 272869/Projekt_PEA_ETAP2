#include "../Utils/Matrix.h"
#include "../Utils/PriorityQueue.h"
#include "../Utils/FIFOQueue.h"

class BranchAndBound {

public:
    BranchAndBound() {
        matrixWeights = new Matrix();
        if (matrixWeights->getMatrixWeights() != nullptr)
            matrix = matrixWeights->getMatrixWeights();
    }

    ~BranchAndBound() {
        if (matrixWeights->getMatrixWeights() != nullptr)
            matrixWeights->deleteMatrixTable(matrix);
        delete matrixWeights;
    }

    void branchAndBoundAlgorithm();
    int **getMatrix() const;

private:
    int **matrix = nullptr;
    Matrix *matrixWeights;
    PriorityQueue priorityQueue{1000}; // Max queue size assumption
    FIFOQueue fifoQueue{1000}; // FIFO Queue for BFS
    void calculateCost(int **matrixReduced, Node *node);
    void reduceRow(int **matrixReduced, Node *node);
    void reduceColumn(int **matrixReduced, Node *node);
    void makeInfinity(Node *parent, Node *child);
    static void showPath(int* path, int pathSize);
    void solveLevel();  // Existing DFS level solver

};
