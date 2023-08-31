#include "sorcery.h"

#include <conio.h>
#include <stdbool.h>

bool gameRunning = true;
bool quitPrompt = false;

unsigned char c = 0;

void gameLoop() {
    while (gameRunning) {
        clrscr();
        menuDrawTitleScreen();
        menuDrawWindow(5, 5, 5, 5);

        gotoxy(3,5);
        cprintf("%d", c);

        if (quitPrompt) {
            menuDrawQuitPrompt();
        }
        
        c = cgetc();
        if (c == 3) {
            quitPrompt = true;
        }
        c = 0;
    }
    
}