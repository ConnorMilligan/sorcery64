#include "sorcery.h"

#include <conio.h>
#include <stdbool.h>

enum gameState {
    TitleScreen,
    NamePrompt,
    Game
};

bool gameRunning = true;
bool quitPrompt = false;
uint8 quitSelector = 0;
enum gameState currentState = TitleScreen;

void gameLoop() {
    uint8 c = 0, choice = 0;

    while (gameRunning) {
        draw(&c, &choice);

        gotoxy(3,5);
        cprintf("value of c: %d", c);
        gotoxy(3,6);
        cprintf("value of choice: %d", choice);

        takeInput(&c, &choice);
    }
    
}

void draw(uint8 *c, uint8 *choice) {
    if (!quitPrompt && currentState != NamePrompt) {
        clrscr();
    }

    if (currentState == TitleScreen) {
        menuDrawTitleScreen();
    }
    else if (currentState == NamePrompt) {
        menuDrawNamePrompt();
    }

    if (quitPrompt) {
        menuDrawQuitPrompt(quitSelector);
    }
}

void takeInput(uint8 *c, uint8 *choice) {
    *c = cgetc();

    if (quitPrompt) {
        if (*c == KEY_DOWN || *c == KEY_UP) {
            quitSelector = quitSelector ? 0 : 1;
        } 
        else if (*c == KEY_RETURN) {
            if (quitSelector == 0) {
                gameRunning = false;
            }
            else {
                quitPrompt = false;
                clrscr();
            }
        }
    }

    // Title Screen prompts
    if (*c == KEY_RETURN && currentState == TitleScreen && !quitPrompt) {
        currentState = NamePrompt;
        clrscr();
    }

    else if (currentState == NamePrompt) {
        uint8 x = (XSize)/2 - 12, y = YSize/2+1;

        if (*c != KEY_RETURN && *c != KEY_BACKSPACE) {
            *choice+=1;
            cputcxy(x + *choice, y, c);
        } else if (*c == KEY_BACKSPACE) {
            *choice-=1;;
            cputcxy(x + *choice, y, CHAR_BLANK);
        }
        
    }
        
    if (*c == 3) {
        quitPrompt = true;
    }
}