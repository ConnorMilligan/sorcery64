#include "sorcery.h"
#include "locale.h"

#include <cbm.h>
#include <conio.h>
#include <peekpoke.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern uint8 XSize, YSize, xBound, yBound;
extern const char* locale[2][LC_NUM_STRINGS];

const char titleArt[19][38] = {
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
    { 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0xa6, 0x20, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0x20 },
    { 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0x20 },
    { 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0x20 },
    { 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20 },
    { 0x20, 0xa6, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0xa6, 0x22, 0x20, 0xa6, 0xa6, 0xa6, 0xa6, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0xa6, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0xa6, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0xa6, 0xa6, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa6, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
    { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 },
};

void menuDrawTeeLine(uint8 x, uint8 y);
void menuDrawWindow(uint8 x, uint8 y, uint8 width, uint8 height);
void menuDrawLeftSector(Context *ctx);
void menuDrawRightSector(Context *ctx);
void menuDrawCenterSector(Context *ctx);


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

void menuDrawTitleScreen(Context *ctx) {
    size_t i, j;

    menuDrawWindow(0, 0, XSize, YSize);
    menuDrawTeeLine(XSize, 20);

    for (i = 0; i < 19; i++) {
        for (j = 0; j < 38; j++) {
            if (i == 10)
                textcolor(COLOR_RED);
            if (titleArt[i][j] != 0x20)
                cputcxy(j+1, i+1, titleArt[i][j]);
        }
    }
    textcolor(COLOR_WHITE);
    cputsxy((XSize)/2 - strlen(locale[ctx->locale][LC_TITLE_PROMPT])/2, YSize - 3, locale[ctx->locale][LC_TITLE_PROMPT]);
    gotoxy(1, YSize-1);
    cprintf(locale[ctx->locale][LC_TITLE_LANG], ctx->locale == English ? "en" : "eo");
}

void menuDrawQuitPrompt(Context *ctx) {
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
    cputsxy(x + 1, 10, locale[ctx->locale][LC_QUIT_PROMPT1]);
    cputsxy(x + 1, 11, locale[ctx->locale][LC_QUIT_PROMPT2]);

    cputsxy(x + 6, 13, locale[ctx->locale][LC_YES]);
    cputsxy(x + 6, 14, locale[ctx->locale][LC_NO]);

    ctx->quitSelector ? cputcxy(XSize/2 - 4, 14, 218) : cputcxy(XSize/2 - 4, 13, 218);
    ctx->quitSelector ? cputcxy(XSize/2 - 4, 13, CHAR_BLANK) : cputcxy(XSize/2 - 4, 14, CHAR_BLANK);
}

void menuDrawDeathScreen(Context *ctx) {
    size_t i, j;
    char str[10];

    menuDrawWindow(0, 0, XSize, YSize);

    // Draw the tombstone
    // right line is one more than the left line (zero indexed)
    cvlinexy(XSize-12, YSize/2, YSize/2);
    cvlinexy(12, YSize/2, YSize/2);

    chlinexy(17, YSize/2-5, 7);

    for (i = 0; i < 5; i++) {
        cputcxy(12+i, YSize/2-i, 206);
        cputcxy(XSize-12-i, YSize/2-i, 205);
    }

    // lil cross
    cvlinexy((XSize)/2, YSize/2-2, 4);
    chlinexy((XSize)/2-1, YSize/2-1, 3);
    cputcxy((XSize)/2, YSize/2-1, 219);

    // Text
    cputsxy(XSize/2 - strlen(locale[ctx->locale][LC_DEATH_TOMBSTONE])/2, YSize/2+4, locale[ctx->locale][LC_DEATH_TOMBSTONE]);
    cputsxy(XSize/2 - strlen(ctx->player.name)/2, YSize/2+5, ctx->player.name);

    sprintf(str, "%u", ctx->player.score);

    gotoxy(XSize/2 - strlen(locale[ctx->locale][LC_SCORE_FULL])/2 - strlen(str)/2 + 1, YSize/2+7);
    cprintf(locale[ctx->locale][LC_SCORE_FULL], ctx->player.score);
}

void menuDrawNamePrompt(Context *ctx) {
    menuDrawWindow(0, 0, XSize, YSize);
    cputsxy((XSize)/2 - strlen(locale[ctx->locale][LC_NAME_PROMPT])/2, YSize/2-1, locale[ctx->locale][LC_NAME_PROMPT]);
    cputcxy((XSize)/2 - 5, YSize/2+1, 62);
}

void menuDrawPlayerInfo(Context *ctx) {
    cputsxy(xBound+1, 1, ctx->player.name);
    gotoxy(xBound+1, 2);
    cprintf(locale[ctx->locale][LC_STAT_LEVEL], ctx->player.stats.level);
    gotoxy(xBound+1, 3);
    cprintf(locale[ctx->locale][LC_STAT_HP], ctx->player.stats.health.health, ctx->player.stats.health.maxHealth);

    // Stats
    cputsxy(xBound+1, 5, locale[ctx->locale][LC_SIDEBAR_STAT_LABEL]);
    gotoxy(xBound+1, 6);
    cprintf(locale[ctx->locale][LC_STAT_ATK], ctx->player.stats.attack);
    gotoxy(xBound+1, 7);
    cprintf(locale[ctx->locale][LC_STAT_DEF], ctx->player.stats.defense);
    gotoxy(xBound+1, 8);
    cprintf(locale[ctx->locale][LC_STAT_SPD], ctx->player.stats.speed);
    gotoxy(xBound+1, 9);
    cprintf(locale[ctx->locale][LC_STAT_LCK], ctx->player.stats.luck);

    // Location
    cputsxy(xBound+1, 11, locale[ctx->locale][LC_SIDEBAR_LOC_LABEL]);
    gotoxy(xBound+1, 12);
    cprintf(locale[ctx->locale][LC_SIDEBAR_LOC], ctx->player.position.x, ctx->player.position.y);
    gotoxy(xBound+1, 13);
    cprintf(locale[ctx->locale][LC_SIDEBAR_DIR], locale[ctx->locale][ctx->player.direction]);

    // Score
    cputsxy(xBound+1, 15, locale[ctx->locale][LC_SCORE]);
    gotoxy(xBound+1, 16);
    cprintf("%d", ctx->player.score);

}

void menuDrawLeftSector(Context *ctx) {
    uint8 posX, posY;
    uint8 x = 1, y = 2;
    size_t i, j;
    bool isWall, isWallAhead;

    posX = ctx->player.position.x;
    posY = ctx->player.position.y;

    for (i = 0; i < 3; i++) {
        switch (ctx->player.direction) {
            case North:
                isWall = mazeGetPos(&ctx->maze, posX-1, posY-i);
                isWallAhead = mazeGetPos(&ctx->maze, posX, posY-i);
                break;
            case South:
                isWall = mazeGetPos(&ctx->maze, posX+1, posY+i);
                isWallAhead = mazeGetPos(&ctx->maze, posX, posY+i);
                break;
            case East:
                isWall = mazeGetPos(&ctx->maze, posX+i, posY-1);
                isWallAhead = mazeGetPos(&ctx->maze, posX+i, posY);
                break;
            case West:
                isWall = mazeGetPos(&ctx->maze, posX-i, posY+1);
                isWallAhead = mazeGetPos(&ctx->maze, posX-i, posY);
                break;
        }

        if (isWallAhead) {
            for (j = x+(4*i); j < xBound/2+1; j++) {
                cputcxy(j, y+i, 197);
                cputcxy(j, y+(yBound-2)-i-2, 175);
                if (ctx->gameState == Battle && j > xBound/2-5) { break; }
            }
            break;
        }

        else if (isWall) {

            // Top horizontal line part1
            cputcxy(x+(4*i), y+i, 197);
            cputcxy(x+1+(4*i), y+i, 195);

            // Bottom horizontal line part1
            cputcxy(x+(4*i), y+(yBound-4)-i, 175);
            cputcxy(x+1+(4*i), y+(yBound-4)-i, 210);


            // Hacky way to prevent flickering when in battle
            if (i == 2 && ctx->gameState == Battle) {break;}
            // Top horizontal line part2
            cputcxy(x+2+(4*i), y+i, 210);
            cputcxy(x+3+(4*i), y+i, 175);

            // Bottom horizontal line part2
            cputcxy(x+2+(4*i), y+(yBound-4)-i, 195);
            cputcxy(x+3+(4*i), y+(yBound-4)-i, 197);

        }
        else {
            for (j = 0; j < 4; j++) {
                cputcxy(x+(4*i)+j, y+i+1, 197);
                cputcxy(x+(4*i)+j, y+(yBound-4)-i-1, 175);
                // flickering in battle prevention
                if (i == 2 && ctx->gameState == Battle) {break;}
            }
        }

        // Vertical line
        if (ctx->gameState != Battle || i != 2) {
            cvlinexy(4*(i+1), 3+i, 12-(2*i));
        }
    }
}

void menuDrawRightSector(Context *ctx) {
    uint8 posX, posY;
    uint8 x = xBound-1, y = 2;
    size_t i, j;
    bool isWall, isWallAhead;

    posX = ctx->player.position.x;
    posY = ctx->player.position.y;

    for (i = 0; i < 3; i++) {
        switch (ctx->player.direction) {
            case North:
                isWall = mazeGetPos(&ctx->maze, posX+1, posY-i);
                isWallAhead = mazeGetPos(&ctx->maze, posX, posY-i);
                break;
            case South:
                isWall = mazeGetPos(&ctx->maze, posX-1, posY+i);
                isWallAhead = mazeGetPos(&ctx->maze, posX, posY+i);
                break;
            case East:
                isWall = mazeGetPos(&ctx->maze, posX+i, posY+1);
                isWallAhead = mazeGetPos(&ctx->maze, posX+i, posY);
                break;
            case West:
                isWall = mazeGetPos(&ctx->maze, posX-i, posY-1);
                isWallAhead = mazeGetPos(&ctx->maze, posX-i, posY);
                break;
        }

        if (isWallAhead) {
            for (j = xBound-(4*i)-1; j > xBound/2; j--) {
                cputcxy(j, y+i, 197);
                cputcxy(j, y+(yBound-2)-i-2, 175);
                if (ctx->gameState == Battle && j < xBound/2+6) { break; }
            }
            break;
        }

        else if (isWall) {

            // Top horizontal line
            cputcxy(x-(4*i), y+i, 197);
            cputcxy(x-1-(4*i), y+i, 195);
            
            // Bottom horizontal line
            cputcxy(x-(4*i), y+(yBound-4)-i, 175);
            cputcxy(x-1-(4*i), y+(yBound-4)-i, 210);

            // Hacky way to prevent flickering when in battle
            if (i == 2 && ctx->gameState == Battle) {break;}
            // Top horizontal line
            cputcxy(x-2-(4*i), y+i, 210);
            cputcxy(x-3-(4*i), y+i, 175);
            // Bottom horizontal line
            cputcxy(x-2-(4*i), y+(yBound-4)-i, 195);
            cputcxy(x-3-(4*i), y+(yBound-4)-i, 197);

        }
        else {
            for (j = 1; j < 4; j++) {
                cputcxy(xBound-(4*i)-j, y+i+1, 197);
                cputcxy(xBound-(4*i)-j, y+(yBound-4)-i-1, 175);
                // flickering in battle prevention
                if (i == 2 && ctx->gameState == Battle) {break;}
            }
        }

        // Vertical line
        if (ctx->gameState != Battle || i != 2) {
            cvlinexy(xBound-4*(i+1), 3+i, 12-(2*i));
        }
    }
}

// This covers a specific case, but a pretty important one,
void menuDrawCenterSector(Context *ctx) {
    uint8 posX, posY;
    uint8 x = (xBound/2)-1, y = 5;
    size_t i;
    bool wall;

    posX = ctx->player.position.x;
    posY = ctx->player.position.y;

    switch (ctx->player.direction) {
        case North:
            wall = posY-3 >= 0 ? (mazeGetPos(&ctx->maze, posX, posY-3) && !mazeGetPos(&ctx->maze, posX, posY-2)) : false;
            break;
        case South:
            wall = posY+3 <= MAZE_HEIGHT-1 ? (mazeGetPos(&ctx->maze, posX, posY+3) && !mazeGetPos(&ctx->maze, posX, posY+2)) : false;
            break;
        case East:
            wall = posX+3 <= MAZE_WIDTH-1 ? (mazeGetPos(&ctx->maze, posX+3, posY) && !mazeGetPos(&ctx->maze, posX+2, posY)) : false;
            break;
        case West:
            wall = posX-3 >= 0 ? (mazeGetPos(&ctx->maze, posX-3, posY) && !mazeGetPos(&ctx->maze, posX-2, posY)) : false;
            break;
    }

    if (wall && ctx->gameState != Battle) {
        for (i = 0; i < 4; i++) {
            cputcxy(x+i, y, 197);
            cputcxy(x+i, yBound-y, 175);
        }
    }
}

void menuDrawGameScreen(Context *ctx) {
    clrscr();

    // Draw lines
    menuDrawWindow(0, 0, XSize, YSize);
    menuDrawTeeLine(XSize, yBound);
    // Separator line
    cvlinexy(xBound, 1, yBound-1);
    cputcxy(xBound, 0, 178);
    cputcxy(xBound, yBound, 177);

    // Draw player information
    menuDrawPlayerInfo(ctx);

    // Draw walls
    menuDrawLeftSector(ctx);
    menuDrawRightSector(ctx);
    menuDrawCenterSector(ctx);

    // Display console
    consoleWrite(&ctx->consoleBuffer, XSize);
}

void menuDrawBattleScreen(Context *ctx) {
    uint8 i, j;
    uint8 x = (xBound-1)/2-3, y = 1;

    // Draw lines
    menuDrawWindow(0, 0, XSize, YSize);
    menuDrawTeeLine(XSize, yBound);
    // Separator line
    cvlinexy(xBound, 1, YSize-2);
    cputcxy(xBound, 0, 178);
    cputcxy(xBound, yBound, 219);
    cputcxy(xBound, YSize-1, 177);

    // Draw player information
    menuDrawPlayerInfo(ctx);
    // Draw walls
    menuDrawLeftSector(ctx);
    menuDrawRightSector(ctx);
    menuDrawCenterSector(ctx);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            cputcxy(x+j, y+i, (*ctx->enemy.head)[i][j]);
            cputcxy(x+j, yBound-8+i, (*ctx->enemy.body)[i][j]);
        }
    }

    for (i = 0; i < 5; i++) {
        cputcxy(xBound+1, yBound+1+i, CHAR_BLANK);
    }

    cputsxy(xBound+3, yBound+1, locale[ctx->locale][LC_COMBAT_ATTACK_BUTTION]);
    cputsxy(xBound+3, yBound+2, locale[ctx->locale][LC_COMBAT_DEFEND_BUTTON]);
    cputsxy(xBound+3, yBound+3, locale[ctx->locale][LC_COMBAT_INSPECT_BUTTON]);
    cputsxy(xBound+3, yBound+4, locale[ctx->locale][LC_COMBAT_ITEM_BUTTON]);
    cputsxy(xBound+3, yBound+5, locale[ctx->locale][LC_COMBAT_RUN_BUTTON]);

    cputcxy(xBound+1, yBound+1+ctx->choice, 218);

    // Display console
    consoleWrite(&ctx->consoleBuffer, xBound);
}

