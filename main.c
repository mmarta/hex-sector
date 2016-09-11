#include "machine.h"
#include "game.h"
#include "title.h"

int main() {
    //Initialize system
    machineInit();
    gameStart();

    while(1) {
        WaitVsync(1);

        //Update & inputs
        machineCheckCoinStart();

        if(machineTitleMode) {
            titleUpdate();
        } else {
            gameUpdate();
        }
    }
}