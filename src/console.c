#include "sorcery.h"

#include <conio.h>
#include <string.h>
#include <stdlib.h>

void consoleBufferBuild(ConsoleBuffer *consoleBuffer) {
    uint8 i;

    for (i = 0; i < 6; i++) {
        consoleBuffer->buffer[i] = malloc(sizeof(char));
        *consoleBuffer->buffer[i] = '\0';
    }

    consoleBuffer->pos = 0;
}

void consoleWrite(ConsoleBuffer *consoleBuffer, uint8 bound) {
    uint8 i, j;
    uint8 x = 3, y = yBound+1;
    uint8 pos;

    // Loop through the buffer in order
    for (i = 0; i < 6; i++) {
        pos = (consoleBuffer->pos + 6 - i) % 6;
        x = 3;

        if (*consoleBuffer->buffer[pos] != '\0') {
            if (y < YSize-1)
                cputcxy(x-2, y, 215);

            for (j = 0; j < strlen(*consoleBuffer->buffer[pos]); j++) {
                if (x == XSize-1 || getNextWordLen(*consoleBuffer->buffer[pos], j) + x > bound-1) {
                    x = 3;
                    y++;
                }
                if (y > YSize-2) {
                    textcolor(COLOR_WHITE);
                    return;
                }
                cputcxy(x, y, (*consoleBuffer->buffer[pos])[j]);
                x++;
            }
            y++;
        }
        if (i == 0)
            textcolor(COLOR_GRAY2);
    }
    textcolor(COLOR_WHITE);
}

void consoleBufferAdd(ConsoleBuffer *consoleBuffer, const char *text) {
    // update buffer position
    consoleBuffer->pos = (consoleBuffer->pos + 1) % 6;

    // free memory for previous string
    free((char*)*consoleBuffer->buffer[consoleBuffer->pos]);

    // allocate memory for new string
    *consoleBuffer->buffer[consoleBuffer->pos] = malloc(sizeof(char) * (strlen(text) + 1));

    // copy new string to buffer
    memcpy(*consoleBuffer->buffer[consoleBuffer->pos], text, strlen(text) + 1);
}


void consoleBufferCleanUp(ConsoleBuffer *consoleBuffer) {
    uint8 i;

    for (i = 0; i < 6; i++) {
        free(consoleBuffer->buffer[i]);
    }
}

uint8 getNextWordLen(const char *text, uint8 pos) {
    uint8 len = 0;

    while (text[pos+len] != ' ' && text[pos+len] != '\0') {
        len++;
    }

    return len;
}

void consoleMenuClear() {
    size_t x, y;

    for (y = yBound+1; y < YSize-1; y++) {
        cputcxy(1, y, CHAR_BLANK);
        for (x = 3; x < xBound-1; x++) {
            cputcxy(x, y, CHAR_BLANK);
        }
    }
}