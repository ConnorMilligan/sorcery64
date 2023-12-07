#include "sorcery.h"
#include "locale.h"

#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

bool debugMode = false;

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
            case DeathScreen:
                menuDrawDeathScreen(ctx);
                break;
        }
    }

    if (debugMode) {
        textcolor(COLOR_RED);
        cputsxy(1, 0, "debug");
        textcolor(COLOR_WHITE);
    }
}

void takeInput(Context *ctx) {
    uint8 x, y;
    Stats lvlStats;
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
            while (ctx->input != KEY_L && ctx->input != KEY_RETURN && ctx->input != 3 && ctx->input != 'd') {
                ctx->input = cgetc();
            }

            if (ctx->input == KEY_RETURN) {
                ctx->gameState = NamePrompt;
                clrscr();
            }
            // change locale
            else if (ctx->input == KEY_L) {
                ctx->locale = ctx->locale == English ? Esperanto : English;
                clrscr();
            }
            // enter debug mode
            else if (ctx->input == 'd') {
                debugMode = true;
                strcpy(ctx->player.name, "debug");
                ctx->gameState = Game;
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
            // open the map
            if (ctx->input == 'm') {
                // we unfortunately have to call draws to pop-up windows here to prevent expensive re-drawing
                menuDrawMap(ctx);
                ctx->input = 0;
                while (ctx->input != 'm' && ctx->input != KEY_RETURN && ctx->input != 3) {
                    ctx->input = cgetc();
                }
            }
            // open help
            else if (ctx->input == '?') {
                menuDrawHelp(ctx);
                ctx->input = 0;
                while (ctx->input != '?' && ctx->input != KEY_RETURN && ctx->input != 3) {
                    ctx->input = cgetc();
                }
            }
            // add a potion (DEBUG)
            else if (debugMode && ctx->input == 'o') {
                playerAddItem(ctx);
            }
            // show char sheet
            else if (ctx->input == 'p') {
                menuDrawPlayerStats(ctx);
                ctx->input = 0;
                while (ctx->input != 'p' && ctx->input != KEY_RETURN && ctx->input != 3) {
                    ctx->input = cgetc();
                }
            }
            // show inventory
            else if (ctx->input == 'i') {
                int8 itemSelection = 0, itemOption = 3;

                ctx->input = 0;
                menuDrawInventory(ctx, itemSelection, true);

                while (ctx->input != 'i' && ctx->input != 3) {
                    menuDrawInventory(ctx, itemSelection, false);
                    ctx->input = cgetc();
                    if (UP_PRESSED(ctx->input)) {
                        itemSelection = itemSelection - 1 < 0 ? ctx->player.inventorySize-1 : itemSelection - 1;
                    } else if (DOWN_PRESSED(ctx->input)) {
                        itemSelection = itemSelection + 1 > ctx->player.inventorySize-1 ? 0 : itemSelection + 1;
                    } else if (ctx->input == KEY_RETURN && ctx->player.inventorySize > 0) {
                        itemOption = 0;
                        menuDrawInventorySelection(ctx, itemOption, true);
                    }

                    while (itemOption != 3) {
                        menuDrawInventorySelection(ctx, itemOption, false);
                        ctx->input = cgetc();
                        if (UP_PRESSED(ctx->input) || DOWN_PRESSED(ctx->input)) {
                            itemOption = itemOption ? 0 : 1;
                        }
                        else if (ctx->input == 'i' || ctx->input == 3) {
                            itemOption = 3;
                        }
                        else if (ctx->input == KEY_RETURN) {
                            if (itemOption == 0) {
                                Item item;
                                char *message;
                                
                                playerUseItem(ctx, itemSelection, &item);
                                clrscr();
                                draw(ctx);
                                musicDrinkPotion();
                                sleep(1);

                                message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ITEM_USE]) + strlen(locale[ctx->locale][LC_POTION_HEALTH + item.stat]) + 1));
                                sprintf(message, locale[ctx->locale][LC_ITEM_EFFECT], locale[ctx->locale][LC_POTION_HEALTH + item.stat], item.modifier);
                                consoleBufferAdd(&ctx->consoleBuffer, message);
                                free(message);

                            }
                            else if (itemOption == 1) {
                                playerDropItem(ctx, itemSelection);
                            }
                            itemOption = 3;
                            ctx->input = 'i';
                        }
                    }
                }
            }
            // enter battle mode (DEBUG)
            else if (debugMode && ctx->input == 'b') {
                char *message;
                enemyBuild(&ctx->enemy, ctx->player.stats.level);
                message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ENEMY_ENCOUNTER_TEXT]) + 
                                                 strlen(locale[ctx->locale][LC_ENEMY_ADJECTIVE_1 + ctx->enemy.adjective]) + 
                                                 strlen(locale[ctx->locale][LC_ENEMY_HEAD_1 + ctx->enemy.headName]) + 
                                                 strlen(locale[ctx->locale][LC_ENEMY_BODY_1 + ctx->enemy.bodyName]) - 2));

                sprintf(message, locale[ctx->locale][LC_ENEMY_ENCOUNTER_TEXT], locale[ctx->locale][LC_ENEMY_ADJECTIVE_1 + ctx->enemy.adjective], locale[ctx->locale][LC_ENEMY_BODY_1 + ctx->enemy.bodyName], locale[ctx->locale][LC_ENEMY_HEAD_1 + ctx->enemy.headName]);

                consoleBufferAdd(&ctx->consoleBuffer, message);
                free(message);

                ctx->gameState = Battle;
                ctx->choice = 0;
                clrscr();
            }
            // move forward
            else if (UP_PRESSED(ctx->input)) {
                if (playerAttemptMove(&ctx->player, &ctx->maze, Forward)) {
                    uint8 event = rand() % 10;
                    char *message;

                    // 10% chance of enemy encounter
                    // 10% chance of item encounter
                    // 80% chance of normal movement
                    if (event == 0) {
                        enemyBuild(&ctx->enemy, ctx->player.stats.level);
                        message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ENEMY_ENCOUNTER_TEXT]) + 
                                                         strlen(locale[ctx->locale][LC_ENEMY_ADJECTIVE_1 + ctx->enemy.adjective]) + 
                                                         strlen(locale[ctx->locale][LC_ENEMY_HEAD_1 + ctx->enemy.headName]) + 
                                                         strlen(locale[ctx->locale][LC_ENEMY_BODY_1 + ctx->enemy.bodyName]) - 2));

                        sprintf(message, locale[ctx->locale][LC_ENEMY_ENCOUNTER_TEXT], locale[ctx->locale][LC_ENEMY_ADJECTIVE_1 + ctx->enemy.adjective], locale[ctx->locale][LC_ENEMY_BODY_1 + ctx->enemy.bodyName], locale[ctx->locale][LC_ENEMY_HEAD_1 + ctx->enemy.headName]);

                        consoleBufferAdd(&ctx->consoleBuffer, message);
                        free(message);

                        ctx->gameState = Battle;
                        ctx->choice = 0;
                        clrscr();
                    }
                    if (event == 1) {
                        playerAddItem(ctx);
                    }
                    else {
                        message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ADVANCE_MESSAGE]) + strlen(locale[ctx->locale][ctx->player.direction+4])-1));

                        sprintf(message, locale[ctx->locale][LC_ADVANCE_MESSAGE], locale[ctx->locale][ctx->player.direction+4]);
                        consoleBufferAdd(&ctx->consoleBuffer, message);
                        free(message);

                        ctx->player.score += 10;
                    }
                } else {
                    consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_MOVE_FAIL_MESSAGE]);
                }
            }
            // move backwards
            else if (DOWN_PRESSED(ctx->input)) {
                if (playerAttemptMove(&ctx->player, &ctx->maze, Backward)) {
                    uint8 dir = ctx->player.direction == North ? LC_SOUTH : ctx->player.direction == East ? LC_WEST : ctx->player.direction == South ? LC_NORTH : LC_EAST;  
                    char *message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ADVANCE_MESSAGE]) + strlen(locale[ctx->locale][dir])-1));

                    sprintf(message, locale[ctx->locale][LC_RETREAT_MESSAGE], locale[ctx->locale][dir]);
                    consoleBufferAdd(&ctx->consoleBuffer, message);
                    free(message);

                    ctx->player.score += 10;
                } else {
                    consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_MOVE_FAIL_MESSAGE]);
                }
            }
            // turn left
            else if (LEFT_PRESSED(ctx->input)) {
                char *message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_TURN_MESSAGE]) + strlen(locale[ctx->locale][LC_LEFT])-1));

                playerMakeTurn(&ctx->player, Left);
                
                sprintf(message, locale[ctx->locale][LC_TURN_MESSAGE], locale[ctx->locale][LC_LEFT]);
                consoleBufferAdd(&ctx->consoleBuffer, message);
                free(message);
            }
            // turn right
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
                int8 itemSelection = 0, itemOption = 3;
                switch (ctx->choice) {
                    case Attack:
                        // This is a pretty dreadful way of doing this
                        playerAttackEnemy(ctx);
                        clrscr();
                        draw(ctx);
                        musicCombatPlayerTurn();
                        sleep(1);
                        if (ctx->enemy.stats.health.health <= 0) {
                            consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_COMBAT_ENEMY_DEFEATED]);
                            musicCombatWin();
                            if (playerAddXp(ctx, &lvlStats)) {
                                menuDrawLevelUp(ctx, &lvlStats);
                                ctx->input = 0;
                                ctx->player.score += 100*ctx->player.stats.level;
                                while (ctx->input != KEY_RETURN && ctx->input != 3) {
                                    ctx->input = cgetc();
                                }
                            }
                            ctx->player.score += 50+(10*ctx->enemy.stats.level);
                            ctx->gameState = Game;
                        } else {
                            enemyAttack(ctx, false);
                            musicCombatEnemyTurn();
                            if (ctx->player.stats.health.health <= 0) {
                                ctx->gameState = DeathScreen;
                            }
                        }
                        break; 
                    case Defend:
                        consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_COMBAT_PLAYER_DEFEND]);
                        clrscr();
                        draw(ctx);
                        musicCombatPlayerTurn();
                        sleep(1);
                        enemyAttack(ctx, true);
                        musicCombatEnemyTurn();
                        if (ctx->player.stats.health.health <= 0) {
                            ctx->gameState = DeathScreen;
                        }
                        break;
                    case Inspect:
                        consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_ENEMY_INSPECT]);
                        musicCombatPlayerTurn();
                        menuDrawEnemyStats(ctx);
                        ctx->input = 0;
                        while (ctx->input != KEY_RETURN && ctx->input != 3)
                            ctx->input = cgetc();
                        break;
                    case Inventory:

                        // All this code is copied, but functionalizing this would be really quite dreadful
                        ctx->input = 0;
                        menuDrawInventory(ctx, itemSelection, true);

                        while (ctx->input != 'i' && ctx->input != 3) {
                            menuDrawInventory(ctx, itemSelection, false);
                            ctx->input = cgetc();
                            if (UP_PRESSED(ctx->input)) {
                                itemSelection = itemSelection - 1 < 0 ? ctx->player.inventorySize-1 : itemSelection - 1;
                            } else if (DOWN_PRESSED(ctx->input)) {
                                itemSelection = itemSelection + 1 > ctx->player.inventorySize-1 ? 0 : itemSelection + 1;
                            } else if (ctx->input == KEY_RETURN && ctx->player.inventorySize > 0) {
                                itemOption = 0;
                                menuDrawInventorySelection(ctx, itemOption, true);
                            }

                            while (itemOption != 3) {
                                menuDrawInventorySelection(ctx, itemOption, false);
                                ctx->input = cgetc();
                                if (UP_PRESSED(ctx->input) || DOWN_PRESSED(ctx->input)) {
                                    itemOption = itemOption ? 0 : 1;
                                }
                                else if (ctx->input == 'i' || ctx->input == 3) {
                                    itemOption = 3;
                                }
                                else if (ctx->input == KEY_RETURN) {
                                    if (itemOption == 0) {
                                        Item item;
                                        char *message;
                                        
                                        playerUseItem(ctx, itemSelection, &item);
                                        clrscr();
                                        draw(ctx);
                                        musicDrinkPotion();
                                        sleep(1);

                                        message = malloc(sizeof(char) * (strlen(locale[ctx->locale][LC_ITEM_USE]) + strlen(locale[ctx->locale][LC_POTION_HEALTH + item.stat]) + 1));
                                        sprintf(message, locale[ctx->locale][LC_ITEM_EFFECT], locale[ctx->locale][LC_POTION_HEALTH + item.stat], item.modifier);
                                        consoleBufferAdd(&ctx->consoleBuffer, message);
                                        free(message);

                                    }
                                    else if (itemOption == 1) {
                                        playerDropItem(ctx, itemSelection);
                                    }
                                    itemOption = 3;
                                    ctx->input = 'i';
                                }
                            }
                        }
                        clrscr();
                        draw(ctx);
                        musicCombatPlayerTurn();
                        sleep(1);
                        enemyAttack(ctx, false);
                        musicCombatEnemyTurn();
                        break;
                    case Run:
                        // chance of sucessful flee scales off of player luck
                        if ((rand() % 10)+ctx->player.stats.luck > 5) {
                            consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_COMBAT_PLAYER_RUN_SUCCESS]);
                            ctx->gameState = Game;
                        } else {
                            consoleBufferAdd(&ctx->consoleBuffer, locale[ctx->locale][LC_COMBAT_PLAYER_RUN_FAIL]);
                            clrscr();
                            draw(ctx);
                            musicCombatPlayerTurn();
                            sleep(1);
                            enemyAttack(ctx, false);
                            musicCombatEnemyTurn();
                        }
                        break;
                } 
                clrscr();
            }
            break;

        case DeathScreen:
            if (ctx->input == KEY_RETURN) {
                ctx->gameRunning = false;
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

    else if (debugMode && ctx->input == 'q') {
        ctx->locale = ctx->locale == English ? Esperanto : English;
        clrscr();
    }
}
