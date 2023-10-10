#include "sorcery.h"

#include <string.h>

void playerBuild(Player *player) {

    strcpy(player->name, "p");

    player->position.x = 0;
    player->position.y = 0;
    player->direction = North;
    
    player->level = 1;
    player->experience = 0;

    player->health.health = 30;
    player->health.maxHealth = 30;

    player->attack = 2;
    player->defense = 2;
    player->speed = 2;
    player->luck;

}