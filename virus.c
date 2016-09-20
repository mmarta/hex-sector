#include "virus.h"

u8 virusY[VIRUS_POOL_TOTAL], virusTime[VIRUS_POOL_TOTAL],
    virusLocation[VIRUS_POOL_TOTAL], virusDieTime[VIRUS_POOL_TOTAL];

u8 virusActive[VIRUS_POOL_TOTAL];
u8 virusIsAngry[VIRUS_POOL_TOTAL];
u8 virusNextMoveTime[VIRUS_POOL_TOTAL];

void virusDraw(u8);
void virusErase(u8);

//Create a new virus
u8 virusInit(u8 loc, u8 isAngry) {
    u8 i = 0;
    while(i < VIRUS_POOL_TOTAL) {
        if(!virusActive[i]) {
            virusY[i] = BG_Y;
            virusTime[i] = 0;
            virusLocation[i] = loc;
            virusNextMoveTime[i] = VIRUS_NEXT_MOVE_START;
            virusIsAngry[i] = isAngry;
            virusActive[i] = 1;
            virusDieTime[i] = 0;
            virusDraw(i);
            return 1;
        }

        i++;
    }
    
    return 0;
}

void virusUpdate(u8 i, u8 stage) {
    u8 angerFactor, shotFactor;
    
    if(!virusActive[i]) {
        return;
    }
    
    //Set anger factor & shot factors
    angerFactor = (stage >= VIRUS_ANGRY_FAST_STAGE) ? VIRUS_ANGRY_FAST_FACTOR : VIRUS_ANGRY_SLOW_FACTOR;
    if(stage >= VIRUS_SHOT_HOT_STAGE) {
        shotFactor = VIRUS_SHOT_HOT_FACTOR;
    } else if(stage >= VIRUS_SHOT_MEDIUM_STAGE) {
        shotFactor = VIRUS_SHOT_MEDIUM_FACTOR;
    } else {
        shotFactor = VIRUS_SHOT_MILD_FACTOR;
    }

    //Always erase/redraw if need be
    if(playerRedrawTick) {
        //Redraw on location change completion tick
        if(playerLocationTime > 0) {
            virusErase(i);
        } else {
            virusDraw(i);
        }
    }

    if(virusDieTime[i] > 0) {
        if(virusDieTime[i] <= 16) {
            switch(virusDieTime[i]) {
                case 1:
                case 5:
                case 9:
                case 13:
                    virusDraw(i);
            }
        } else if(virusDieTime[i] > 16) {
            virusDieTime[i] = 0;
            virusActive[i] = 0;
            virusErase(i);
        }

        virusDieTime[i]++;
        return;
    }

    virusTime[i]++;
    if(virusTime[i] == virusNextMoveTime[i]) {
        virusTime[i] = 0;

        //Erase previous virus stuff (if same loc)
        if(virusLocation[i] == playerLocation) {
            virusErase(i);
        }

        virusY[i]++;
        if(virusNextMoveTime[i] >= 5) {
            if(stage >= VIRUS_HIGH_SPEED_STAGE) {
                virusNextMoveTime[i] -= 2;
            } else if(stage >= VIRUS_MEDIUM_SPEED_STAGE && virusNextMoveTime[i] % 4 == 0) {
                virusNextMoveTime[i] -= 2;
            } else {
                virusNextMoveTime[i] -= 1;
            }
        }
        
        //Angry virus specific stuff
        if(virusIsAngry[i] && virusY[i] % angerFactor == 0) {
            //Clear the current threat before moving.
            locationClearThreat(virusLocation[i]);
            
            if(rand() % 2) {
                virusLocation[i] = virusLocation[i] + 1;
                if(virusLocation[i] == 6) {
                    virusLocation[i] = LOCATION_GREEN;
                }
            } else {
                virusLocation[i] = virusLocation[i] - 1;
                if(virusLocation[i] == 255) {
                    virusLocation[i] = LOCATION_CYAN;
                }
            }
        }
        
        //Shoot?
        if(!(rand() % shotFactor) && virusLocation[i] == playerLocation && playerLocationTime == 0 && virusY[i] <= 12) {
            shotInitViral(virusY[i] << 3);
        }
        
        if(virusY[i] <= 12) {
            locationSetMaxIntensity(virusLocation[i], 1, virusIsAngry[i]);
        } else if(virusY[i] <= 16) {
            locationSetMaxIntensity(virusLocation[i], 2, virusIsAngry[i]);
        } else {
            locationSetMaxIntensity(virusLocation[i], 3, virusIsAngry[i]);
        }

        //Virus too close? Kill the player
        if(virusY[i] >= PLAYER_Y - 1) {
            playerKill();
        } else if(virusLocation[i] == playerLocation) {
            //Draw new virus (if same loc)
            virusDraw(i);
        }
    }
}

void virusDestroy(u8 i) {
    virusDieTime[i] = 1;
    locationClearThreat(virusLocation[i]);
}

void virusErase(u8 i) {
    DrawMap(VIRUS_X, virusY[i], gfxMapBlank16);
}

void virusDraw(u8 i) {
    if(!virusActive[i] || virusLocation[i] != playerLocation || playerLocationTime > 0) {
        return;
    }

    if(virusDieTime[i] > 0) {
        switch(virusDieTime[i]) {
            case 1:
                DrawMap(VIRUS_X, virusY[i], gfxVirusDieA);
                break;
            case 5:
                DrawMap(VIRUS_X, virusY[i], gfxVirusDieB);
                break;
            case 9:
                DrawMap(VIRUS_X, virusY[i], gfxVirusDieC);
                break;
            default:
                DrawMap(VIRUS_X, virusY[i], gfxVirusDieD);
        }
        return;
    }
    
    //Angry Virus????
    if(virusIsAngry[i]) {
        DrawMap(VIRUS_X, virusY[i], gfxVirusCloseAngry);
        return;
    }

    switch(virusLocation[i]) {
        case LOCATION_GREEN:
            DrawMap(VIRUS_X, virusY[i], gfxVirusCloseGreen);
            break;
        case LOCATION_BLUE:
            DrawMap(VIRUS_X, virusY[i], gfxVirusCloseBlue);
            break;
        case LOCATION_RED:
            DrawMap(VIRUS_X, virusY[i], gfxVirusCloseRed);
            break;
        case LOCATION_YELLOW:
            DrawMap(VIRUS_X, virusY[i], gfxVirusCloseYellow);
            break;
        case LOCATION_PURPLE:
            DrawMap(VIRUS_X, virusY[i], gfxVirusClosePurple);
            break;
        case LOCATION_CYAN:
            DrawMap(VIRUS_X, virusY[i], gfxVirusCloseCyan);
            break;
    }
}
