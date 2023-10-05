#ifndef LOCALE_H
#define LOCALE_H

#define LC_NUM_STRINGS 7

#define LC_TITLE_PROMPT 0
#define LC_TITLE_LANG 1
#define LC_NAME_PROMPT 2
#define LC_QUIT_PROMPT1 3
#define LC_QUIT_PROMPT2 4
#define LC_YES 5
#define LC_NO 6


enum Locale {
    English,
    Esperanto
};

extern const char* locale[2][LC_NUM_STRINGS];

#endif