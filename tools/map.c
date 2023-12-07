#include <stdio.h>
#include <math.h>

const char maze[20][20] = {
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o','o', 'o', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'o', 'w', 'w', 'o', 'w', 'w', 'w', 'w','w', 'w', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'w', 'w', 'o', 'w', 'w', 'o', 'w', 'w', 'w', 'w','w', 'w', 'o', 'o', 'o', 'o', 'o', 'w', 'w', 'w'},
    {'w', 'w', 'o', 'w', 'w', 'o', 'w', 'w', 'w', 'w','w', 'w', 'o', 'w', 'w', 'w', 'o', 'w', 'w', 'w'},
    {'w', 'o', 'o', 'o', 'w', 'o', 'w', 'w', 'o', 'o','o', 'o', 'o', 'o', 'w', 'w', 'o', 'o', 'o', 'w'},
    {'w', 'o', 'w', 'o', 'w', 'o', 'o', 'o', 'o', 'w','w', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w','w', 'w', 'w', 'o', 'o', 'o', 'o', 'o', 'o', 'w'},
    {'w', 'o', 'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w','w', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'w', 'o', 'o', 'o', 'o', 'o', 'o', 'o','o', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w', 'w', 'w','o', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w', 'w', 'w','o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'w'},
    {'w', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'w','o', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w', 'o', 'w','o', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'o', 'o', 'o', 'o', 'o', 'w', 'o', 'w','o', 'o', 'o', 'o', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'o', 'w','o', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'o', 'o','o', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'o', 'w','w', 'w', 'w', 'o', 'w', 'w', 'w', 'w', 'o', 'w'},
    {'w', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'w','w', 'w', 'w', 'o', 'o', 'o', 'o', 'o', 'o', 'w'},
    {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'}
};

int getMap(unsigned char map[20][3], int x, int y) {
    int bitPosition = x % 8;
    unsigned char byte = map[y][x / 8];

    return (byte >> bitPosition) & 1;
}

int main(void) {
    unsigned char submap[3];
    unsigned char map[20][3];

    for (int i = 0; i < 20; i++) {
        submap[0] = 0;
        submap[1] = 0;
        submap[2] = 0;

        for (int j = 0; j < 20; j++) {
            if (maze[i][j] == 'w') {
                if (j < 8)
                    submap[0] += 1 << j;
                else if (j < 16)
                    submap[1] += 1 << (j - 8);
                else
                    submap[2] += 1 << (j - 16);
            }
        }
        for (int j = 0; j < 3; j++) {
            map[i][j] = submap[j];
        }

    }

    for (int i = 0; i < 20; i++) {
        printf("{");
        for (int j = 0; j < 3; j++) {
            if (j == 2)
                printf("%d", map[i][j]);
            else
                printf("%d, ", map[i][j]);
        }
        printf("},\n");
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 3; j++) {
            int x = map[i][j];
            while (x) {
                if (x & 1)
                    printf("1");
                else
                    printf("0");

                x >>= 1;
            }
            printf(" ");
        }
        printf("\n");
    }

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++)
            if (getMap(map, j, i) == 1) {
                printf("█");
            } else {
                printf(" ");
            }
        printf("\n");
    }



    return 0;
}

        
