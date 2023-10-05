#ifndef SORCERY_H
#define SORCERY_H

#include "locale.h"

#include <stdbool.h>

#define POKE_CHAR(x, y, char) (POKE(((1024 + (x)) + ((y) * 40)), (char)))
#define POKE_COLOR(x, y, color) (((55296U+x)+(y*40)), color);

#define UP_PRESSED(c) (c == KEY_UP || c == KEY_W || c == KEY_J)
#define DOWN_PRESSED(c) (c == KEY_DOWN || c == KEY_S || c == KEY_K)
#define LEFT_PRESSED(c) (c == KEY_LEFT || c == KEY_A || c == KEY_H)
#define RIGHT_PRESSED(c) (c == KEY_RIGHT || c == KEY_D || c == KEY_L)

#define KEY_J 75
#define KEY_K 74
#define KEY_H 72
#define KEY_L 76

#define KEY_UP 145
#define KEY_DOWN 175
#define KEY_LEFT 157
#define KEY_RIGHT 297

#define KEY_W 87
#define KEY_A 65
#define KEY_S 83
#define KEY_D 68

#define KEY_RETURN 13
#define KEY_BACKSPACE 20

#define CHAR_BLANK 32

typedef unsigned char uint8;
typedef char int8;

typedef struct Player {
    char name[9];
} Player;

enum GameState {
    TitleScreen,
    NamePrompt,
    Game
};

enum quitSelection {
    Quit,
    Remain,
    Pass
};

typedef struct Context {
    Player player;

    bool gameRunning;
    bool quitPrompt;
    bool showMap;

    uint8 quitSelector;
    uint8 choice;
    uint8 input;

    enum Locale locale;
    enum GameState gameState;
} Context;

// Screen dimensions
extern unsigned char XSize, YSize;

/* Menu */
void menuDrawTeeLine(uint8 x, uint8 y);
void menuDrawWindow(uint8 x, uint8 y, uint8 width, uint8 height);


void menuDrawTitleScreen(Context *ctx);
void menuDrawQuitPrompt(uint8 choice);
void menuDrawNamePrompt();
void menuDrawGameScreen(Context *ctx);
void menuDrawPopUpWindow(char *title);
void menuDrawMap(Context *ctx);

/* Selector */
uint8 selectorQuitPrompt();
void namePrompt();

/* Game */
void buildContext(Context *ctx);
void gameLoop();
void draw(Context *ctx);
void takeInput(Context *ctx);

#endif