#include "smoothenPath.hpp"

vector<vector<int>> smoothenPath(vector<vector<int>>* path) {
    vector<vector<int>> newPath(path->size(), vector<int>(2, 0));

    newPath[0] = path->at(0);
    int l = 1;

    change change = CHANGE_UNKNOWN;

    for (unsigned int i = 1; i < path->size(); ++i) {
        int cmpX = (*path)[i - 1][0];
        int cmpY = (*path)[i - 1][1];
        int pX   = (*path)[i][0];
        int pY   = (*path)[i][1];

        if (change == CHANGE_UNKNOWN) {
            if (cmpX == pX) {
                change = CHANGE_Y;
            } else {
                if (cmpY != pY) {
                    // Both change => diagonal

                    // South east
                    if (pY > cmpY && pX > cmpX) {
                        change = CHANGE_SE;
                    }

                    // South west
                    if (pY > cmpY && pX < cmpX) {
                        change = CHANGE_SW;
                    }

                    // North east
                    if (pY < cmpY && pX > cmpX) {
                        change = CHANGE_NE;
                    }

                    // North west
                    if (pY < cmpY && pX < cmpX) {
                        change = CHANGE_NW;
                    }
                } else {
                    change = CHANGE_X;
                }
            }
        }

        bool hasChange = false;
        if (change == CHANGE_Y && !(cmpX == pX && cmpY != pY)) {
            hasChange = true;
        } else if (change == CHANGE_X && !(cmpY == pY && cmpX != pX)) {
            hasChange = true;
        } else if (change == CHANGE_SE && !(pY > cmpY && pX > cmpX)) {
            hasChange = true;
        } else if (change == CHANGE_SW && !(pY > cmpY && pX < cmpX)) {
            hasChange = true;
        } else if (change == CHANGE_NE && !(pY < cmpY && pX > cmpX)) {
            hasChange = true;
        } else if (change == CHANGE_NW && !(pY < cmpY && pX < cmpX)) {
            hasChange = true;
        }

        if (hasChange) {
            change = CHANGE_UNKNOWN;
            newPath[l] = (*path)[i - 1];
            ++l;
        }
    }

    newPath[l] = path->at(path->size() - 1);

    newPath.resize(l + 1);

    return newPath;
}
