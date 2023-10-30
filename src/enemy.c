#include "sorcery.h"

const char heads[1][8][8] = {
    { // Frowny
        {32, 32, 213, 195, 195, 201, 32, 32},
        {32, 206, 32, 32, 32, 32, 205, 32},
        {213, 32, 150, 32, 32, 215, 32, 201},
        {221, 32, 32, 32, 32, 32, 32, 221},
        {221, 32, 175, 210, 210, 175, 32, 221},
        {202, 32, 32, 32, 32, 32, 32, 203},
        {32, 205, 32, 32, 32, 32, 206, 32},
        {32, 32, 202, 195, 195, 203, 32, 32}
    }
};

const char bodies[1][8][8] = {
    { // Ghost
        {32, 32, 206, 32, 32, 205, 32, 32},
        {32, 206, 32, 32, 32, 32, 205, 32},
        {206, 32, 32, 32, 32, 32, 32, 205},
        {221, 32, 32, 32, 32, 32, 32, 221},
        {221, 32, 32, 32, 32, 32, 32, 221},
        {221, 32, 32, 32, 32, 32, 32, 221},
        {221, 213, 201, 213, 201, 213, 201, 221},
        {202, 203, 202, 203, 202, 203, 202, 203}
    }
};


void enemyBuild(Enemy *enemy) {
    enemy->name = "Goblin";

    enemy->head = &heads[0];
    enemy->body = &bodies[0];

    enemy->stats.level = 1;
    enemy->stats.experience = 0;

    enemy->stats.health.health = 10;
    enemy->stats.health.maxHealth = 10;

    enemy->stats.attack = 1;
    enemy->stats.defense = 1;
    enemy->stats.speed = 1;
    enemy->stats.luck = 1;
}