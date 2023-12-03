#include "sorcery.h"

#include <c64.h>

const unsigned int combatHitNotes[] = {
    0x7c31, 0x3e98, 0x1f4c 
};

const unsigned int combatWinNotes[] = {
    0xe6b, 0x133f, 0x159a, 0x1981, 0x0000, 0x159a, 0x1981, 0x1981
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

void musicCombatWin() {
    unsigned int i,d;
    
    SID.amp = 0x1F;
    SID.v1.ad = 0x0f;
    for(i = 0; i < sizeof(combatWinNotes) / sizeof(int); i++) {
        SID.v1.freq = combatWinNotes[i];
        SID.v1.ctrl = 0x11;
        for(d=0; d<1300; d++) { }
        SID.v1.ctrl = 0x10;
    }
}