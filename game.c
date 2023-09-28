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
enum gameState currentState = TitleScreen;

void gameLoop() {
    uint8 c = 0, choice = 0;

    while (gameRunning) {
        draw(&c, &choice);

        c = 12;
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
        menuDrawQuitPrompt(*choice);
    }
}

void takeInput(uint8 *c, uint8 *choice) {
    *c = cgetc();

    if (quitPrompt) {
        if (*c == KEY_DOWN || *c == KEY_UP) {
            *choice = *choice ? 0 : 1;
        } 
        else if (*c == KEY_RETURN) {
            if (*choice == 0) {
                gameRunning = false;
            }
            else {
                quitPrompt = false;
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

        
    }
        
    if (*c == 3) {
        quitPrompt = true;
    }
}