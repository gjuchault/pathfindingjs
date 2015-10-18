#include "backtrace.hpp"

vector<vector<int>> backtrace(Node* n) {
    Node* node = n;
    Node* nodeCount = n;

    int l = 1;
    while(nodeCount->parent != nullptr) {
        nodeCount = nodeCount->parent;
        ++l;
    }

    vector<vector<int>> path (l, vector<int>(2));

    vector<int> initVector = { node->x, node->y };
    path[0] = initVector;
    unsigned int len = 1;

    while (node->parent != nullptr) {
        node = node->parent;

        path[len] = { node->x, node->y };
        ++len;
    }

    reverse(path.begin(), path.end());

    return path;
}