void menuDrawMap(Context *ctx) {
    uint8 i, j;
    uint8 x = 4, y = 1;
    uint8 width = 22, height = 22;

    menuDrawWindow(x, y, width, height);
    cputsxy(x+1, y, locale[ctx->locale][LC_MAP_WINDOW_LABEL]);

    for (i = 0; i < MAZE_HEIGHT; i++) {
        for (j = 0; j < MAZE_WIDTH; j++) {
            if (mazeGetPos(&ctx->maze, i, j)) {
                cputcxy(x+i+1, y+j+1, 166);
            } else {
                cputcxy(x+i+1, y+j+1, 32);
            }
        }
    }

    textcolor(COLOR_RED);
    cputcxy(x+ctx->player.position.x+1, y+ctx->player.position.y+1, '@');
    textcolor(COLOR_WHITE);   
}

void menuDrawPlayerStats(Context *ctx) {
    uint8 i, j;
    uint8 width = 24, height = 19;
    uint8 x = XSize/2-width/2, y = YSize/2-height/2;
    uint8 flavor = LC_PLAYER_INFO_FLAVOR1 + rand() % 5;

    menuDrawWindow(x, y, width, height);
    cputsxy(x+1, y, locale[ctx->locale][LC_SIDEBAR_STAT_LABEL]);

    for (i = 0; i < width-2; i++) {
        for (j = 0; j < height-2; j++) {
            cputcxy(x+i+1, y+j+1, 32);
        }
    }

    cputsxy(x+1, y+2, ctx->player.name);
    gotoxy(x+2, y+4);
    cprintf(locale[ctx->locale][LC_STAT_FULL_LEVEL], ctx->player.stats.level);
    gotoxy(x+2, y+5);
    cprintf(locale[ctx->locale][LC_STAT_FULL_HP], ctx->player.stats.health.health, ctx->player.stats.health.maxHealth);

    // Stats
    gotoxy(x+3, y+7);
    cprintf(locale[ctx->locale][LC_STAT_FULL_ATK], ctx->player.stats.attack);
    gotoxy(x+3, y+8);
    cprintf(locale[ctx->locale][LC_STAT_FULL_DEF], ctx->player.stats.defense);
    gotoxy(x+3, y+9);
    cprintf(locale[ctx->locale][LC_STAT_FULL_SPD], ctx->player.stats.speed);
    gotoxy(x+3, y+10);
    cprintf(locale[ctx->locale][LC_STAT_FULL_LCK], ctx->player.stats.luck);

    gotoxy(x+2, y+12);
    cprintf(locale[ctx->locale][LC_STAT_FULL_EXP], ctx->player.stats.experience, XP_FACTOR * ctx->player.stats.level + 1);
    gotoxy(x+2, y+13);
    cprintf(locale[ctx->locale][LC_SCORE_FULL], ctx->player.score);

    for (i = 0; i < strlen(locale[ctx->locale][flavor]); i++) {
        if (x > width+(XSize/2-width/2)-2 || getNextWordLen(locale[ctx->locale][flavor], i) + x > width+(XSize/2-width/2)-2) {
            x = XSize/2-width/2;
            y++;
        }
        if (locale[ctx->locale][flavor][i] != ' ' && x != width+(XSize/2-width/2)-2) {
            cputcxy(x+1, y+15, locale[ctx->locale][flavor][i]);
        }
        x++;
    }
}

