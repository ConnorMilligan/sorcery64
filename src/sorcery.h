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
void menuDrawMap(Context *ctx);

/* Console */
void consoleWrite(char *text);

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

#endif