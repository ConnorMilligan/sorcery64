#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdbool.h>

#define POKE_CHAR(x, y, char) (POKE(((1024 + (x)) + ((y) * 40)), (char)))
#define POKE_COLOR(x, y, color) (((55296U+x)+(y*40)), color);

#define UP_PRESSED(c) (c == KEY_UP || c == KEY_W || c == KEY_J)
#define DOWN_PRESSED(c) (c == KEY_DOWN || c == KEY_S || c == KEY_K)
#define LEFT_PRESSED(c) (c == KEY_LEFT || c == KEY_A || c == KEY_H)
#define RIGHT_PRESSED(c) (c == KEY_RIGHT || c == KEY_D || c == KEY_L)

#define KEY_J 74
#define KEY_K 75
#define KEY_H 72
#define KEY_L 76

#define KEY_UP 145
#define KEY_DOWN 17
#define KEY_LEFT 157
#define KEY_RIGHT 29

#define KEY_W 87
#define KEY_A 65
#define KEY_S 83
#define KEY_D 68

#define KEY_RETURN 13
#define KEY_BACKSPACE 20

#define CHAR_BLANK 32

#define MAZE_WIDTH  20
#define MAZE_HEIGHT 20
#define MAZE_OFFSET 3

#define XP_FACTOR 2
#define INVENTORY_SIZE 5

typedef unsigned char uint8;
typedef signed char int8;

enum GameState {
    TitleScreen,
    NamePrompt,
    Game,
    Battle,
    DeathScreen
};

enum QuitSelection {
    Quit,
    Remain,
    Pass
};

enum BattleSelection {
    Attack,
    Defend,
    Inspect,
    Inventory,
    Run
};

enum StatType {
    StatHealth,
    StatAttack,
    StatDefense,
    StatSpeed,
    StatLuck
};

enum Direction {
    North = 18,
    East = 19,
    South = 20,
    West = 21
};

enum Movement {
    Forward,
    Backward,
    Left,
    Right
};

enum Locale {
    English,
    Esperanto
};

typedef struct Health {
    int8 health;
    int8 maxHealth;
} Health;

typedef struct Position {
    char x;
    char y;
} Position;

typedef struct Stats {
    uint8 level;
    uint8 experience;

    Health health;

    uint8 attack;
    uint8 defense;
    uint8 speed;
    uint8 luck;
} Stats;

typedef struct Item {
    enum StatType stat;
    int8 modifier;
} Item;

typedef struct Player {
    char name[9];

    Position position;
    enum Direction direction;

    unsigned int score;

    Item items[INVENTORY_SIZE];
    uint8 inventorySize;
    Stats stats;
} Player;

typedef struct Enemy {
    uint8 headName;
    uint8 bodyName;
    uint8 adjective;

    const char (*head)[8][8];
    const char (*body)[8][8];

    Stats stats;
} Enemy;

typedef struct Maze {
    uint8 map[MAZE_HEIGHT][MAZE_OFFSET];
    Position start;
} Maze;

typedef struct ConsoleBuffer {
    const char **buffer[6];
    uint8 pos;
} ConsoleBuffer;

typedef struct Context {
    Player player;
    Enemy enemy;
    Maze maze;
    ConsoleBuffer consoleBuffer;

    bool gameRunning;

    bool quitPrompt;

    uint8 quitSelector;
    uint8 choice;
    uint8 input;

    enum Locale locale;
    enum GameState gameState;
} Context;


#endif