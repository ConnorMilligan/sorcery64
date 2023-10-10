#ifndef SORCERY_H
#define SORCERY_H

#include "locale.h"

#include <stdbool.h>

// Screen dimensions
extern unsigned char XSize, YSize;

/* Menu */
void menuDrawTitleScreen(Context *ctx);
void menuDrawQuitPrompt(Context *ctx);
void menuDrawNamePrompt(Context *ctx);
void menuDrawGameScreen(Context *ctx);
void menuDrawPopUpWindow(char *title);
void menuDrawMap(Context *ctx);

/* Game */
void buildContext(Context *ctx);
void gameLoop();
void draw(Context *ctx);
void takeInput(Context *ctx);

/* Maze */
void mazeBuild(Maze *maze);
bool mazeGetPos(Maze *maze, uint8 x, uint8 y);

/* Player */
void playerBuild(Player *player);

#endif