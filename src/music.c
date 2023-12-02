#include "sorcery.h"

#include <c64.h>

const unsigned int combatHitNotes[] = {
    0x7c31, 0x3e98, 0x1f4c 
};


void musicCombatPlayerTurn() {
    unsigned int i,d;
    
    SID.amp = 0x1F;
    SID.v1.ad = 0x0f;
    for(i = 0; i < sizeof(combatHitNotes) / sizeof(int); i++) {
        SID.v1.freq = combatHitNotes[i];
        SID.v1.ctrl = 0x11;
        for(d=0; d<1000; d++) { }
        SID.v1.ctrl = 0x10;
    }
}

void musicCombatEnemyTurn() {
    unsigned int i,d;
    
    SID.amp = 0x1F;
    SID.v1.ad = 0x0f;
    for(i = sizeof(combatHitNotes) / sizeof(int); i > 0; i--) {
        SID.v1.freq = combatHitNotes[i];
        SID.v1.ctrl = 0x11;
        for(d=0; d<1000; d++) { }
        SID.v1.ctrl = 0x10;
    }
}