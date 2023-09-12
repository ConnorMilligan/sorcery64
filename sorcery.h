#ifndef SORCERY_H
#define SORCERY_H

#define POKE_CHAR(x, y, char) (POKE(((1024 + (x)) + ((y) * 40)), (char)))
#define POKE_COLOR(x, y, color) (((55296U+x)+(y*40)), color);

#define KEY_UP 75
#define KEY_DOWN 74
#define KEY_LEFT 72
#define KEY_RIGHT 76

#define KEY_RETURN 13

typedef unsigned char uint8;
typedef char int8;

// Screen dimensions
extern unsigned char XSize, YSize;

/* Menu */
void menuDrawTitleScreen();

void menuDrawTeeLine(uint8 y);
void menuDrawWindow(uint8 x, uint8 y, uint8 width, uint8 height);
void menuDrawQuitPrompt();

/* Selector */
uint8 selectorQuitPrompt();

/* Game */
void gameLoop();

#endif