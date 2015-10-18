#include "astar.hpp"
#include "backtrace.hpp"

bool HeapCompare_f::operator() (Node* x, Node* y) {
    return x->f > y->f;
}

AStarFinder AStarFinder_constructor(bool allowDiagonal, bool dontCrossCorners, int weight) {
    AStarFinder astar = { allowDiagonal, dontCrossCorners, weight, 0 };

    if (!astar.allowDiagonal) {
        astar.diagonalMovement = DM_NEVER;
    } else {
        if (astar.dontCrossCorners) {
            astar.diagonalMovement = DM_ONLYWHENNOOBSTACLES;
        } else {
            astar.diagonalMovement = DM_IFATMOSTONEOBSTACLE;
        }
    }

    return astar;
}

float AStarFinder_heuristic(AStarFinder astar, int dx, int dy) {
    float dx_ = (float) dx;
    float dy_ = (float) dy;
    if (astar.diagonalMovement == DM_NEVER) {
        return dx_ + dy_; // 4 ways => manhattan
    } else {
        return (dx < dy) ? F * dx_ + dx_ : F * dy_ + dx_; // 8 ways => octile
    }
}

vector<vector<int>> AStarFinder_findPath(AStarFinder astar, int startX, int startY, int endX, int endY, Grid* grid) {
    Node* startNode     = Grid_getNodeAt(grid, startX, startY);
    Node* endNode       = Grid_getNodeAt(grid, endX, endY);
    DiagonalMovement dm = astar.diagonalMovement;
    int weight          = astar.weight;

    Node* node;
    Node* neighbor;
    vector<Node*> neighbors(MAX_NEIGHBORS, nullptr);
    int i, l, x, y;
    float ng;

    priority_queue<Node*, vector<Node*>, HeapCompare_f> openList;

    startNode->g = 0;
    startNode->f = 0;
    startNode->opened = true;

    openList.push(startNode);

    while (!openList.empty()) {
        node = openList.top();
        openList.pop();
        
        node->closed = true;

        if (node->x == endNode->x && node->y == endNode->y) {
            return backtrace(endNode);
        }

        neighbors = Grid_getNeighbors(grid, *node, dm);

        for (i = 0, l = MAX_NEIGHBORS; i < l; ++i) {
            // We don't know how neighbors there is
            if (neighbors[i] == nullptr) {
                continue;
            }

            neighbor = neighbors[i];

            if (neighbor->closed) {
                continue;
            }

            x = neighbor->x;
            y = neighbor->y;

            ng = node->g + ((x - node->x == 0 || y - node->y == 0) ? 1 : SQRT2);

            if (!neighbor->opened || ng < neighbor->g) {
                neighbor->g = ng;
                neighbor->h = (neighbor->h) ? neighbor->h : weight * AStarFinder_heuristic(astar, abs(x - endX), abs(y - endY));
                neighbor->f = neighbor->g + neighbor->h;

                neighbor->parent = node;

                if (!neighbor->opened) {
                    openList.push(neighbor);
                    neighbor->opened = true;
                } else {
                    // Updated an item, sort again the priority queue using make_heap
                    make_heap(const_cast<Node**>(&openList.top()),
                              const_cast<Node**>(&openList.top()) + openList.size(),
                              HeapCompare_f());
                }
            }
        }
    }

    vector<vector<int>> notFound(0);
    return notFound;
}

