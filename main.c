#include <stdio.h>
#include <string.h>
#include <cbm.h>
#include <conio.h>


/* Screen dimensions */
static unsigned char XSize, YSize;


void MakeTeeLine(unsigned char Y) {
    cputcxy(0, Y, CH_LTEE);
    chline(XSize - 2);
    cputc(CH_RTEE);
}



void MakeNiceScreen(void) {
    char* message = "Hello world!";

    textcolor(COLOR_WHITE);
    bordercolor(COLOR_BLACK);
    bgcolor(COLOR_BLACK);

    clrscr();
    cursor(0);

    /* Top line */
    cputcxy(0, 0, CH_ULCORNER);
    chline(XSize - 2);
    cputc(CH_URCORNER);

    /* Left line */
    cvlinexy(0, 1, 23);

    /* Bottom line */
    cputc(CH_LLCORNER);
    chline(XSize - 2);
    cputc(CH_LRCORNER);

    /* Right line */
    cvlinexy(XSize - 1, 1, 23);
    
    MakeTeeLine(22);
    
    gotox(1);
    printf("Hello world!");
    

}


int main (void) {

    /* Get the screen dimensions */
    screensize (&XSize, &YSize);

    /* Make a nice screen */
    MakeNiceScreen ();
    cgetc ();
    /* Clear the screen */
    clrscr ();

    /* If we have a character, remove it from the buffer */
    if (kbhit ()) {
        cgetc ();
    }

    /* Done */
    return 0;
}



