#include "sorcery.h"
#include "locale.h"

#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void gameLoop() {
    Context ctx;
    contextBuild(&ctx);

    while (ctx.gameRunning) {
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
            case Battle:
                menuDrawBattleScreen(ctx);
                break;
        }
    }
}

void takeInput(Context *ctx) {
    uint8 x, y;
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
    switch (ctx->gameState) {
        case TitleScreen:
            if (ctx->input == KEY_RETURN) {
                ctx->gameState = NamePrompt;
                clrscr();
            }
            else if (ctx->input == KEY_L) {
                ctx->locale = ctx->locale == English ? Esperanto : English;
                clrscr();
            }
            break;
        
        case NamePrompt:
            x = (XSize)/2 - 4, y = YSize/2+1;

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
                consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_MAZE_ENTRY_MESSAGE]);
                ctx->gameState = Game;
                clrscr();
            }
            break;
        
        case Game:
            if (ctx->input == 'm') {
                // we unforunately have to call draws to pop-up windows here to prevent expensive re-drawing
                menuDrawMap(ctx);
                ctx->input = 0;
                while (ctx->input != 'm' && ctx->input != KEY_RETURN && ctx->input != 3) {
                    ctx->input = cgetc();
                }
            }
            else if (ctx->input == '?') {
                menuDrawHelp(ctx);
                ctx->input = 0;
                while (ctx->input != '?' && ctx->input != KEY_RETURN && ctx->input != 3) {
                    ctx->input = cgetc();
                }
            }
            else if (ctx->input == 'p') {
                menuDrawPlayerStats(ctx);
                ctx->input = 0;
                while (ctx->input != 'p' && ctx->input != KEY_RETURN && ctx->input != 3) {
                    ctx->input = cgetc();
                }
            }
            else if (ctx->input == 'b') {
                char *message;
                enemyBuild(&ctx->enemy, ctx->player.stats.level);
                message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ENEMY_ENCOUNTER_TEXT]) + strlen(locale[ctx->locale][LC_ENEMY_ADJECTIVE_1 + ctx->enemy.adjective]) + strlen(locale[ctx->locale][LC_ENEMY_HEAD_1 + ctx->enemy.headName]) + strlen(locale[ctx->locale][LC_ENEMY_BODY_1 + ctx->enemy.bodyName]) - 2));
                sprintf(message, locale[ctx->locale][LC_ENEMY_ENCOUNTER_TEXT], locale[ctx->locale][LC_ENEMY_ADJECTIVE_1 + ctx->enemy.adjective], locale[ctx->locale][LC_ENEMY_BODY_1 + ctx->enemy.bodyName], locale[ctx->locale][LC_ENEMY_HEAD_1 + ctx->enemy.headName]);

                consoleBufferAdd(&ctx->consoleBuffer, message);
                free(message);

                ctx->gameState = Battle;
                ctx->choice = 0;
                clrscr();
            }
            else if (UP_PRESSED(ctx->input)) {
                if (playerAttemptMove(&ctx->player, &ctx->maze, Forward)) {
                    // I am so sorry
                    char *message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ADVANCE_MESSAGE]) + strlen(locale[ctx->locale][ctx->player.direction+4])-1));

                    sprintf(message, locale[ctx->locale][LC_ADVANCE_MESSAGE], locale[ctx->locale][ctx->player.direction+4]);
                    consoleBufferAdd(&ctx->consoleBuffer, message);
                    free(message);
                } else {
                    consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_MOVE_FAIL_MESSAGE]);
                }
            }
            else if (DOWN_PRESSED(ctx->input)) {
                if (playerAttemptMove(&ctx->player, &ctx->maze, Backward)) {
                    // I am still sorry, but not as sorry since i'm doing this line now
                    uint8 dir = ctx->player.direction == North ? LC_SOUTH : ctx->player.direction == East ? LC_WEST : ctx->player.direction == South ? LC_NORTH : LC_EAST;  
                    char *message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ADVANCE_MESSAGE]) + strlen(locale[ctx->locale][dir])-1));

                    sprintf(message, locale[ctx->locale][LC_RETREAT_MESSAGE], locale[ctx->locale][dir]);
                    consoleBufferAdd(&ctx->consoleBuffer, message);
                    free(message);
                } else {
                    consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_MOVE_FAIL_MESSAGE]);
                }
            }
            else if (LEFT_PRESSED(ctx->input)) {
                char *message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_TURN_MESSAGE]) + strlen(locale[ctx->locale][LC_LEFT])-1));

                playerMakeTurn(&ctx->player, Left);
                
                sprintf(message, locale[ctx->locale][LC_TURN_MESSAGE], locale[ctx->locale][LC_LEFT]);
                consoleBufferAdd(&ctx->consoleBuffer, message);
                free(message);
            }
            else if (RIGHT_PRESSED(ctx->input)) {
                char *message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_TURN_MESSAGE]) + strlen(locale[ctx->locale][LC_RIGHT])-1));

                playerMakeTurn(&ctx->player, Right);

                sprintf(message, locale[ctx->locale][LC_TURN_MESSAGE], locale[ctx->locale][LC_RIGHT]);
                consoleBufferAdd(&ctx->consoleBuffer, message);
                free(message);
            }
            break;

        case Battle:
            if (UP_PRESSED(ctx->input)) {
                //advance choice up to 3 then wrap around
                ctx->choice = ctx->choice-1 < 0 ? 4 : ctx->choice-1;
            }
            else if (DOWN_PRESSED(ctx->input)) {
                ctx->choice = ctx->choice+1 > 4 ? 0 : ctx->choice+1;
            }
            else if (ctx->input == KEY_RETURN) {
                if (ctx->choice == 0) {
                    consoleBufferAdd(&ctx->consoleBuffer, "you attack the ghost sock!");
                }
                else if (ctx->choice == 1) {
                    consoleBufferAdd(&ctx->consoleBuffer, "you defend against the ghost sock!");
                }
                else if (ctx->choice == 2) {
                    consoleBufferAdd(&ctx->consoleBuffer, "you inspect the creature");
                }
                else if (ctx->choice == 3) {
                    consoleBufferAdd(&ctx->consoleBuffer, "you use an item!");
                }
                else if (ctx->choice == 4) {
                    consoleBufferAdd(&ctx->consoleBuffer, "you flee!");
                    ctx->gameState = Game;
                }
                clrscr();
            }
            break;

        default:
            break;
    }

    if (ctx->input == 3) {
        ctx->quitSelector = 0;
        ctx->quitPrompt = true;
    }

    else if (ctx->input == 'q') {
        ctx->locale = ctx->locale == English ? Esperanto : English;
        clrscr();
    }
}