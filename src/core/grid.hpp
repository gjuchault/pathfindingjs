#ifndef _GRIDH_
#define _GRIDH_

#include "defs.hpp"

#include "diagonalMovement.hpp"
#include "node.hpp"

#include <algorithm> // fill
#include <vector>

using std::vector;
using std::fill;

typedef struct Grid {
    int width;
    int height;
    int walkerSize;
    vector<vector<Node*>> nodes;
} Grid;

Grid Grid_constructor(vector<vector<int>> map, int height, int width, int walkerSize);

vector<vector<Node*>> Grid_buildNodes(int width, int height, vector<vector<int>> map);

Node* Grid_getNodeAt(Grid* grid, int x, int y);

bool Grid_isWalkableAt(Grid* grid, int x, int y);

bool Grid_isInside(Grid* grid, int x, int y);

void Grid_setWalkableAt(Grid* grid, int x, int y, bool walkable);

vector<Node*> Grid_getNeighbors(Grid* grid, Node node, DiagonalMovement diagonalMovement);

#endif
