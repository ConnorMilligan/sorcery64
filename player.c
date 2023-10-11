#include "sorcery.h"

#include <string.h>

void playerBuild(Player *player) {

    strcpy(player->name, "p");

    player->position.x = 0;
    player->position.y = 0;
    player->direction = North;
    
    player->stats.level = 1;
    player->stats.experience = 0;

    player->stats.health.health = 30;
    player->stats.health.maxHealth = 30;

    player->stats.attack = 2;
    player->stats.defense = 2;
    player->stats.speed = 2;
    player->stats.luck = 2;

}

bool playerAttemptMove(Player *player, Maze *maze, enum Movement move) {
    // Some particularly clown-like syntax
    if ((player->direction == North && move == Forward) || (player->direction == South && move == Backward)) {
        // Make sure the player does not leave the map
        if (player->position.y == 0)
            return false;
        // Make sure there is no wall in the way
        else if (mazeGetPos(maze, player->position.x, player->position.y-1))
            return false;
        // if good, move
        else
            player->position.y--;
    }

    else if ((player->direction == North && move == Backward) || (player->direction == South && move == Forward)) {
        if (player->position.y == MAZE_HEIGHT-1)
            return false;
        else if (mazeGetPos(maze, player->position.x, player->position.y+1))
            return false;
        else
            player->position.y++;
    }

    else if ((player->direction == East && move == Forward) || (player->direction == West && move == Backward)) {
        if (player->position.x == MAZE_WIDTH-1)
            return false;
        else if (mazeGetPos(maze, player->position.x+1, player->position.y))
            return false;
        else
            player->position.x++;
    }

    else if ((player->direction == East && move == Backward) || (player->direction == West && move == Forward)) {
        if (player->position.x == 0)
            return false;
        else if (mazeGetPos(maze, player->position.x-1, player->position.y))
            return false;
        else
            player->position.x--;
    }
    return true;
}

void playerMakeTurn(Player *player, enum Movement move) {
    switch (move) {
        case Right:
            player->direction == West ? player->direction = North : player->direction++;
            break;
        case Left:
            player->direction == North ? player->direction = West : player->direction--;
            break;
        
    }
}