void menuDrawEnemyStats(Context *ctx) {
    uint8 i, j;
    uint8 width = 24, height = 18;
    uint8 x = XSize/2-width/2, y = YSize/2-height/2;
    uint8 flavor = LC_ENEMY_INFO_FLAVOR1+ rand() % 5;
    uint8 statOffset = 0;
    char *name;

    menuDrawWindow(x, y, width, height);
    cputsxy(x+1, y, locale[ctx->locale][LC_SIDEBAR_STAT_LABEL]);

    for (i = 0; i < width-2; i++) {
        for (j = 0; j < height-2; j++) {
            cputcxy(x+i+1, y+j+1, 32);
        }
    }

    gotoxy(x+1, y+2);
    // Bit of a hacky workaround, but saves on a bit of time complexity
    if (width - 2 < (strlen(locale[ctx->locale][LC_ENEMY_ADJECTIVE_1 + ctx->enemy.adjective]) + strlen(locale[ctx->locale][LC_ENEMY_BODY_1 + ctx->enemy.bodyName]) + strlen(locale[ctx->locale][LC_ENEMY_HEAD_1 + ctx->enemy.headName]) + 2)) {
        cprintf("%s %s", locale[ctx->locale][LC_ENEMY_ADJECTIVE_1 + ctx->enemy.adjective], locale[ctx->locale][LC_ENEMY_BODY_1 + ctx->enemy.bodyName]);
        gotoxy(x+1, y+3);
        cprintf("%s", locale[ctx->locale][LC_ENEMY_HEAD_1 + ctx->enemy.headName]);
        statOffset = 1;
    } else {
        cprintf("%s %s %s", locale[ctx->locale][LC_ENEMY_ADJECTIVE_1 + ctx->enemy.adjective], locale[ctx->locale][LC_ENEMY_BODY_1 + ctx->enemy.bodyName], locale[ctx->locale][LC_ENEMY_HEAD_1 + ctx->enemy.headName]);
    }


    gotoxy(x+2, y+4+statOffset);
    cprintf(locale[ctx->locale][LC_STAT_FULL_LEVEL], ctx->enemy.stats.level);
    gotoxy(x+2, y+5+statOffset);
    cprintf(locale[ctx->locale][LC_STAT_FULL_HP], ctx->enemy.stats.health.health, ctx->enemy.stats.health.maxHealth);

    // Stats
    gotoxy(x+3, y+7+statOffset);
    cprintf(locale[ctx->locale][LC_STAT_FULL_ATK], ctx->enemy.stats.attack);
    gotoxy(x+3, y+8+statOffset);
    cprintf(locale[ctx->locale][LC_STAT_FULL_DEF], ctx->enemy.stats.defense);
    gotoxy(x+3, y+9+statOffset);
    cprintf(locale[ctx->locale][LC_STAT_FULL_SPD], ctx->enemy.stats.speed);
    gotoxy(x+3, y+10+statOffset);
    cprintf(locale[ctx->locale][LC_STAT_FULL_LCK], ctx->enemy.stats.luck);

    for (i = 0; i < strlen(locale[ctx->locale][flavor]); i++) {
        if (x > width+(XSize/2-width/2)-1 || getNextWordLen(locale[ctx->locale][flavor], i) + x > width+(XSize/2-width/2)-2) {
            x = XSize/2-width/2;
            y++;
        }
        if (locale[ctx->locale][flavor][i] != ' ' && x != width+(XSize/2-width/2)-2) {
            cputcxy(x+1, y+13, locale[ctx->locale][flavor][i]);
        }
        x++;
    }
}

