#include "sorcery.h"

#include <cbm.h>
#include <conio.h>
#include <peekpoke.h>
#include <stdio.h>

extern uint8 XSize, YSize;

void menuDrawTeeLine(uint8 x, uint8 y) {
    cputcxy(0, y, CH_LTEE);
    chline(x - 2);
    cputc(CH_RTEE);
}

void menuDrawWindow(uint8 x, uint8 y, uint8 width, uint8 height) {
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
    menuDrawWindow(0, 0, XSize, YSize);
    menuDrawTeeLine(XSize, 20);

    cputsxy((XSize)/2 - 11, 21, "press enter to begin!");
}

void menuDrawQuitPrompt(uint8 choice) {
    uint8 i, j;
    uint8 x = XSize/2 - 8;
    uint8 y = YSize/2 - 4;

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

    choice ? cputcxy(XSize/2 - 4, 14, 218) : cputcxy(XSize/2 - 4, 13, 218);
    choice ? cputcxy(XSize/2 - 4, 13, CHAR_BLANK) : cputcxy(XSize/2 - 4, 14, CHAR_BLANK);
}

void menuDrawNamePrompt() {
    menuDrawWindow(0, 0, XSize, YSize);
    cputsxy((XSize)/2 - 12, YSize/2-1, "please enter your name:");
    cputcxy((XSize)/2 - 5, YSize/2+1, 62);
}

void menuDrawGameScreen(Context *ctx) {
    uint8 xBound = (XSize - XSize/3)+2;
    uint8 yBound = 17;
    uint8 x = 1, y = 1;
    size_t i;

    // Draw lines
    menuDrawWindow(0, 0, XSize, YSize);
    menuDrawTeeLine(xBound+1, yBound);
    cvlinexy(xBound, 1, YSize-2);
    cputcxy(xBound, 0, 178);
    cputcxy(xBound, YSize-1, 177);
    cputcxy(xBound, yBound, 179);

    // Draw player information
    cputsxy(xBound+1, 1, ctx->player.name);
    gotoxy(xBound+1, 2);
    cprintf("lv: %d", 1);
    gotoxy(xBound+1, 3);
    cprintf("hp: %d/%d", 30, 30);

    cputsxy(xBound+1, 5, "stats");
    gotoxy(xBound+1, 6);
    cprintf("atk: %d", 2);
    gotoxy(xBound+1, 7);
    cprintf("def: %d", 2);
    gotoxy(xBound+1, 8);
    cprintf("spd: %d", 2);
    gotoxy(xBound+1, 9);
    cprintf("lck: %d", 2);

    cputsxy(xBound+1, 11, "location");
    gotoxy(xBound+1, 12);
    cprintf("loc: %d,%d", 2, 2);
    gotoxy(xBound+1, 13);
    cprintf("dir: %c", 'n');


    cvlinexy(6, 3, 10);
    for (i = 0; i < 3; i++) {
        cputcxy(x, y, 197);
        cputcxy(x+1, y, 195);
        cputcxy(x+2, y, 210);
        cputcxy(x+3, y, 175);
        y++;
        x+=4;
    }
    
    x = 1;
    y = yBound-1;

    for (i = 0; i < 3; i++) {
        cputcxy(x, y, 175);
        cputcxy(x+1, y, 210);
        cputcxy(x+2, y, 195);
        cputcxy(x+3, y, 197);
        y--;
        x+=4;
    }

}