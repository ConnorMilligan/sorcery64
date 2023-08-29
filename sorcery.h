#ifndef SORCERY_H
#define SORCERY_H

// Screen dimensions
extern unsigned char XSize, YSize;

/* Menu */
void drawTitleScreen();

void menuDrawTeeLine(unsigned int y);
void menuDrawWindow();

/* Game */
void gameLoop();

#endif