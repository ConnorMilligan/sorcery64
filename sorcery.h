#ifndef SORCERY_H
#define SORCERY_H

#define POKE_CHAR(x, y, char) (POKE(((1024 + (x)) + ((y) * 40)), (char)))
#define POKE_COLOR(x, y, color) (((55296U+x)+(y*40)), color);

// Screen dimensions
extern unsigned char XSize, YSize;

/* Menu */
void menuDrawTitleScreen();

void menuDrawTeeLine(char y);
void menuDrawWindow(char x, char y, char width, char height);
void menuDrawQuitPrompt();

/* Selector */
int selectorQuitPrompt();

/* Game */
void gameLoop();

#endif