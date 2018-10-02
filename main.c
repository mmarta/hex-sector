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
        machineCheckCoin();

        if(machineTitleMode) {
            if(titleTime < 1500) {
                start = machineCheckStart();
                if(start) {
                    titleTime = 1700;
                }
            } else if(titleTime == 1800) {
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
