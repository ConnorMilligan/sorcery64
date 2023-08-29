#include "sorcery.h"

#include <cbm.h>
#include <conio.h>
#include <stdio.h>

extern unsigned char XSize, YSize;

void menuDrawTeeLine(unsigned int y) {
    cputcxy(0, y, CH_LTEE);
    chline(XSize - 2);
    cputc(CH_RTEE);
}

void menuDrawWindow() {
    bordercolor(COLOR_BLACK);
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);

    clrscr();
    cursor(0);

    /* Top line */
    cputcxy(0, 0, CH_ULCORNER);
    chline(XSize - 2);
    cputc(CH_URCORNER);

    /* Left line */
    cvlinexy(0, 1, 23);

    /* Bottom line */
    cputc(CH_LLCORNER);
    chline(XSize - 2);
    cputc(CH_LRCORNER);

    /* Right line */
    cvlinexy(XSize - 1, 1, 23);
}

void drawTitleScreen() {
    menuDrawWindow();
    menuDrawTeeLine(20);

    gotoxy((XSize)/2 - 11, 21);
    printf("Press ENTER to begin!");
}