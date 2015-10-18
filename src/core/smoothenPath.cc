#include "smoothenPath.hpp"

vector<vector<int>> smoothenPath(vector<vector<int>>* path) {
    vector<vector<int>> newPath(path->size(), vector<int>(2, 0));

    newPath[0] = path->at(0);
    int l = 1;

    change change = CHANGE_UNKNOWN;

    for (unsigned int i = 1; i < path->size(); ++i) {
        int cmpX = newPath[l - 1][0];
        int cmpY = newPath[l - 1][1];
        int pX   = (*path)[i][0];
        int pY   = (*path)[i][1];


        if (change == CHANGE_UNKNOWN) {
            change = (cmpX == pX) ? CHANGE_Y : CHANGE_X;
        }

        if (change == CHANGE_Y) {
            if (cmpX != pX) {
                change = CHANGE_UNKNOWN;
                newPath[l] = (*path)[i - 1];
                ++l;
            }
        } else {
            if (cmpY != pY) {
                change = CHANGE_UNKNOWN;
                newPath[l] = (*path)[i - 1];
                ++l;
            }
        }
    }

    newPath[l] = path->at(path->size() - 1);

    newPath.resize(l);

    return newPath;
}
