#ifndef _ASTARH_
#define _ASTARH_

#include "defs.hpp"

#include "diagonalMovement.hpp"
#include "grid.hpp"
#include "node.hpp"

#include <algorithm> // make_heap
#include <vector>
#include <queue>
#include <vector>

using std::vector;
using std::priority_queue;
using std::make_heap;
using std::vector;

class HeapCompare_f {
    public:
        bool operator() (Node* x, Node* y);
};

typedef struct AStarFinder {
    bool allowDiagonal;
    bool dontCrossCorners;
    int weight;
    DiagonalMovement diagonalMovement;
} AStarFinder;

AStarFinder AStarFinder_constructor(bool allowDiagonal, bool dontCrossCorners, int weight);

vector<vector<int>> AStarFinder_findPath(AStarFinder astar, int startX, int startY, int endX, int endY, Grid* grid);

float AStarFinder_heuristic(AStarFinder astar, int dx, int dy);

#endif
