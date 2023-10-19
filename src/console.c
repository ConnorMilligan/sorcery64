#include "sorcery.h"

#include <conio.h>
#include <string.h>

uint8 getNextWordLen(char *text, uint8 pos);

void consoleWrite(char *text) {
    uint8 i;
    uint8 x = 3, y = yBound+1;

    cputcxy(x-2, y, 215);

    for (i = 0; i < strlen(text); i++) {
        if (x == XSize-1) {
            if (y == YSize-2)
                return;
            x = 3;
            y++;
        }
        if (getNextWordLen(text, i) + x > XSize-1) {
            x = 3;
            y++;
        }
        cputcxy(x, y, text[i]);
        x++;
    }
}

uint8 getNextWordLen(char *text, uint8 pos) {
    uint8 len = 0;

    while (text[pos+len] != ' ' && text[pos+len] != '\0') {
        len++;
    }

    return len;
}