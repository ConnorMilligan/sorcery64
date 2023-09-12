#include "sorcery.h"

#include <conio.h>
#include <stdbool.h>

bool gameRunning = true;
bool quitPrompt = false;

void gameLoop() {
    uint8 c = 0;

    while (gameRunning) {
        clrscr();
        menuDrawTitleScreen();
        menuDrawWindow(5, 5, 5, 5);

        if (quitPrompt) {
            menuDrawQuitPrompt();
            gameRunning = selectorQuitPrompt() ? true : false;
            quitPrompt = false;
        } else {
            c = cgetc();
        }
        
        if (c == 3) {
            quitPrompt = true;
        }

        gotoxy(3,5);
        cprintf("%d", c);

        c = 0;
    }
    
}