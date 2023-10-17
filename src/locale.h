#ifndef LOCALE_H
#define LOCALE_H

#include "constants.h"

#define LC_NUM_STRINGS 22

#define LC_TITLE_PROMPT 0
#define LC_TITLE_LANG 1
#define LC_NAME_PROMPT 2

#define LC_QUIT_PROMPT1 3
#define LC_QUIT_PROMPT2 4
#define LC_YES 5
#define LC_NO 6

#define LC_STAT_LEVEL 7
#define LC_STAT_HP 8
#define LC_STAT_ATK 10
#define LC_STAT_DEF 11
#define LC_STAT_SPD 12
#define LC_STAT_LCK 13

#define LC_SIDEBAR_STAT_LABEL 9
#define LC_SIDEBAR_LOC_LABEL 14
#define LC_SIDEBAR_LOC 15
#define LC_SIDEBAR_DIR 16

#define LC_DIR_NORTH 18
#define LC_DIR_EAST 19
#define LC_DIR_SOUTH 20
#define LC_DIR_WEST 21

#define LC_MAP_WINDOW_LABEL 17

extern const char* locale[2][LC_NUM_STRINGS];

#endif