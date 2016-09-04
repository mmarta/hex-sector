#include "location.h"

const char leftArrowString[] PROGMEM = "<";
const char rightArrowString[] PROGMEM = ">";

u8 locationIntensity[LOCATION_COUNT];
u8 locationTime[LOCATION_COUNT];
u8 locationAngry[LOCATION_COUNT];

void locationDrawBlock(u8);

void locationUpdate(u8 i) {
    switch(locationIntensity[i]) {
        case 0:
            return;
        default:
            locationTime[i] += (1 << locationIntensity[i]);
    }

    locationTime[i]++;
    if(locationTime[i] >= 64) {
        locationTime[i] = 0;
    }

    if(locationTime[i] < 32) {
        DrawMap(12 + i, PLAYER_Y + 3, gfxMapBlank8);
    } else {
        if(locationAngry[i]) {
            DrawMap(12 + i, PLAYER_Y + 3, gfxBlockAngry);
        } else {
            locationDrawBlock(i);
        }
    }
}

//Draw full location
void locationDraw(u8 playerLocation, u8 playerLastLocation, u8 playerLocationTime) {
    u8 i = 0;

    const char *leftMap, *rightMap;
    u8 isRight = 0;

    if(playerLocationTime == 0) {
        DrawMap(0, BG_Y, gfxMapBigBlank);
        DrawMap(22, BG_Y, gfxMapBigBlank);

        //Draw two of the same view map
        switch(playerLocation) {
            case LOCATION_GREEN:
                leftMap = gfxBorderGreenLeft;
                rightMap = gfxBorderGreenRight;
                break;
            case LOCATION_BLUE:
                leftMap = gfxBorderBlueLeft;
                rightMap = gfxBorderBlueRight;
                break;
            case LOCATION_RED:
                leftMap = gfxBorderRedLeft;
                rightMap = gfxBorderRedRight;
                break;
            case LOCATION_YELLOW:
                leftMap = gfxBorderYellowLeft;
                rightMap = gfxBorderYellowRight;
                break;
            case LOCATION_PURPLE:
                leftMap = gfxBorderPurpleLeft;
                rightMap = gfxBorderPurpleRight;
                break;
            default:
                leftMap = gfxBorderCyanLeft;
                rightMap = gfxBorderCyanRight;
        }
    } else if(playerLocationTime == 2) {
        //Draw one map in one color, and the other in the previous
        DrawMap(6, BG_Y, gfxMapBigBlank);
        DrawMap(16, BG_Y, gfxMapBigBlank);

        DrawMap(1, PLAYER_Y + 2, gfxMapBlank8);
        DrawMap(28, PLAYER_Y + 2, gfxMapBlank8);

        switch(playerLocation) {
            case LOCATION_GREEN:
                if(playerLastLocation == LOCATION_CYAN) {
                    rightMap = gfxBorderCyanRight;
                    isRight = 1;
                } else {
                    leftMap = gfxBorderBlueLeft;
                }
                break;
            case LOCATION_BLUE:
                if(playerLastLocation == LOCATION_GREEN) {
                    rightMap = gfxBorderGreenRight;
                    isRight = 1;
                } else {
                    leftMap = gfxBorderRedLeft;
                }
                break;
            case LOCATION_RED:
                if(playerLastLocation == LOCATION_BLUE) {
                    rightMap = gfxBorderBlueRight;
                    isRight = 1;
                } else {
                    leftMap = gfxBorderYellowLeft;
                }
                break;
            case LOCATION_YELLOW:
                if(playerLastLocation == LOCATION_RED) {
                    rightMap = gfxBorderRedRight;
                    isRight = 1;
                } else {
                    leftMap = gfxBorderPurpleLeft;
                }
                break;
            case LOCATION_PURPLE:
                if(playerLastLocation == LOCATION_YELLOW) {
                    rightMap = gfxBorderYellowRight;
                    isRight = 1;
                } else {
                    leftMap = gfxBorderCyanLeft;
                }
                break;
            default:
                if(playerLastLocation == LOCATION_PURPLE) {
                    rightMap = gfxBorderPurpleRight;
                    isRight = 1;
                } else {
                    leftMap = gfxBorderGreenLeft;
                }
        }
    } else {
        //Draw one map in one color, and the other in the previous
        DrawMap(0, BG_Y, gfxMapBigBlank);
        DrawMap(22, BG_Y, gfxMapBigBlank);

        switch(playerLocation) {
            case LOCATION_GREEN:
                if(playerLastLocation == LOCATION_CYAN) {
                    leftMap = gfxBorderGreenLeft;
                } else {
                    rightMap = gfxBorderGreenRight;
                    isRight = 1;
                }
                break;
            case LOCATION_BLUE:
                if(playerLastLocation == LOCATION_GREEN) {
                    leftMap = gfxBorderBlueLeft;
                } else {
                    rightMap = gfxBorderBlueRight;
                    isRight = 1;
                }
                break;
            case LOCATION_RED:
                if(playerLastLocation == LOCATION_BLUE) {
                    leftMap = gfxBorderRedLeft;
                } else {
                    rightMap = gfxBorderRedRight;
                    isRight = 1;
                }
                break;
            case LOCATION_YELLOW:
                if(playerLastLocation == LOCATION_RED) {
                    leftMap = gfxBorderYellowLeft;
                } else {
                    rightMap = gfxBorderYellowRight;
                    isRight = 1;
                }
                break;
            case LOCATION_PURPLE:
                if(playerLastLocation == LOCATION_YELLOW) {
                    leftMap = gfxBorderPurpleLeft;
                } else {
                    rightMap = gfxBorderPurpleRight;
                    isRight = 1;
                }
                break;
            default:
                if(playerLastLocation == LOCATION_PURPLE) {
                    leftMap = gfxBorderCyanLeft;
                } else {
                    rightMap = gfxBorderCyanRight;
                    isRight = 1;
                }
        }
    }

    //Draw all the location tiles
    if(playerLocationTime > 0) {
        i = 0;
        if(isRight) {
            while(i < 8) {
                DrawMap(0 + i, BG_Y + (i << 1), rightMap);
                i++;
            }
        } else {
            while(i < 8) {
                DrawMap(29 - i, BG_Y + (i << 1), leftMap);
                i++;
            }
        }
    } else {
        i = 0;
        while(i < 8) {
            DrawMap(13 - i, BG_Y + (i << 1), leftMap);
            DrawMap(16 + i, BG_Y + (i << 1), rightMap);
            i++;
        }

        Print(1, PLAYER_Y + 2, leftArrowString);
        Print(28, PLAYER_Y + 2, rightArrowString);
    }
}

