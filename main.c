#include "machine.h"
#include "game.h"
#include "title.h"

int main() {
    u8 start;

    //Initialize system
    machineInit();

    while(1) {
        WaitVsync(1);

        //Update & inputs
        start = machineCheckCoinStart();

        if(machineTitleMode) {
            if(start && titleTime < 1500) {
                titleTime = 2000;
            } else if(titleTime == 2100) {
                machineTitleMode = 0;
                gameStart();
            }

            titleUpdate();
        } else {
            gameUpdate();
            if(machineTitleMode) {
                titleReset();
            }
        }
    }
}
