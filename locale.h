#ifndef LOCALE_H
#define LOCALE_H

#define LC_NUM_STRINGS 2

#define LC_TITLE_PROMPT 0
#define LC_TITLE_LANG 1

enum Locale {
    English,
    Esperanto
};

extern char* locale[2][LC_NUM_STRINGS];

#endif