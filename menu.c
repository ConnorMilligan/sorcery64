#include "sorcery.h"

#include <cbm.h>
#include <conio.h>
#include <peekpoke.h>
#include <stdio.h>

extern unsigned char XSize, YSize;

void menuDrawTeeLine(char y) {
    cputcxy(0, y, CH_LTEE);
    chline(XSize - 2);
    cputc(CH_RTEE);
}

void menuDrawWindow(char x, char y, char width, char height) {
    /* Top line */
    cputcxy(x, y, CH_ULCORNER);
    chline(width - 2);
    cputc(CH_URCORNER);

    /* Left line */
    cvlinexy(x, y+1, height-2);

    /* Bottom line */
    cputc(CH_LLCORNER);
    chline(width - 2);
    cputc(CH_LRCORNER);

    /* Right line */
    cvlinexy(x + width - 1, y+1, height-2);
}

void menuDrawTitleScreen() {
    char i, x, y;
    menuDrawWindow(0, 0, XSize, YSize);
    menuDrawTeeLine(20);

    x = y = 1;

    for (i = 0; i < 15; i++) {
        POKE_CHAR(x, y, 77);
        POKE(((55296U+x)+(y*40)), COLOR_RED);

        x = ++y;
    }
    

    cputsxy((XSize)/2 - 11, 21, "press enter to begin!");
}

void menuDrawQuitPrompt() {
    char i, j;
    char x = XSize/2 - 8;
    char y = YSize/2 - 4;

    for(i = 1; i < 14; i++) {
        for (j = 1; j < 7; j++) {
            cputcxy(i + x, y + j, 32);
        }
    }

    textcolor(COLOR_RED);
    menuDrawWindow(x, y, 15, 8);
    textcolor(COLOR_WHITE);
    cputsxy(x + 1, 10, "do you really");
    cputsxy(x + 1, 11, "wish to quit?");

    cputsxy(x + 6, 13, "yes");
    cputsxy(x + 6, 14, "no");
}