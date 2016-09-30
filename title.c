#include "title.h"

u16 titleTime;
u8 titleLastCredits;

const char sectorStr[] PROGMEM = "SECTOR";
const char copyStr[] PROGMEM = "@2016 ARXENGINE";
const char pressStartStr[] PROGMEM = "PRESS  START";
const char insertCoinStr[] PROGMEM = "INSERT  COIN";

void titleUpdate() {
    u8 modTime = titleTime % 80;
    switch(titleTime) {
        case 0:
            break;
        case 15:
            DrawMap(11, 9, gfxLogoH);
            break;
        case 55:
            DrawMap(13, 8, gfxLogoE);
            break;
        case 95:
            DrawMap(17, 9, gfxLogoX);
            break;
        case 135:
            Print(12, 14, sectorStr);
            break;
        case 175:
            Print(7, 17, copyStr);
            break;
    }

    if(titleLastCredits < machineCredits) {
        titleTime = 175;
        DrawMap(11, 9, gfxLogoH);
        DrawMap(13, 8, gfxLogoE);
        DrawMap(17, 9, gfxLogoX);
        Print(12, 14, sectorStr);
        Print(7, 17, copyStr);
        Print(9, 25, pressStartStr);
    } else if(modTime == 0) {
        if(machineCredits == 0) {
            Print(9, 25, insertCoinStr);
        } else {
            Print(9, 25, pressStartStr);
        }
    } else if(modTime == 40) {
        DrawMap(0, 23, gfxMapLongBlank);
    }

    titleLastCredits = machineCredits;

    titleTime++;
    if(titleTime >= 600) {
        titleTime = 0;
    }
}
