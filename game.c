#include "sorcery.h"

#include <conio.h>

void buildContext(Context *ctx) {
    // Build the context
    Player player = {"p"};
    ctx->player = player;

    ctx->gameState = true;
    ctx->quitPrompt = false;
    ctx->showMap = false;

    ctx->quitSelector = 0;
    ctx->choice = 0;
    ctx->input = 0;

    ctx->gameState = TitleScreen;
    //ctx->gameState = Game;
}

void gameLoop() {
    Context ctx;
    buildContext(&ctx);

    while (ctx.gameRunning) {
        draw(&ctx);

        //gotoxy(3,5);
        //cprintf("value of input: %d", ctx.input);
        //gotoxy(3,6);
        //cprintf("value of choice: %d", ctx.choice);
        //gotoxy(3,7);
        //cprintf("current name: %s", ctx.player.name);

        takeInput(&ctx);
    }
    
}

void draw(Context *ctx) {
    if (!ctx->quitPrompt && ctx->gameState != NamePrompt && ctx->gameState != TitleScreen) {
        clrscr();
    }

    switch (ctx->gameState) {
        case TitleScreen:
            menuDrawTitleScreen();
            break;
        case NamePrompt:
            menuDrawNamePrompt();
            break;
        case Game:
            menuDrawGameScreen(ctx);
            break;
    }

    if (ctx->quitPrompt) {
        menuDrawQuitPrompt(ctx->quitSelector);
    }

    if (ctx->showMap) {
        menuDrawMap(ctx);
    }
}

void takeInput(Context *ctx) {
    ctx->input = cgetc();

    // Quit prompt
    if (ctx->quitPrompt) {
        if (ctx->input == KEY_DOWN || ctx->input == KEY_UP) {
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
    if (ctx->input == KEY_RETURN && ctx->gameState == TitleScreen && !ctx->quitPrompt) {
        ctx->gameState = NamePrompt;
        clrscr();
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
        if (ctx->showMap == false && ctx->input == 'm') {
            ctx->showMap = true;
        }
    }
    

    if (ctx->input == 3) {
        ctx->quitPrompt = true;
    }
}