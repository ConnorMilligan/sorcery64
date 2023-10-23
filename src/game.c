#include "sorcery.h"
#include "locale.h"

#include <conio.h>

void gameLoop() {
    Context ctx;
    contextBuild(&ctx);

    while (ctx.gameRunning) {
        consoleBufferAdd(&ctx.consoleBuffer, "this is a very long string that should have some issue with text wrapping around i hope");
        draw(&ctx);

        // gotoxy(3,5);
        // cprintf("value of input: %d", ctx.input);
        // gotoxy(3,6);
        // cprintf("value of choice: %d", ctx.choice);
        // gotoxy(3,7);
        // cprintf("current name: %s", ctx.player.name);

        takeInput(&ctx);
    }
    
    contextCleanUp(&ctx);
}

void draw(Context *ctx) {


    if (ctx->quitPrompt) {
        menuDrawQuitPrompt(ctx);
    } else {

    switch (ctx->gameState) {
        case TitleScreen:
            menuDrawTitleScreen(ctx);
            break;
        case NamePrompt:
            menuDrawNamePrompt(ctx);
            break;
        case Game:
            menuDrawGameScreen(ctx);
            break;
    }

    if (ctx->showMap) {
        menuDrawMap(ctx);
    }}
}

void takeInput(Context *ctx) {
    ctx->input = cgetc();

    // Quit prompt
    if (ctx->quitPrompt) {
        if (UP_PRESSED(ctx->input) || DOWN_PRESSED(ctx->input)) {
            ctx->quitSelector = ctx->quitSelector ? 0 : 1;
        } 
        else if (ctx->input == KEY_RETURN) {
            if (ctx->quitSelector == 0) {
                ctx->gameRunning = false;
            }
            else {
                ctx->quitPrompt = false;
                clrscr();
            }
        }
        ctx->input = 0;
    }

    // Title Screen prompts
    else if (ctx->gameState == TitleScreen && !ctx->quitPrompt) {
        if (ctx->input == KEY_RETURN) {
            ctx->gameState = NamePrompt;
            clrscr();
        }
        else if (ctx->input == KEY_L) {
            ctx->locale = ctx->locale == English ? Esperanto : English;
            clrscr();
        }
    }

    // Name prompt
    else if (ctx->gameState == NamePrompt) {
        uint8 x = (XSize)/2 - 4, y = YSize/2+1;

        if (ctx->input != KEY_RETURN && ctx->input != KEY_BACKSPACE) {
            if (ctx->choice+1 != 9) {
                ctx->player.name[ctx->choice] = ctx->input;
                cputcxy(x + ctx->choice, y, ctx->input);
                ctx->choice+=1;
            }
        } 
        else if (ctx->input == KEY_BACKSPACE) {
            if (ctx->choice != 0) {
                ctx->choice-=1;
                ctx->player.name[ctx->choice] = ' ';
                cputcxy(x + ctx->choice, y, CHAR_BLANK);
            }
        }
        else if (ctx->input == KEY_RETURN) {
            ctx->gameState = Game;
            clrscr();
        }
    }
    
    // Game
    else if (ctx->gameState == Game) {
        if (ctx->input == 'm') {
            ctx->showMap = ctx->showMap ? false : true;
            clrscr();
        } 
        else if (UP_PRESSED(ctx->input)) {
            playerAttemptMove(&ctx->player, &ctx->maze, Forward);
        }
        else if (DOWN_PRESSED(ctx->input)) {
            playerAttemptMove(&ctx->player, &ctx->maze, Backward);
        }
        else if (LEFT_PRESSED(ctx->input)) {
            playerMakeTurn(&ctx->player, Left);
        }
        else if (RIGHT_PRESSED(ctx->input)) {
            playerMakeTurn(&ctx->player, Right);
        }
        
    }
    

    if (ctx->input == 3) {
        ctx->quitSelector = 0;
        ctx->quitPrompt = true;
    }

    else if (ctx->input == 80) {
        ctx->locale = ctx->locale == English ? Esperanto : English;
        clrscr();
    }
}