#ifndef PROJEKT_ETAP2_NODE_H
#define PROJEKT_ETAP2_NODE_H

struct Node {
    int* path;
    int cost;
    int depth;
    int bound;

    Node(int size) : cost(0), depth(0), bound(0) {
        path = new int[size];
        for (int i = 0; i < size; i++) path[i] = -1;
    }

    Node(const Node& source, int size) : cost(source.cost), depth(source.depth), bound(source.bound) {
        path = new int[size];
        for (int i = 0; i < size; i++) path[i] = source.path[i];
    }

    ~Node() {
        delete[] path;
        path = nullptr;
    }
};
#endif //PROJEKT_ETAP2_NODE_H
