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