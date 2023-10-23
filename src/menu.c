#include "sorcery.h"
#include "locale.h"

#include <cbm.h>
#include <conio.h>
#include <peekpoke.h>
#include <stdlib.h>
#include <string.h>

extern uint8 XSize, YSize, xBound, yBound;
extern const char* locale[2][LC_NUM_STRINGS];

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
    menuDrawWindow(0, 0, XSize, YSize);
    menuDrawTeeLine(XSize, 20);

    cputsxy((XSize)/2 - strlen(locale[ctx->state.locale][LC_TITLE_PROMPT])/2, YSize - 3, locale[ctx->state.locale][LC_TITLE_PROMPT]);
    gotoxy(1, YSize-1);
    cprintf(locale[ctx->state.locale][LC_TITLE_LANG], ctx->state.locale == English ? "en" : "eo");
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
    cputsxy(x + 1, 10, locale[ctx->state.locale][LC_QUIT_PROMPT1]);
    cputsxy(x + 1, 11, locale[ctx->state.locale][LC_QUIT_PROMPT2]);

    cputsxy(x + 6, 13, locale[ctx->state.locale][LC_YES]);
    cputsxy(x + 6, 14, locale[ctx->state.locale][LC_NO]);

    ctx->state.quitSelector ? cputcxy(XSize/2 - 4, 14, 218) : cputcxy(XSize/2 - 4, 13, 218);
    ctx->state.quitSelector ? cputcxy(XSize/2 - 4, 13, CHAR_BLANK) : cputcxy(XSize/2 - 4, 14, CHAR_BLANK);
}

void menuDrawNamePrompt(Context *ctx) {
    menuDrawWindow(0, 0, XSize, YSize);
    cputsxy((XSize)/2 - strlen(locale[ctx->state.locale][LC_NAME_PROMPT])/2, YSize/2-1, locale[ctx->state.locale][LC_NAME_PROMPT]);
    cputcxy((XSize)/2 - 5, YSize/2+1, 62);
}

void menuDrawPlayerInfo(Context *ctx) {
    cputsxy(xBound+1, 1, ctx->player.name);
    gotoxy(xBound+1, 2);
    cprintf(locale[ctx->state.locale][LC_STAT_LEVEL], ctx->player.stats.level);
    gotoxy(xBound+1, 3);
    cprintf(locale[ctx->state.locale][LC_STAT_HP], ctx->player.stats.health.health, ctx->player.stats.health.maxHealth);

    // Stats
    cputsxy(xBound+1, 5, locale[ctx->state.locale][LC_SIDEBAR_STAT_LABEL]);
    gotoxy(xBound+1, 6);
    cprintf(locale[ctx->state.locale][LC_STAT_ATK], ctx->player.stats.attack);
    gotoxy(xBound+1, 7);
    cprintf(locale[ctx->state.locale][LC_STAT_DEF], ctx->player.stats.defense);
    gotoxy(xBound+1, 8);
    cprintf(locale[ctx->state.locale][LC_STAT_SPD], ctx->player.stats.speed);
    gotoxy(xBound+1, 9);
    cprintf(locale[ctx->state.locale][LC_STAT_LCK], ctx->player.stats.luck);

    // Location
    cputsxy(xBound+1, 11, locale[ctx->state.locale][LC_SIDEBAR_LOC_LABEL]);
    gotoxy(xBound+1, 12);
    cprintf(locale[ctx->state.locale][LC_SIDEBAR_LOC], ctx->player.position.x, ctx->player.position.y);
    gotoxy(xBound+1, 13);
    cprintf(locale[ctx->state.locale][LC_SIDEBAR_DIR], locale[ctx->state.locale][ctx->player.direction]);

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
            }
            break;
        }

        else if (isWall) {

            // Top horizontal line
            cputcxy(x+(4*i), y+i, 197);
            cputcxy(x+1+(4*i), y+i, 195);
            cputcxy(x+2+(4*i), y+i, 210);
            cputcxy(x+3+(4*i), y+i, 175);

            // Bottom horizontal line
            cputcxy(x+(4*i), y+(yBound-4)-i, 175);
            cputcxy(x+1+(4*i), y+(yBound-4)-i, 210);
            cputcxy(x+2+(4*i), y+(yBound-4)-i, 195);
            cputcxy(x+3+(4*i), y+(yBound-4)-i, 197);

        }
        else {
            for (j = 0; j < 4; j++) {
                cputcxy(x+(4*i)+j, y+i+1, 197);
                cputcxy(x+(4*i)+j, y+(yBound-4)-i-1, 175);
            }
        }

        // Vertical line
        cvlinexy(4*(i+1), 3+i, 12-(2*i));
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
            }
            break;
        }

        else if (isWall) {

            // Top horizontal line
            cputcxy(x-(4*i), y+i, 197);
            cputcxy(x-1-(4*i), y+i, 195);
            cputcxy(x-2-(4*i), y+i, 210);
            cputcxy(x-3-(4*i), y+i, 175);

            // Bottom horizontal line
            cputcxy(x-(4*i), y+(yBound-4)-i, 175);
            cputcxy(x-1-(4*i), y+(yBound-4)-i, 210);
            cputcxy(x-2-(4*i), y+(yBound-4)-i, 195);
            cputcxy(x-3-(4*i), y+(yBound-4)-i, 197);

        }
        else {
            for (j = 1; j < 4; j++) {
                cputcxy(xBound-(4*i)-j, y+i+1, 197);
                cputcxy(xBound-(4*i)-j, y+(yBound-4)-i-1, 175);
            }
        }

        // Vertical line
        cvlinexy(xBound-4*(i+1), 3+i, 12-(2*i));
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
            wall = posX+3 >= MAZE_WIDTH-1 ? (mazeGetPos(&ctx->maze, posX+3, posY) && !mazeGetPos(&ctx->maze, posX+2, posY)) : false;
            break;
        case West:
            wall = posX-3 >= 0 ? (mazeGetPos(&ctx->maze, posX-3, posY) && !mazeGetPos(&ctx->maze, posX-2, posY)) : false;
            break;
    }

    if (wall) {
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

    // Display console
    consoleWrite(&ctx->consoleBuffer);

    // Draw walls
    menuDrawLeftSector(ctx);
    menuDrawRightSector(ctx);
    menuDrawCenterSector(ctx);
    
}

