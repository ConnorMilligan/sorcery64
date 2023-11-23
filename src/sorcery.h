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

/* Maze */
void mazeBuild(Maze *maze);
bool mazeGetPos(Maze *maze, int8 x, int8 y);

/* Player */
void playerBuild(Player *player);
bool playerAttemptMove(Player *player, Maze *maze, enum Movement move);
void playerMakeTurn(Player *player, enum Movement move);
void playerAttackEnemy(Context *ctx);
bool playerAddXp(Context *ctx, Stats *lvlStats);

/* Enemy */
void enemyBuild(Enemy *enemy, uint8 level);
void enemyAttack(Context *ctx, bool playerDefending);

#endif