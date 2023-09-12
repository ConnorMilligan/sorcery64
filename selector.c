#include "sorcery.h"

#include <stdbool.h>
#include <conio.h>

uint8 selectorQuitPrompt() {
    uint8 choice = 0;
    bool select = false;
    char c = 0;

    while (!select) {
        choice ? cputcxy(XSize/2 - 4, 14, 218) : cputcxy(XSize/2 - 4, 13, 218);
        choice ? cputcxy(XSize/2 - 4, 13, 32) : cputcxy(XSize/2 - 4, 14, 32);
        
        c = cgetc();

        if (c == KEY_DOWN || c == KEY_UP) {
            choice =  choice ? 0 : 1;
        } else if (c == KEY_RETURN) {
            return choice;
        }
        
        
    }
}