#include "sorcery.h"
#include "locale.h"

#include <cbm.h>
#include <conio.h>
#include <peekpoke.h>
#include <stdlib.h>
#include <string.h>

extern uint8 XSize, YSize, xBound, yBound;
extern const char* locale[2][LC_NUM_STRINGS];

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

}

void menuDrawLeftSector(bool hasWall) {
    uint8 x = 1, y = 2;
    size_t i;

    // Draw vertical lines
    cvlinexy(4, 3, 12);
    cvlinexy(8, 4, 10);


    // Horizontal lines top left
    for (i = 0; i < 2; i++) {
        cputcxy(x, y, 197);
        cputcxy(x+1, y, 195);
        cputcxy(x+2, y, 210);
        cputcxy(x+3, y, 175);
        y++;
        x+=4;
    }
    
    // Horizontal lines bottom left
    x = 1;
    y = yBound-2;

    for (i = 0; i < 2; i++) {
        cputcxy(x, y, 175);
        cputcxy(x+1, y, 210);
        cputcxy(x+2, y, 195);
        cputcxy(x+3, y, 197);
        y--;
        x+=4;
    }
}

void menuDrawRightSector(bool hasWall) {
    uint8 x = xBound-8, y = 3;
    size_t i;

    // Draw vertical lines
    cvlinexy(xBound-4, 3, 12);
    cvlinexy(xBound-8, 4, 10);

    // Horizontal lines top right
    for (i = 0; i < 2; i++) {
        cputcxy(x, y, 175);
        cputcxy(x+1, y, 210);
        cputcxy(x+2, y, 195);
        cputcxy(x+3, y, 197);
        y--;
        x+=4;
    }

    // Horizontal lines bottom right
    x = xBound-8;
    y = yBound-3;

    for (i = 0; i < 2; i++) {
        cputcxy(x, y, 197);
        cputcxy(x+1, y, 195);
        cputcxy(x+2, y, 210);
        cputcxy(x+3, y, 175);
        y++;
        x+=4;
    }
}

void menuDrawCenterSector(bool hasWall) {
    size_t i;
    uint8 x = 9, y = 3;

    for (i = 0; i < 12; i++) {
        cputcxy(x+i, y, 175);
        cputcxy(x+i, y+11, 197);
    }

}

void menuDrawGameScreen(Context *ctx) {
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
    menuDrawLeftSector(1);
    menuDrawRightSector(1);
    menuDrawCenterSector(1);
    
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