void locationClear() {
    DrawMap(0, BG_Y, gfxMapBigBlank);
    DrawMap(8, BG_Y, gfxMapBigBlank);
    DrawMap(16, BG_Y, gfxMapBigBlank);
    DrawMap(22, BG_Y, gfxMapBigBlank);

    DrawMap(0, PLAYER_Y + 2, gfxMapLongBlank);
}

void locationClearThreat(u8 location) {
    locationIntensity[location] = 0;
    locationTime[location] = 0;
    locationAngry[location] = 0;
    locationDrawBlock(location);
}

void locationShowAll(u8 playerLocation) {
    DrawMap(12, PLAYER_Y + 3, gfxBlockGreen);
    DrawMap(13, PLAYER_Y + 3, gfxBlockBlue);
    DrawMap(14, PLAYER_Y + 3, gfxBlockRed);
    DrawMap(15, PLAYER_Y + 3, gfxBlockYellow);
    DrawMap(16, PLAYER_Y + 3, gfxBlockPurple);
    DrawMap(17, PLAYER_Y + 3, gfxBlockCyan);

    DrawMap(12 + playerLocation, PLAYER_Y + 4, gfxArrow);
}

void locationMoveArrow(u8 playerLocation) {
    u8 xVal = playerLocation + 12;
    switch(playerLocation) {
        case LOCATION_GREEN:
            DrawMap(xVal + 5, PLAYER_Y + 4, gfxMapBlank8);
            DrawMap(xVal + 1, PLAYER_Y + 4, gfxMapBlank8);
            break;
        case LOCATION_CYAN:
            DrawMap(xVal - 5, PLAYER_Y + 4, gfxMapBlank8);
            DrawMap(xVal - 1, PLAYER_Y + 4, gfxMapBlank8);
            break;
        default:
            DrawMap(xVal + 1, PLAYER_Y + 4, gfxMapBlank8);
            DrawMap(xVal - 1, PLAYER_Y + 4, gfxMapBlank8);
    }

    DrawMap(xVal, PLAYER_Y + 4, gfxArrow);
}

void locationSetMaxIntensity(u8 location, u8 intensity, u8 isAngry) {
    if(locationIntensity[location] < intensity) {
        locationIntensity[location] = intensity;
        locationTime[location] = 0;
    }
    locationAngry[location] = isAngry;
}

void locationDrawBlock(u8 location) {
    switch(location) {
        case LOCATION_GREEN:
            DrawMap(12, PLAYER_Y + 3, gfxBlockGreen);
            break;
        case LOCATION_BLUE:
            DrawMap(13, PLAYER_Y + 3, gfxBlockBlue);
            break;
        case LOCATION_RED:
            DrawMap(14, PLAYER_Y + 3, gfxBlockRed);
            break;
        case LOCATION_YELLOW:
            DrawMap(15, PLAYER_Y + 3, gfxBlockYellow);
            break;
        case LOCATION_PURPLE:
            DrawMap(16, PLAYER_Y + 3, gfxBlockPurple);
            break;
        default:
            DrawMap(17, PLAYER_Y + 3, gfxBlockCyan);
    }
}
