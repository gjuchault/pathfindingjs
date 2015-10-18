#ifndef _BACKTRACEH_
#define _BACKTRACEH_

#include "defs.hpp"

#include "astar.hpp"

#include <vector>
#include <algorithm> // reverse

using std::vector;
using std::reverse;

vector<vector<int>> backtrace(Node* n);

#endif
