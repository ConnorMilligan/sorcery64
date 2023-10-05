#ifndef MAZE_H
#define MAZE_H

#include "constants.h"

#define MAZE_WIDTH  20
#define MAZE_HEIGHT 20

extern const char maze[MAZE_HEIGHT][MAZE_WIDTH];

Position mapGetStart();

#endif