#include "player.h"

u8 playerLocation, playerLives, playerTime, playerDieTime, playerFlash, playerFlashTick;
unsigned long playerScore;
u8 playerRedrawTick = 0;

unsigned long playerToNext;

//Internal vars
u8 playerLastLocation, playerLocationTime;
u8 playerLeftB, playerRightB, playerFireB, playerFlashB;

const char scoreString[] PROGMEM = "SCORE";
const char readyString[] PROGMEM = "READY!";
const char flashString[] PROGMEM = "FLASH=";
const char gameOverString[] PROGMEM = "GAME  OVER";

void playerFire();
void playerDraw();
u8 playerCheckAllShotsFree();

void playerStart() {
    u8 i;

    playerLocation = LOCATION_GREEN;
    playerLives = 3;
    playerTime = 0;
    playerDieTime = 0;
    playerLocationTime = 0;
    playerFlash = 1;

    playerLeftB = 0;
    playerRightB = 0;
    playerFireB = 0;
    playerFlashB = 0;

    playerScore = 0;
    playerToNext = 50000;

    locationDraw(playerLocation, playerLastLocation, playerLocationTime);
    locationShowAll(playerLocation);
    playerDraw();
    Print(0, 0, scoreString);
    Print(21, 4, flashString);
    PrintLong(7, 1, playerScore);
    PrintByte(29, 4, playerFlash, 0);

    i = playerLives - 1;
    while(i--) {
        DrawMap(i, 2, gfxLife);
    }
}

void playerInput() {
    u8 i = SHOT_TOTAL_ONSCREEN;
    unsigned int pad;

    if(playerDieTime > 0) {
        return; //No input if player is dying.
    }

    pad = ReadJoypad(0);
    playerFlashTick = 0; //Reset tick

    if(pad & BTN_LEFT) {
        if(!playerLeftB && playerLocationTime == 0) {
            playerLastLocation = playerLocation;
            playerLocation--;
            playerLocationTime = 1;
            playerRedrawTick = 1;
            if(playerLocation == 255) {
                playerLocation = LOCATION_CYAN;
            }
            locationMoveArrow(playerLocation);

            while(i--) {
                shotFree(i);
            }

            playerLeftB = 1;
        }
    } else {
        playerLeftB = 0;
    }

    if(pad & BTN_RIGHT) {
        if(!playerRightB && playerLocationTime == 0) {
            playerLastLocation = playerLocation;
            playerLocation++;
            playerLocationTime = 1;
            playerRedrawTick = 1;
            if(playerLocation == 6) {
                playerLocation = LOCATION_GREEN;
            }
            locationMoveArrow(playerLocation);

            while(i--) {
                shotFree(i);
            }

            playerRightB = 1;
        }
    } else {
        playerRightB = 0;
    }

    if(pad & BTN_A) {
        if(!playerFireB && playerLocationTime == 0) {
            playerFire();
            playerFireB = 1;
        }
    } else {
        playerFireB = 0;
    }

    if(pad & BTN_B) {
        if(!playerFlashB && playerLocationTime == 0 && playerFlash) {
            playerFlashTick = 1;
            playerFlash--;
            PrintByte(29, 4, playerFlash, 0);
            playerFlashB = 1;
        }
    } else {
        playerFlashB = 0;
    }
}

void playerUpdate() {
    u8 i;

    if(playerDieTime == 0) {
        playerTime++;
        if(playerTime >= 8) {
            playerTime = 0;
        }

        if(playerTime == 0 || playerTime == 4) {
            playerDraw();
        }

        if(playerLocationTime > 0) {
            playerLocationTime++;

            if(playerLocationTime == 2 || playerLocationTime == 8) {
                locationDraw(playerLocation, playerLastLocation, playerLocationTime);
            } else if(playerLocationTime >= 14) {
                playerLocationTime = 0;
                playerRedrawTick = 1;
                locationDraw(playerLocation, playerLastLocation, playerLocationTime);
            }
        }
    } else {
        if(playerDieTime <= 17) {
            switch(playerDieTime) {
                case 1:
                case 5:
                case 9:
                case 13:
                case 17:
                    playerDraw();
                    break;
            }
        } else if(playerDieTime == 30) {
            playerLocationTime = 0;
            playerLives--;
            DrawMap(playerLives - 1, 2, gfxMapBlank8);

            playerFlash = 1;
            PrintByte(29, 4, playerFlash, 0);

            locationClear();
            if(playerLives > 0) {
                Print(12, 13, readyString);
            } else {
                Print(10, 13, gameOverString);
            }

            //Clear shots
            i = 0;
            while(i < SHOT_TOTAL_ONSCREEN) {
                if(shotActive[i]) {
                    shotFree(i);
                }
                i++;
            }
        } else if(playerDieTime == 120) {
            playerDieTime = 0;
            playerTime = 0;

            DrawMap(0, 13, gfxMapLongBlank);
            playerDraw();
            locationDraw(playerLocation, playerLastLocation, playerLocationTime);
            locationShowAll(playerLocation);
            return;
        }

        playerDieTime++;
    }
}

void playerKill() {
    playerDieTime = 1;
}

void playerAddScore(u16 score) {
    if(playerScore < 10000000) {
        playerScore += score;
        PrintLong(7, 1, playerScore);

        if(score >= playerToNext) {
            if(playerLives < 255) {
                playerLives++;
                if(playerLives <= 6) {
                    DrawMap(playerLives - 2, 2, gfxLife);
                }
            }

            if(playerFlash < 255) {
                playerFlash++;
                PrintByte(29, 4, playerFlash, 0);
            }

            playerToNext += 80000;
        }
        playerToNext -= score;

        if(playerScore > machineHi) {
            machineHi = playerScore;
            PrintLong(29, 1, machineHi);
        }
    }
}

//Shoot!
void playerFire() {
    shotInitPlayer();
}

//Check if all shots are free
u8 playerCheckAllShotsFree() {
    u8 i = 0;
    while(i < SHOT_PLAYER_COUNT) {
        if(shotActive[i]) {
            return 0;
        }
        i++;
    }

    return 1;
}

//Drawing function-sections
void playerDraw() {
    if(playerDieTime > 0) {
        switch(playerDieTime) {
            case 1:
                DrawMap(PLAYER_X, PLAYER_Y, gfxPlayerDieA);
                break;
            case 5:
                DrawMap(PLAYER_X, PLAYER_Y, gfxPlayerDieB);
                break;
            case 9:
                DrawMap(PLAYER_X, PLAYER_Y, gfxPlayerDieC);
                break;
            case 13:
                DrawMap(PLAYER_X, PLAYER_Y, gfxPlayerDieD);
                break;
            default:
                DrawMap(PLAYER_X, PLAYER_Y, gfxMapBlank16);
        }
        return;
    }

    if(playerTime < 4) {
        DrawMap(PLAYER_X, PLAYER_Y, gfxPlayerA);
    } else {
        DrawMap(PLAYER_X, PLAYER_Y, gfxPlayerB);
    }
}

void playerDrawStats() {

}
