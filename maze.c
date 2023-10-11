#include "constants.h"

#include <string.h>

void mazeBuild(Maze *maze) {
    Position pos = {1, 18};

    uint8 map[MAZE_HEIGHT][MAZE_OFFSET] = {
        {255, 255, 15},
        {255, 255, 15},
        {255, 255, 15},
        {255, 255, 15},
        {255, 255, 15},
        {255, 192, 15},
        {255, 222, 15},
        {255, 222, 15},
        {255, 222, 7},
        {15, 222, 7},
        {239, 223, 7},
        {239, 31, 0},
        {225, 255, 15},
        {252, 255, 15},
        {253, 255, 15},
        {253, 255, 15},
        {253, 255, 15},
        {252, 255, 15},
        {253, 255, 15},
        {255, 255, 15}
    };

    memcpy(maze->map, map, sizeof(map));
    maze->start = pos;
}



bool mazeGetPos(Maze *maze, uint8 x, uint8 y) {
    int bitPosition = x % 8;
    unsigned char byte = maze->map[y][x/8];

    return (byte >> bitPosition) & 1;
}