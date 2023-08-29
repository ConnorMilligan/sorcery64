#include "sorcery.h"

#include <conio.h>

void gameLoop() {
    unsigned char c = 65;
    while (c != 3) {
        drawTitleScreen();

        c = cgetc();
    }
    
}