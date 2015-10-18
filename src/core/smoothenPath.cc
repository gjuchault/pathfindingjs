#include "smoothenPath.hpp"

vector<vector<int>> smoothenPath(vector<vector<int>>* path) {
    vector<vector<int>> newPath(path->size(), vector<int>(2));

    newPath[0] = path->at(0);
    int i = 1;

    change change = CHANGE_UNKNOWN;

    for (unsigned int i = 1; i < path->size(); ++i) {
        if (change == CHANGE_UNKNOWN) {
            change = (newPath[newPath.size() - 1][0] == (*path)[i][0]) ? CHANGE_Y : CHANGE_X;
        }

        if (change == CHANGE_Y) {
            if (newPath[newPath.size() - 1][0] != (*path)[i][0]) {
                change = CHANGE_UNKNOWN;
                newPath[i] = path->at(i - 1);
                ++i;
            }
        } else {
            if (newPath[newPath.size() - 1][1] != (*path)[i][1]) {
                change = CHANGE_UNKNOWN;
                newPath[i] = path->at(i - 1);
                ++i;
            }
        }
    }

    newPath[i] = path->at(path->size() - 1);

    return newPath;
}
