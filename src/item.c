#include "sorcery.h"

void itemBuild(Item *item, enum StatType stat, int8 modifier) {
    item->stat = stat;
    item->modifier = modifier;
    if (item->stat == StatHealth)
        item->modifier *= 5;
}

void itemBuildEmpty(Item *item) {
    itemBuild(item, StatHealth, 0);
}