void menuDrawMap(Context *ctx) {
    uint8 i, j;
    uint8 x = 4, y = 1;
    uint8 width = 22, height = 22;

    menuDrawWindow(x, y, width, height);
    cputsxy(x+1, y, locale[ctx->state.locale][LC_MAP_WINDOW_LABEL]);

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

void menuClearLeftWallSegment(uint8 section) {
    uint8 x = 1, y = 2;
    size_t i;

    // clear top and bottom horizontal lines
    for (i = 0; i < 4; i++) {
        cputcxy(x+i+(4*section), y+section, CHAR_BLANK);
        cputcxy(x+i+(4*section), y+(yBound-4)-section, CHAR_BLANK);
    }

    // clear immediate adjacent section
    for (i = 0; i < 4; i++) {
        cputcxy(x+(4*section)+i, y+section+1, CHAR_BLANK);
        cputcxy(x+(4*section)+i, y+(yBound-4)-section-1, CHAR_BLANK);
    }

    // clear vertical line
    for (i = 0; i < 12-(2*section); i++) {
        cputcxy(4*(section+1), i+section+3, CHAR_BLANK);
    }
}

void menuClearRightWallSegment(uint8 section) {
    uint8 x = xBound-1, y = 2;
    size_t i;

    // clear top and bottom horizontal lines
    for (i = 0; i < 4; i++) {
        cputcxy(x-i-(4*section), y+section, CHAR_BLANK);
        cputcxy(x-i-(4*section), y+(yBound-4)-section, CHAR_BLANK);
    }

    // clear immediate adjacent section
    for (i = 1; i < 4; i++) {
        cputcxy(xBound-(4*section)-i, y+section+1, CHAR_BLANK);
        cputcxy(xBound-(4*section)-i, y+(yBound-4)-section-1, CHAR_BLANK);
    }

    // clear vertical line
    for (i = 0; i < 12-(2*section); i++) {
        cputcxy(xBound-4*(section+1), i+section+3, CHAR_BLANK);
    }
}