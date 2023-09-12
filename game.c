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
    while (gameRunning) {
        //gotoxy(3,5);
        //cprintf("%d", c);
        draw();
        takeInput();
    }
    
}

void draw() {
    clrscr();

    if (currentState == TitleScreen) {
        menuDrawTitleScreen();
    }
    else if (currentState == NamePrompt) {
        menuDrawNamePrompt();
    }
}

void takeInput() {
    uint8 c = 0;
        
    if (quitPrompt) {
        menuDrawQuitPrompt();
        gameRunning = selectorQuitPrompt() ? true : false;
        quitPrompt = false;
    } else {
        c = cgetc();
    }

    // Title Screen prompts
    if (c == KEY_RETURN && currentState == TitleScreen) {
        currentState = NamePrompt;
    }
        
    if (c == 3) {
        quitPrompt = true;
    }
}