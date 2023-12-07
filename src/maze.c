#include "constants.h"

#include <string.h>

void mazeBuild(Maze *maze) {
    Position pos = {1, 18};

    uint8 map[MAZE_HEIGHT][MAZE_OFFSET] = {
        {255, 255, 15},
        {3, 224, 15},
        {219, 239, 15},
        {219, 15, 14},
        {219, 239, 14},
        {209, 192, 8},
        {21, 222, 11},
        {245, 30, 8},
        {245, 222, 11},
        {5, 216, 11},
        {189, 219, 11},
        {189, 3, 8},
        {1, 250, 11},
        {189, 250, 11},
        {129, 194, 11},
        {253, 218, 11},
        {253, 216, 11},
        {253, 222, 11},
        {1, 30, 8},
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