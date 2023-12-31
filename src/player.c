#include "sorcery.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void playerBuild(Player *player) {
    size_t i;
    for (i = 0; i < 9; i++)
        player->name[i] = '\0';

    player->position.x = 0;
    player->position.y = 0;
    player->direction = North;

    player->score = 0;
    
    player->stats.level = 1;
    player->stats.experience = 0;

    player->stats.health.health = 30;
    player->stats.health.maxHealth = 30;

    player->stats.attack = 2;
    player->stats.defense = 2;
    player->stats.speed = 2;
    player->stats.luck = 2;

    player->inventorySize = 0;
    for (i = 0; i < INVENTORY_SIZE; i++)
        itemBuildEmpty(&player->items[i]);
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

void playerAttackEnemy(Context *ctx) {
    uint8 attackMod, damage;
    char *message;

    // As luck increases, so do the odds of a # [0,10] falling between [0,luck/2];
    // If the number falls between [0,luck/2], then the attack is a critical hit (double damage)
    attackMod = (rand() % 10) <= ctx->player.stats.luck/2 ? 2 : 1;

    // Damage range is [attack/2, (3/2)*attack] * modifier
    damage = (rand() % (ctx->player.stats.attack/2) + (ctx->player.stats.attack/2)) * attackMod;

    if (attackMod == 1) {
        message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_COMBAT_PLAYER_ATTACK]) + damage%10 + 1));
        sprintf(message, locale[ctx->locale][LC_COMBAT_PLAYER_ATTACK], damage);
    } else {
        message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_COMBAT_PLAYER_ATTACK_CRIT]) + damage%10 + 1));
        sprintf(message, locale[ctx->locale][LC_COMBAT_PLAYER_ATTACK_CRIT], damage);
    }

    consoleBufferAdd(&ctx->consoleBuffer, message);
    free(message);

    ctx->enemy.stats.health.health -= damage; 
}

bool playerAddXp(Context *ctx, Stats *lvlStats) {
    char *message;

    message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_COMBAT_XP_GAIN]) + (ctx->enemy.stats.level*3)/2%10 + 1));
    sprintf(message, locale[ctx->locale][LC_COMBAT_XP_GAIN], (ctx->enemy.stats.level*3)/2);
    consoleBufferAdd(&ctx->consoleBuffer, message);
    free(message);

    ctx->player.stats.experience += (ctx->enemy.stats.level * 3) / 2;

    if (ctx->player.stats.experience >= XP_FACTOR * ctx->player.stats.level + 1) {
        message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_COMBAT_LEVEL_UP]) + ctx->player.stats.level+1%10 + 1));
        sprintf(message, locale[ctx->locale][LC_COMBAT_LEVEL_UP], ctx->player.stats.level+1);
        consoleBufferAdd(&ctx->consoleBuffer, message);
        free(message);

        ctx->player.stats.level++;

        ctx->player.stats.health.maxHealth += lvlStats->health.maxHealth = 10;
        ctx->player.stats.health.health += lvlStats->health.health = 10;

        ctx->player.stats.attack += lvlStats->attack = rand() % 3 + 1;
        ctx->player.stats.defense += lvlStats->defense = rand() % 3 + 1;
        ctx->player.stats.speed += lvlStats->speed = rand() % 3 + 1;
        ctx->player.stats.luck += lvlStats->luck = rand() % 3 + 1;

        return true;
    }
    return false;
}

void playerAddItem(Context *ctx) {
    size_t i;
    Item item;
    enum StatType stat = rand() % 5;
    int8 modifier = rand() % 2 + 1;
    char *message;

    itemBuild(&item, stat, modifier);

    for (i = 0; i < INVENTORY_SIZE; i++) {
        if (ctx->player.items[i].modifier == 0) {
            ctx->player.items[i] = item;
            message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ITEM_FIND]) + strlen(locale[ctx->locale][LC_POTION_HEALTH]) + 1));
            sprintf(message, locale[ctx->locale][LC_ITEM_FIND], locale[ctx->locale][LC_POTION_HEALTH+stat]);
            consoleBufferAdd(&ctx->consoleBuffer, message);
            free(message);
            ctx->player.inventorySize++;
            ctx->player.score += 10;
            return;
        }
    }

    message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ITEM_FIND_FULL]) + strlen(locale[ctx->locale][LC_POTION_HEALTH]) + 1));
    sprintf(message, locale[ctx->locale][LC_ITEM_FIND_FULL], locale[ctx->locale][LC_POTION_HEALTH]);
    consoleBufferAdd(&ctx->consoleBuffer, message);
    free(message);
}

void playerUseItem(Context *ctx, uint8 selection, Item *item) {
    char *message;
    size_t i, index = 0;

    // make the selection match the index of the item in the inventory
    // this is done because the inventory is not contiguous
    for (i = 0; i < INVENTORY_SIZE; i++) {
        if (ctx->player.items[i].modifier != 0) {
            if (index == selection) {
                index = i;
                break;
            }
            index++;
        }
    }

    message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ITEM_USE]) + strlen(locale[ctx->locale][LC_POTION_HEALTH + ctx->player.items[index].stat]) + 1));
    sprintf(message, locale[ctx->locale][LC_ITEM_USE], locale[ctx->locale][LC_POTION_HEALTH + ctx->player.items[index].stat]);
    consoleBufferAdd(&ctx->consoleBuffer, message);
    free(message);

    switch (ctx->player.items[index].stat) {
        case StatHealth:
            ctx->player.stats.health.health += ctx->player.items[index].modifier;
            if (ctx->player.stats.health.health > ctx->player.stats.health.maxHealth)
                ctx->player.stats.health.health = ctx->player.stats.health.maxHealth;
            break;
        case StatAttack:
            ctx->player.stats.attack += ctx->player.items[index].modifier;
            break;
        case StatDefense:
            ctx->player.stats.defense += ctx->player.items[index].modifier;
            break;
        case StatSpeed:
            ctx->player.stats.speed += ctx->player.items[index].modifier;
            break;
        case StatLuck:
            ctx->player.stats.luck += ctx->player.items[index].modifier;
            break;
    }

    item->modifier = ctx->player.items[index].modifier;
    item->stat = ctx->player.items[index].stat;

    itemBuildEmpty(&ctx->player.items[index]);
    ctx->player.inventorySize--;
}

void playerDropItem(Context *ctx, uint8 selection) {
    char *message;
    size_t i, index = 0;

    // make the selection match the index of the item in the inventory
    // this is done because the inventory is not contiguous
    for (i = 0; i < INVENTORY_SIZE; i++) {
        if (ctx->player.items[i].modifier != 0) {
            if (index == selection) {
                index = i;
                break;
            }
            index++;
        }
    }

    message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ITEM_DISCARD]) + strlen(locale[ctx->locale][LC_POTION_HEALTH + ctx->player.items[index].stat])));
    sprintf(message, locale[ctx->locale][LC_ITEM_DISCARD], locale[ctx->locale][LC_POTION_HEALTH + ctx->player.items[index].stat]);
    consoleBufferAdd(&ctx->consoleBuffer, message);
    free(message);
    
    itemBuildEmpty(&ctx->player.items[index]);
    ctx->player.inventorySize--;
}
