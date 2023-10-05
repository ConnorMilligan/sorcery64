#ifndef LOCALE_H
#define LOCALE_H

#define LC_NUM_STRINGS 3

#define LC_TITLE_PROMPT 0
#define LC_TITLE_LANG 1
#define LC_NAME_PROMPT 2

enum Locale {
    English,
    Esperanto
};

extern const char* locale[2][LC_NUM_STRINGS];

#endif