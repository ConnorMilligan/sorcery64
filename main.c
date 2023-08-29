#include "sorcery.h"

#include <conio.h>

unsigned char XSize, YSize;

int main (void) {

    /* Get the screen dimensions */
    screensize(&XSize, &YSize);

    
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



