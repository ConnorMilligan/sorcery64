#include "constants.h"

#include <string.h>

void mazeBuild(Maze *maze) {
    Position pos = {1, 18};

    uint8 map[MAZE_HEIGHT][MAZE_OFFSET] = {
        {255, 255, 15},
        {1, 0, 8},
        {253, 255, 11},
        {253, 255, 11},
        {253, 255, 11},
        {253, 192, 11},
        {253, 222, 11},
        {253, 222, 11},
        {253, 222, 11},
        {13, 222, 11},
        {237, 223, 11},
        {237, 31, 8},
        {225, 255, 11},
        {253, 255, 11},
        {253, 255, 11},
        {253, 255, 11},
        {253, 255, 11},
        {253, 255, 11},
        {1, 0, 8},
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