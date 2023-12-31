#ifndef SORCERY_H
#define SORCERY_H

#include "locale.h"

#include <stdbool.h>

// Screen dimensions
extern uint8 XSize, YSize, xBound, yBound;

/* Menu */
void menuDrawTitleScreen(Context *ctx);
void menuDrawQuitPrompt(Context *ctx);
void menuDrawNamePrompt(Context *ctx);
void menuDrawGameScreen(Context *ctx);
void menuDrawBattleScreen(Context *ctx);
void menuDrawDeathScreen(Context *ctx);

void menuDrawMap(Context *ctx);
void menuDrawPlayerStats(Context *ctx);
void menuDrawEnemyStats(Context *ctx);
void menuDrawHelp(Context *ctx);
void menuDrawLevelUp(Context *ctx, Stats *lvlStats);
void menuDrawInventory(Context *ctx, uint8 selection, bool firstDraw);
void menuDrawInventorySelection(Context *ctx, uint8 selection, bool firstDraw);

void menuClearViewport();
void menuClearInfoWindow();

/* Console */
void consoleBufferBuild(ConsoleBuffer *consoleBuffer);
void consoleWrite(ConsoleBuffer *consoleBuffer, uint8 bound);
void consoleBufferAdd(ConsoleBuffer *consoleBuffer, const char *text);
void consoleBufferCleanUp(ConsoleBuffer *consoleBuffer);
void consoleMenuClear();

uint8 getNextWordLen(const char *text, uint8 pos);

/* Context */
void contextBuild(Context *ctx);
void contextCleanUp(Context *ctx);

/* Game */
void buildContext(Context *ctx);
void gameLoop();
void draw(Context *ctx);
void takeInput(Context *ctx);

/* Music */
void musicCombatPlayerTurn();
void musicCombatEnemyTurn();
void musicCombatWin();
void musicDrinkPotion();

/* Maze */
void mazeBuild(Maze *maze);
bool mazeGetPos(Maze *maze, int8 x, int8 y);

/* Player */
void playerBuild(Player *player);
bool playerAttemptMove(Player *player, Maze *maze, enum Movement move);
void playerMakeTurn(Player *player, enum Movement move);
void playerAttackEnemy(Context *ctx);
bool playerAddXp(Context *ctx, Stats *lvlStats);
void playerAddItem(Context *ctx);
void playerUseItem(Context *ctx, uint8 selection, Item *item);
void playerDropItem(Context *ctx, uint8 selection);
void playerRemoveItem(Context *ctx, uint8 selection);

/* Enemy */
void enemyBuild(Enemy *enemy, uint8 level);
void enemyAttack(Context *ctx, bool playerDefending);

/* Item */
void itemBuild(Item *item, enum StatType stat, int8 modifier);
void itemBuildEmpty(Item *item);

#endif