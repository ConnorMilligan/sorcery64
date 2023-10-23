#include "sorcery.h"
#include "locale.h"

#include <conio.h>

void gameLoop() {
    Context ctx;
    contextBuild(&ctx);

    while (ctx.state.gameRunning) {
        consoleBufferAdd(&ctx.consoleBuffer, "this is a test string that should be wrapped around the screen");
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


    if (ctx->state.quitPrompt) {
        menuDrawQuitPrompt(ctx);
    } else {

    switch (ctx->state.gameState) {
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

    if (ctx->state.showMap) {
        menuDrawMap(ctx);
    }}
}

void takeInput(Context *ctx) {
    ctx->state.input = cgetc();

    // Quit prompt
    if (ctx->state.quitPrompt) {
        if (UP_PRESSED(ctx->state.input) || DOWN_PRESSED(ctx->state.input)) {
            ctx->state.quitSelector = ctx->state.quitSelector ? 0 : 1;
        } 
        else if (ctx->state.input == KEY_RETURN) {
            if (ctx->state.quitSelector == 0) {
                ctx->state.gameRunning = false;
            }
            else {
                ctx->state.quitPrompt = false;
                clrscr();
            }
        }
        ctx->state.input = 0;
    }

    // Title Screen prompts
    else if (ctx->state.gameState == TitleScreen && !ctx->state.quitPrompt) {
        if (ctx->state.input == KEY_RETURN) {
            ctx->state.gameState = NamePrompt;
            clrscr();
        }
        else if (ctx->state.input == KEY_L) {
            ctx->state.locale = ctx->state.locale == English ? Esperanto : English;
            clrscr();
        }
    }

    // Name prompt
    else if (ctx->state.gameState == NamePrompt) {
        uint8 x = (XSize)/2 - 4, y = YSize/2+1;

        if (ctx->state.input != KEY_RETURN && ctx->state.input != KEY_BACKSPACE) {
            if (ctx->state.choice+1 != 9) {
                ctx->player.name[ctx->state.choice] = ctx->state.input;
                cputcxy(x + ctx->state.choice, y, ctx->state.input);
                ctx->state.choice+=1;
            }
        } 
        else if (ctx->state.input == KEY_BACKSPACE) {
            if (ctx->state.choice != 0) {
                ctx->state.choice-=1;
                ctx->player.name[ctx->state.choice] = ' ';
                cputcxy(x + ctx->state.choice, y, CHAR_BLANK);
            }
        }
        else if (ctx->state.input == KEY_RETURN) {
            ctx->state.gameState = Game;
            clrscr();
        }
    }
    
    // Game
    else if (ctx->state.gameState == Game) {
        if (ctx->state.input == 'm') {
            ctx->state.showMap = ctx->state.showMap ? false : true;
            clrscr();
        } 
        else if (UP_PRESSED(ctx->state.input)) {
            playerAttemptMove(&ctx->player, &ctx->maze, Forward);
        }
        else if (DOWN_PRESSED(ctx->state.input)) {
            playerAttemptMove(&ctx->player, &ctx->maze, Backward);
        }
        else if (LEFT_PRESSED(ctx->state.input)) {
            playerMakeTurn(&ctx->player, Left);
        }
        else if (RIGHT_PRESSED(ctx->state.input)) {
            playerMakeTurn(&ctx->player, Right);
        }
        
    }
    

    if (ctx->state.input == 3) {
        ctx->state.quitSelector = 0;
        ctx->state.quitPrompt = true;
    }

    else if (ctx->state.input == 80) {
        ctx->state.locale = ctx->state.locale == English ? Esperanto : English;
        clrscr();
    }
}