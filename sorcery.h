#ifndef SORCERY_H
#define SORCERY_H

#include <stdbool.h>

#define POKE_CHAR(x, y, char) (POKE(((1024 + (x)) + ((y) * 40)), (char)))
#define POKE_COLOR(x, y, color) (((55296U+x)+(y*40)), color);

#define KEY_UP 75
#define KEY_DOWN 74
#define KEY_LEFT 72
#define KEY_RIGHT 76

#define KEY_RETURN 13
#define KEY_BACKSPACE 20

#define CHAR_BLANK 32

typedef unsigned char uint8;
typedef char int8;

typedef struct Player {
    char name[16];
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

    uint8 quitSelector;
    uint8 choice;
    uint8 input;

    enum GameState gameState;
} Context;

// Screen dimensions
extern unsigned char XSize, YSize;

/* Menu */
void menuDrawTeeLine(uint8 x, uint8 y);
void menuDrawWindow(uint8 x, uint8 y, uint8 width, uint8 height);


void menuDrawTitleScreen();
void menuDrawQuitPrompt();
void menuDrawNamePrompt();
void menuDrawGameScreen();

/* Selector */
uint8 selectorQuitPrompt();
void namePrompt();

/* Game */
void buildContext(Context *ctx);
void gameLoop();
void draw(Context *ctx);
void takeInput(Context *ctx);

#endif