#ifndef LOCALE_H
#define LOCALE_H

#include "constants.h"

#define LC_NUM_STRINGS 49

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

#define LC_NORTH 22
#define LC_EAST 23
#define LC_SOUTH 24
#define LC_WEST 25

#define LC_LEFT 30
#define LC_RIGHT 31

#define LC_ADVANCE_MESSAGE 26
#define LC_RETREAT_MESSAGE 27
#define LC_MOVE_FAIL_MESSAGE 28
#define LC_TURN_MESSAGE 29
#define LC_MAZE_ENTRY_MESSAGE 32

#define LC_MAP_WINDOW_LABEL 17

#define LC_ENEMY_HEAD_1 33
#define LC_ENEMY_HEAD_2 34
#define LC_ENEMY_HEAD_3 35
#define LC_ENEMY_HEAD_4 36
#define LC_ENEMY_HEAD_5 37

#define LC_ENEMY_BODY_1 38
#define LC_ENEMY_BODY_2 39
#define LC_ENEMY_BODY_3 40
#define LC_ENEMY_BODY_4 41
#define LC_ENEMY_BODY_5 42

#define LC_ENEMY_ADJECTIVE_1 43
#define LC_ENEMY_ADJECTIVE_2 44
#define LC_ENEMY_ADJECTIVE_3 45
#define LC_ENEMY_ADJECTIVE_4 46
#define LC_ENEMY_ADJECTIVE_5 47

#define LC_ENEMY_ENCOUNTER_TEXT 48

extern const char* locale[2][LC_NUM_STRINGS];

#endif