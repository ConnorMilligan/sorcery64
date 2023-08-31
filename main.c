#include "sorcery.h"

#include <conio.h>
#include <peekpoke.h>

unsigned char XSize, YSize;

int main (void) {
    /* Get the screen dimensions */
    screensize(&XSize, &YSize);
    POKE(53272,21);
    
    bordercolor(COLOR_BLACK);
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);

    clrscr();
    cursor(0);

    gameLoop();

    /* Clear the screen */
    clrscr();

    /* If we have a character, remove it from the buffer */
    if (kbhit()) {
        cgetc();
    }

    /* Done */
    return 0;
}



