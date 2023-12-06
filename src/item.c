#include "sorcery.h"

void itemBuild(Item *item, enum StatType stat, int8 modifier) {
    item->stat = stat;
    item->modifier = modifier;
}

void itemBuildEmpty(Item *item) {
    itemBuild(item, StatXp, 0);
}