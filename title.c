#include "title.h"

u16 titleTime;
u8 titleLastCredits;

const char sectorStr[] PROGMEM = "SECTOR";
const char copyStr[] PROGMEM = "@2016 ARXENGINE";
const char barkyStr1[] PROGMEM = "DESIGN, PROGRAM AND MEDIA";
const char barkyStr2[] PROGMEM = "BY MARC \"BARKY\" MARTA";
const char pressStartStr[] PROGMEM = "PRESS  START";
const char insertCoinStr[] PROGMEM = "INSERT  COIN";

const char blankStr[] PROGMEM = "        ";

const char instructionScene1Str1[] PROGMEM = "   YOU ARE THE HEX-FIGHTER!   ";
const char instructionScene1Str2[] PROGMEM = "  YOU NAVIGATE THE 6 SECTORS  ";
const char instructionScene1Str3[] PROGMEM = "   BY MOVING LEFT AND RIGHT   ";
const char instructionScene1Str4[] PROGMEM = "  AND FIRING WITH THE BUTTON. ";

const char instructionScene2Str1[] PROGMEM = " VIRAL THREATS WILL COME OUT  ";
const char instructionScene2Str2[] PROGMEM = "   OF EACH SECTOR, AND MUST   ";
const char instructionScene2Str3[] PROGMEM = "   BE DESTROYED BEFORE THEY   ";
const char instructionScene2Str4[] PROGMEM = " REACH THE EDGE OF THE FIELD. ";

const char instructionScene3Str1[] PROGMEM = "  BEWARE OF THE ANGRY VIRUS!  ";
const char instructionScene3Str2[] PROGMEM = "THEY CROSS OVER AND ARE FAST. ";
const char instructionScene3Str3[] PROGMEM = " YOU CAN KILL ALL VIRUSES ON  ";
const char instructionScene3Str4[] PROGMEM = "SCREEN WITH THE FLASH BUTTON. ";

const char instructionScene4Str1[] PROGMEM = " YOU CAN SEE WHICH SECTOR YOU ";
const char instructionScene4Str2[] PROGMEM = "    ARE IN WITH THIS GUIDE.   ";
const char instructionScene4Str3[] PROGMEM = " YOU CAN CROSS AT THE EDGES.  ";
const char instructionScene4Str4[] PROGMEM = " SHOTS VANISH WHEN YOU LEAVE. ";

void titleUpdate() {
    u8 modTime = titleTime % 80, hookTime;
    if(titleTime < 1495) {
        switch(titleTime) {
            //0-534 are for the actual title
            case 0:
                DrawMap(0, 2, gfxMapTitleBlank);
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
                Print(2, 19, barkyStr1);
                Print(4, 20, barkyStr2);
                break;
            //535- is for instructions
            case 535:
                DrawMap(0, 2, gfxMapTitleBlank);
                DrawMap(14, 5, gfxPlayerBare);
                Print(0, 8, instructionScene1Str1);
                Print(0, 9, instructionScene1Str2);
                Print(0, 10, instructionScene1Str3);
                Print(0, 11, instructionScene1Str4);
                break;
            case 775:
                DrawMap(0, 2, gfxMapTitleBlank);
                DrawMap(9, 5, gfxVirusCloseGreen);
                DrawMap(11, 5, gfxVirusCloseBlue);
                DrawMap(13, 5, gfxVirusCloseRed);
                DrawMap(15, 5, gfxVirusCloseYellow);
                DrawMap(17, 5, gfxVirusClosePurple);
                DrawMap(19, 5, gfxVirusCloseCyan);
                Print(0, 8, instructionScene2Str1);
                Print(0, 9, instructionScene2Str2);
                Print(0, 10, instructionScene2Str3);
                Print(0, 11, instructionScene2Str4);
                break;
            case 1015:
                DrawMap(0, 2, gfxMapTitleBlank);
                DrawMap(14, 5, gfxVirusCloseAngry);
                Print(0, 8, instructionScene3Str1);
                Print(0, 9, instructionScene3Str2);
                Print(0, 10, instructionScene3Str3);
                Print(0, 11, instructionScene3Str4);
                break;
            case 1255:
                DrawMap(0, 2, gfxMapTitleBlank);
                DrawMap(12, 5, gfxBlockGreen);
                DrawMap(13, 5, gfxBlockBlue);
                DrawMap(14, 5, gfxBlockRed);
                DrawMap(15, 5, gfxBlockYellow);
                DrawMap(16, 5, gfxBlockPurple);
                DrawMap(17, 5, gfxBlockCyan);
                DrawMap(12, 6, gfxArrow);
                Print(0, 8, instructionScene4Str1);
                Print(0, 9, instructionScene4Str2);
                Print(0, 10, instructionScene4Str3);
                Print(0, 11, instructionScene4Str4);
                break;
            case 1285:
                DrawMap(12, 6, gfxMapBlank8);
                DrawMap(13, 6, gfxArrow);
                break;
            case 1315:
                DrawMap(13, 6, gfxMapBlank8);
                DrawMap(14, 6, gfxArrow);
                break;
            case 1345:
                DrawMap(14, 6, gfxMapBlank8);
                DrawMap(15, 6, gfxArrow);
                break;
            case 1375:
                DrawMap(15, 6, gfxMapBlank8);
                DrawMap(16, 6, gfxArrow);
                break;
            case 1405:
                DrawMap(16, 6, gfxMapBlank8);
                DrawMap(17, 6, gfxArrow);
                break;
            case 1435:
                DrawMap(17, 6, gfxMapBlank8);
                DrawMap(12, 6, gfxArrow);
                break;
        }

        if(titleLastCredits < machineCredits) {
            titleTime = 175;
            DrawMap(0, 2, gfxMapTitleBlank);
            DrawMap(11, 9, gfxLogoH);
            DrawMap(13, 8, gfxLogoE);
            DrawMap(17, 9, gfxLogoX);
            Print(12, 14, sectorStr);
            Print(7, 17, copyStr);
            Print(2, 19, barkyStr1);
            Print(4, 20, barkyStr2);
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
    } else {
        //Ship coming down!
        hookTime = titleTime - 1700;
        if(hookTime < 50) {
            if(hookTime == 0) {
                DrawMap(0, 2, gfxMapTitleBlank);
                DrawMap(0, 23, gfxMapLongBlank);
            } else {
                DrawMap(PLAYER_X, (hookTime >> 1) - 1, gfxWire);
            }
            DrawMap(PLAYER_X, hookTime >> 1, gfxPlayerHook);

        } else {
            if(hookTime == 50) {
                DrawMap(PLAYER_X, PLAYER_Y, gfxPlayerBare);
            } else if(hookTime > 51) {
                if(hookTime > 53) {
                    Print(11, ((100 - hookTime) >> 1) + 1, blankStr);
                }
                DrawMap(PLAYER_X, (100 - hookTime) >> 1, gfxHook);
            }
        }
    }

    titleLastCredits = machineCredits;

    titleTime++;
    if(titleTime == 1495) {
        titleTime = 0;
    }
}

void titleReset() {
    titleTime = 0;
    Print(0, 0, blankStr);
    Print(0, 1, blankStr);
}
