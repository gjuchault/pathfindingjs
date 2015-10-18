#include "grid.hpp"

Grid Grid_constructor(vector<vector<int>> map, int height, int width) {
    vector<vector<Node*>> nodes = Grid_buildNodes(height, width, map);

    Grid g = { width, height, nodes };
    return g;
}

vector<vector<Node*>> Grid_buildNodes(int height, int width, vector<vector<int>> map) {
    vector<vector<Node*>> nodes;
    nodes.resize(height);
    for (int i = 0; i < height; ++i)
    {
        nodes[i].resize(width);
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            nodes[i][j] = new Node(j, i);
            nodes[i][j]->walkable = !(map[i][j]);
        }
    }

    return nodes;
}

Node* Grid_getNodeAt(Grid* grid, int x, int y) {
    return grid->nodes[y][x];
}

bool Grid_isWalkableAt(Grid* grid, int x, int y) {
    if (!Grid_isInside(grid, x, y)) {
        return false;
    }

    return grid->nodes[y][x]->walkable;
}

bool Grid_isInside(Grid* grid, int x, int y) {
    return (x >= 0 && x < grid->width) && (y >= 0 && y < grid->height);
}

void Grid_setWalkableAt(Grid* grid, int x, int y, bool walkable) {
    grid->nodes[y][x]->walkable = walkable;
}

vector<Node*> Grid_getNeighbors(Grid* grid, Node node, DiagonalMovement diagonalMovement) {
    int x = node.x;
    int y = node.y;

    vector<Node*> neighbors(MAX_NEIGHBORS, nullptr);
    int i = 0;

    bool s0 = false, d0 = false,
         s1 = false, d1 = false,
         s2 = false, d2 = false,
         s3 = false, d3 = false;

    // ↑
    if (Grid_isWalkableAt(grid, x, y - 1)) {
        neighbors[i] = grid->nodes[y - 1][x];
        ++i;
        s0 = true;
    }
    // →
    if (Grid_isWalkableAt(grid, x + 1, y)) {
        neighbors[i] = grid->nodes[y][x + 1];
        ++i;
        s1 = true;
    }
    // ↓
    if (Grid_isWalkableAt(grid, x, y + 1)) {
        neighbors[i] = grid->nodes[y + 1][x];
        ++i;
        s2 = true;
    }
    // ←
    if (Grid_isWalkableAt(grid, x - 1, y)) {
        neighbors[i] = grid->nodes[y][x - 1];
        ++i;
        s3 = true;
    }

    if (diagonalMovement == DM_NEVER) {
        return neighbors;
    }

    if (diagonalMovement == DM_ONLYWHENNOOBSTACLES) {
        d0 = s3 && s0;
        d1 = s0 && s1;
        d2 = s1 && s2;
        d3 = s2 && s3;
    } else if (diagonalMovement == DM_IFATMOSTONEOBSTACLE) {
        d0 = s3 || s0;
        d1 = s0 || s1;
        d2 = s1 || s2;
        d3 = s2 || s3;
    } else if (diagonalMovement == DM_ALWAYS) {
        d0 = true;
        d1 = true;
        d2 = true;
        d3 = true;
    }

    // ↖
    if (d0 && Grid_isWalkableAt(grid, x - 1, y - 1)) {
        neighbors[i] = grid->nodes[y - 1][x - 1];
        ++i;
    }
    // ↗
    if (d1 && Grid_isWalkableAt(grid, x + 1, y - 1)) {
        neighbors[i] = grid->nodes[y - 1][x + 1];
        ++i;
    }
    // ↘
    if (d2 && Grid_isWalkableAt(grid, x + 1, y + 1)) {
        neighbors[i] = grid->nodes[y + 1][x + 1];
        ++i;
    }
    // ↙
    if (d3 && Grid_isWalkableAt(grid, x - 1, y + 1)) {
        neighbors[i] = grid->nodes[y + 1][x - 1];
        ++i;
    }

    return neighbors;
}