void menuDrawHelp(Context *ctx) {
    uint8 i, j;
    uint8 x = 4, y = 1;
    uint8 width = 22, height = 22;

    menuDrawWindow(x, y, width, height);
    cputsxy(x+1, y, locale[ctx->locale][LC_HELP_WINDOW_LABEL]);

    for (i = 0; i < width-2; i++) {
        for (j = 0; j < height-2; j++) {
            cputcxy(x+i+1, y+j+1, 32);
        }
    }

    cputsxy(x+1, y+1, "pekora");
}

void menuDrawLevelUp(Context *ctx, Stats *lvlStats) {
    uint8 i, j;
    uint8 x = 8, y = 6;
    uint8 width = 24, height = 14;

    menuDrawWindow(x, y, width, height);
    cputsxy(x+1, y, locale[ctx->locale][LC_LEVEL_UP_WINDOW_LABEL]);

    for (i = 0; i < width-2; i++) {
        for (j = 0; j < height-2; j++) {
            cputcxy(x+i+1, y+j+1, 32);
        }
    }

    gotoxy(x+1, y+2);
    cprintf(locale[ctx->locale][LC_COMBAT_LEVEL_UP], ctx->player.stats.level);

    // Stats
    gotoxy(x+2, y+5);
    cprintf(locale[ctx->locale][LC_STAT_FULL_ATK], ctx->player.stats.attack-lvlStats->attack); 
    gotoxy(x+13, y+5);
    textcolor(COLOR_GREEN);
    cprintf("+%d", lvlStats->attack);
    textcolor(COLOR_WHITE);

    gotoxy(x+2, y+6);
    cprintf(locale[ctx->locale][LC_STAT_FULL_DEF], ctx->player.stats.defense-lvlStats->defense);
    gotoxy(x+13, y+6);
    textcolor(COLOR_GREEN);
    cprintf("+%d", lvlStats->defense);
    textcolor(COLOR_WHITE);

    gotoxy(x+2, y+7);
    cprintf(locale[ctx->locale][LC_STAT_FULL_SPD], ctx->player.stats.speed-lvlStats->speed);
    gotoxy(x+13, y+7);
    textcolor(COLOR_GREEN);
    cprintf("+%d", lvlStats->speed);
    textcolor(COLOR_WHITE);

    gotoxy(x+2, y+8);
    cprintf(locale[ctx->locale][LC_STAT_FULL_LCK], ctx->player.stats.luck-lvlStats->luck);
    gotoxy(x+13, y+8);
    textcolor(COLOR_GREEN);
    cprintf("+%d", lvlStats->luck);
    textcolor(COLOR_WHITE);

    gotoxy(x+2, y+11);
    cprintf(locale[ctx->locale][LC_STAT_FULL_EXP], ctx->player.stats.experience, XP_FACTOR * ctx->player.stats.level + 1);


}

