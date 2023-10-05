#include "maze.h"

const char maze[MAZE_HEIGHT][MAZE_WIDTH] = {
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'o', 'o', 'o', 'o', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'x', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'}
};

Position mapGetStart() {
    uint8 x, y;
    Position pos;

    for (y = 0; y < MAZE_HEIGHT; y++) {
        for (x = 0; x < MAZE_WIDTH; x++) {
            if (maze[y][x] == 'x') { // I hate doing it this way, but the compiler has forced my hand :()
                pos.y = y;
                pos.x = x;
                return pos;
            }
        }
    }
}