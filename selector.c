#include "sorcery.h"

#include <stdbool.h>

int selectorQuitPrompt() {
    char choice = 0;
    bool select = false;
    char c = 0;

    while (!select) {
        choice : cputcxy(XSize/2 - 4, 13, 218) ? cputcxy(XSize/2 - 4, 13, 218);
        
        c = cgetc();
        
    }
}