void menuDrawInventory(Context *ctx) {
    uint8 i, j;
    uint8 x = 4, y = 1;
    uint8 width = 20, height = 22;

    menuDrawWindow(x, y, width, height);
    cputsxy(x+1, y, locale[ctx->locale][LC_INVENTORY_WINDOW_LABEL]);

    for (i = 0; i < width-2; i++) {
        for (j = 0; j < height-2; j++) {
            cputcxy(x+i+1, y+j+1, 32);
        }
    }
    

    for (i = 0; i < INVENTORY_SIZE+1; i++) {
        cputsxy(x+4, y+2+i, locale[ctx->locale][LC_POTION_HEALTH+ctx->player.items[i].modifier]);
    }
}

void menuClearViewport() {
    uint8 x = 1, y = 2;
    size_t i, j;

    for (i = 0; i < 3; i++) {
        
        for (j = 0; j < 4; j++) {
            // clear top and bottom horizontal lines
            cputcxy(xBound-x-j-(4*i), y+i, CHAR_BLANK);
            cputcxy(xBound-x-j-(4*i), y+(yBound-4)-i, CHAR_BLANK);
            cputcxy(x+j+(4*i), y+i, CHAR_BLANK);
            cputcxy(x+j+(4*i), y+(yBound-4)-i, CHAR_BLANK);

            // clear immediate adjacent section
            cputcxy(xBound-(4*i)-j-1, y+i+1, CHAR_BLANK);
            cputcxy(xBound-(4*i)-j-1, y+(yBound-4)-i-1, CHAR_BLANK);
            cputcxy(x+(4*i)+j, y+i+1, CHAR_BLANK);
            cputcxy(x+(4*i)+j, y+(yBound-4)-i-1, CHAR_BLANK);
        }

        // clear vertical line
        for (j = 0; j < 12-(2*i); j++) {
            cputcxy(xBound-4*(i+1), j+i+3, CHAR_BLANK);
            cputcxy(4*(i+1), j+i+3, CHAR_BLANK);
        }
    }
}

void menuClearInfoWindow() {
    size_t x, y;

    for (y = 1; y < yBound-1; y++) {
        for (x = xBound+1; x < XSize-1; x++) {
            cputcxy(x, y, CHAR_BLANK);
        }
    }
}
