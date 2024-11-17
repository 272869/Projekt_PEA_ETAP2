#include <iostream>


class Node {
private:
    int numberOfVertexes;
public:
    int* path;  // Use a dynamic array instead of std::vector
    int pathSize;  // To track the size of the path array
    int level;
    int **matrixReduced;
    long long cost = 0;
    int vertex;

    Node(int vertex, int numberOfVertexes) {
        this->vertex = vertex;
        this->numberOfVertexes = numberOfVertexes;
        pathSize = 0;
        path = new int[numberOfVertexes];
        matrixReduced = new int *[numberOfVertexes];
        for (int i = 0; i < numberOfVertexes; i++) {
            matrixReduced[i] = new int[numberOfVertexes];
        }
    }

    // Copy matrix from another matrix
    void copyMatrix(int **m) const {
        for (int i = 0; i < numberOfVertexes; i++) {
            for (int j = 0; j < numberOfVertexes; ++j) {
                this->matrixReduced[i][j] = m[i][j];
            }
        }
    }

    // Copy the path from the parent node and add the current vertex to it
    void copyPath(int* p, int size) {
        if (size > pathSize) {
            delete[] path;
            path = new int[size];  // Re-allocate memory
        }
        for (int i = 0; i < size; i++) {
            this->path[i] = p[i];  // Copy existing path
        }
        this->path[size] = vertex;  // Add the current vertex
        pathSize = size + 1;  // Update path size
    }


    ~Node() {
        delete[] path;
        for (int i = 0; i < numberOfVertexes; i++) {
            delete[] matrixReduced[i];
        }
        delete[] matrixReduced;
    }
};
