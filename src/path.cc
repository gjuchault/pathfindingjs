#include "core/defs.hpp"

#include "core/astar.hpp"
#include "core/grid.hpp"
#include "core/smoothenPath.hpp"

#include <chrono>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::stringstream;
using std::vector;

int main () {
    printf("Pathfinding\n");
    srand(time(0));

    vector<vector<int>> map;
    int x0 = 0;
    int y0 = 0;
    int x1, y1;

    map.resize(MAP_HEIGHT);
    for (unsigned int i = 0; i < MAP_HEIGHT; ++i)
    {
        map[i].resize(MAP_WIDTH);
    }

    // Generate an alterned map
    for (unsigned int i = 0; i < MAP_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            map[i][j] = (j % 2 == 0) ? 0 : 1;
        }
    }

    for (unsigned int i = 1; i < MAP_WIDTH; i +=2) {
        int rowAvailable = rand() % (MAP_HEIGHT - 1) + 1;
        map[rowAvailable][i] = 0;

        if (i == MAP_WIDTH - 1) {
            x1 = i;
            y1 = rowAvailable;
        }
    }

    // Create the finder
    Grid grid         = Grid_constructor(map, MAP_HEIGHT, MAP_WIDTH, 1);
    AStarFinder astar = AStarFinder_constructor(true, true, 1);

    printf("Starting !\n");
    // Start the timer
    auto start = high_resolution_clock::now();

    vector<vector<int>> path   = AStarFinder_findPath(astar, x0, y0, x1, y1, &grid);
    vector<vector<int>> smooth = smoothenPath(&path);

    // End the timer
    auto elapsed = high_resolution_clock::now() - start;
    long long ms = duration_cast<microseconds>(elapsed).count();

    printf("Temps %fs\n", (float)ms / (float)(1000 * 1000));
    printf("Found %d\n", path.size() > 0);

    if (PRINT_MAP) {
        // Grid to string
        stringstream ss;
        for (unsigned int i = 0; i < map.size(); ++i)
        {
            ss << "{";

            for (unsigned int j = 0; j < map[i].size(); ++j) {
                if (j != 0) {
                    ss << ",";
                }

                ss << " " << map[i][j] << " ";
            }

            ss << "}";

            if (i != map.size() - 1) {
                ss << ",";
            }

            ss << "\n";
        }
        ss << "\n";
        printf("%s\n", ss.str().c_str());
    }

    if (PRINT_PATH) {
                // Path to string
        stringstream ssp;
        for (unsigned int i = 0; i < path.size(); ++i)
        {
            ssp << "[ ";
            ssp << path[i][0] << " " << path[i][1];
            ssp << " ]";
        }
        printf("%s\n", ssp.str().c_str());
    }

    if (PRINT_SMOOTH) {
        // Path to string
        stringstream sssp;
        for (unsigned int i = 0; i < smooth.size(); ++i)
        {
            sssp << "[ ";
            sssp << smooth[i][0] << " " << smooth[i][1];
            sssp << " ]";
        }
        printf("%s\n", sssp.str().c_str());
    }
}
