#include "machine.h"

u8 machineCredits = 0, machineTitleMode = 1, machineInputB[] = {0, 0, 0, 0};
unsigned long machineHi = 10000;
const char machineCreditString[] PROGMEM = "CREDIT";
const char machineHiString[] PROGMEM = "HI";

void machineAddCoin();

//Inits tile tables & whatnot
void machineInit() {
    //Set the tile table and clear.
    SetTileTable(gfxTiles);
    ClearVram();

    SetSpritesTileTable(gfxTilesSprite);
    SetSpriteVisibility(1);
    gfxLoadIndexSprite();

    PrintByte(18, 27, machineCredits, 0);
    Print(11, 27, machineCreditString);

    Print(25, 0, machineHiString);
    PrintLong(29, 1, machineHi);
}

//Checks coin up & player start inputs
u8 machineCheckCoinStart() {
    unsigned int padA = ReadJoypad(0);
    unsigned int padB = ReadJoypad(1);

    //Service!
    if(padA & BTN_SL) {
        if(!machineInputB[0]) {
            machineAddCoin();
            machineInputB[0] = 1;
        }
    } else {
        machineInputB[0] = 0;
    }

    //Coins (dunno why mapped to strange things)
    if(padB & BTN_SR) {
        if(!machineInputB[1]) {
            machineAddCoin();
            machineInputB[1] = 1;
        }
    } else {
        machineInputB[1] = 0;
    }

    if(padB & BTN_SL) {
        if(!machineInputB[2]) {
            machineAddCoin();
            machineInputB[2] = 1;
        }
    } else {
        machineInputB[2] = 0;
    }

    //Player 1 Start
    if(padA & BTN_START && machineTitleMode) {
        if(!machineInputB[3]) {
            machineInputB[3] = 1;
            if(machineCredits > 0) {
                //Start!
                machineCredits--;
                PrintByte(18, 27, machineCredits, 0);
                Print(11, 27, machineCreditString);
                return 1;
            }
        }
    } else {
        machineInputB[3] = 0;
    }

    return 0;
}

//Adds a coin
void machineAddCoin() {
    if(machineCredits < 9) {
        machineCredits++;
        PrintByte(18, 27, machineCredits, 0);
        Print(11, 27, machineCreditString);
    }
}
