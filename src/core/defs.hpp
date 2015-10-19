#ifndef _DEFH_
#define _DEFH_

#include <cmath> // sqrt(2)

#define MAX_PATHS MAP_HEIGHT * MAP_WIDTH
#define MAX_NEIGHBORS 8

#define SQRT2 sqrt(2)
#define F sqrt(2) - 1

#define DM_ALWAYS 1
#define DM_NEVER 2
#define DM_IFATMOSTONEOBSTACLE 3
#define DM_ONLYWHENNOOBSTACLES 4

#define CHANGE_X -1
#define CHANGE_Y 1
#define CHANGE_NE 2
#define CHANGE_NW 3
#define CHANGE_SE 4
#define CHANGE_SW 5
#define CHANGE_UNKNOWN 0

#define PRINT_MAP false
#define PRINT_PATH false
#define PRINT_SMOOTH false

#endif
