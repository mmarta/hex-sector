#include "game.h"

u8 gameStage;
u8 gameVirusesTotal, gameKillCount, gameEnqueued;
u8 gameVirusExtFactor, gameVirusCurrentFactor;
u8 gameReadyStageTime = 0;
const char virusString[] PROGMEM = "VIRAL THREATS";
const char levelString[] PROGMEM = "LV=";

const char challengeStringTop[] PROGMEM = "ARE YOU READY FOR";
const char challengeStringBottom[] PROGMEM = "THE NEXT CHALLENGE?";

void gameStageStart();
void gameStageSetFactors();
void gameStageUp();
void gameRunAllCollisions();
u8 gameCheckCollision(u8, u8, u8, u8);
u8 gameIsCurrentlyPlaying();
u8 gameIsReadyTick();

void gameStart() {
    gameStage = 1;
    gameStageStart();
    gameStageSetFactors();
    playerStart();
}

void gameUpdate() {
    u8 i, readyNextLevel = 1;
    
    if(gameIsCurrentlyPlaying() && playerLives == 0) {
        machineTitleMode = 1;
        return;
    }

    if(gameIsCurrentlyPlaying()) {
        playerInput();
        playerUpdate();
        
        //Check collisions first
        gameRunAllCollisions();
        
        //Any viruses to initialize?
        if(!(rand() % gameVirusCurrentFactor)) {
            if(gameEnqueued < gameVirusesTotal) {
                gameEnqueued += vQueueEnqueue(rand() % 6, rand() % 90, gameStage >= VIRUS_ANGRY_SLOW_STAGE ? 1 : 0);
            }
        }
        
        vQueueCycle();
        
        i = 0;
        //Start looking to go to the next level?
        if(gameKillCount < gameVirusesTotal) {
            readyNextLevel = 0;
        }
        while(i < VIRUS_POOL_TOTAL) {
            virusUpdate(i, gameStage);
            if(readyNextLevel) {
                if(virusActive[i]) { //Last enemmy destroyed fully?
                    readyNextLevel = 0;
                }
            }
            i++;
        }
        playerRedrawTick = 0;
    
        //Update locations next
        i = 0;
        while(i < LOCATION_COUNT) {
            locationUpdate(i);
            i++;
        }
    
        //Sprite updates come next
        i = 0;
        while(i < SHOT_TOTAL_ONSCREEN) {
            shotUpdate(i);
            i++;
        }
        
        if(readyNextLevel) {
            gameReadyStageTime = 1;
        }
    } else if(gameIsReadyTick()) {
        playerUpdate();
        
        //Clear all viruses
        i = 0;
        while(i < VIRUS_POOL_TOTAL) {
            virusActive[i] = 0;
            i++;
        }
        
        //Clear bottom threats counter
        i = 0;
        while(i < LOCATION_COUNT) {
            locationClearThreat(i);
            i++;
        }
        
        //Restart
        gameStageStart();
    } else if(gameReadyStageTime > 0) {
        if(gameReadyStageTime == 1) {
            i = 0;
            while(i < SHOT_TOTAL_ONSCREEN) {
                shotFree(i);
                i++;
            }
            
            locationClear(); //Clear all
            DrawMap(PLAYER_X, PLAYER_Y, gfxMapBlank16);

            Print(6, 12, challengeStringTop);
            Print(5, 14, challengeStringBottom);
            gameReadyStageTime++;
        } else if(gameReadyStageTime == 90) {
            gameStageUp();
        } else {
            gameReadyStageTime++;
        }
    } else {
        playerUpdate();
    }
}

void gameStageStart() {
    //How many enemies?
    if(gameStage <= 2) {
        gameVirusesTotal = 10;
    } else if(gameStage <= 4) {
        gameVirusesTotal = 15;
    } else if(gameStage <= 7) {
        gameVirusesTotal = 20;
    } else {
        gameVirusesTotal = 25;
    }
    
    gameKillCount = 0;
    gameReadyStageTime = 0;
    gameEnqueued = 0;
        
    //Clear virus queue
    vQueueClear();
    
    Print(14, 3, virusString);
    PrintByte(29, 3, gameVirusesTotal, 0);
    Print(0, 3, levelString);
    PrintByte(5, 3, gameStage, 0);
}

void gameStageSetFactors() {
    //More linear difficulty curve
    if(gameStage == 1) {
        gameVirusExtFactor = VIRUS_STARTING_FACTOR / 2;
    } else if(gameVirusExtFactor - 7 > gameVirusExtFactor) {
        gameVirusExtFactor = 0;
    } else {
        gameVirusExtFactor -= 7;
    }
    gameVirusCurrentFactor = (VIRUS_STARTING_FACTOR / 2) + gameVirusExtFactor;
}

void gameStageUp() {
    if(gameStage < 255) {
        gameStage++;
    }
    
    playerTime = 7;
            
    playerLocation = LOCATION_GREEN;
    playerLocationTime = 0;
    DrawMap(0, 12, gfxMapLongBlank);
    DrawMap(0, 14, gfxMapLongBlank);
    locationDraw(playerLocation, LOCATION_GREEN, playerLocationTime);
    locationShowAll(playerLocation);
    gameStageStart();
    gameStageSetFactors();
}

//Runs through all collisions
void gameRunAllCollisions() {
    u8 i, j;

    i = 0;
    while(i < VIRUS_POOL_TOTAL) {
        if(!virusActive[i] || playerLocation != virusLocation[i] || virusDieTime[i] > 0) {
            i++;
            continue;
        }

        j = 0;
        while(j < SHOT_PLAYER_COUNT) {
            if(!shotActive[j]) {
                j++;
                continue;
            }

            if(gameCheckCollision(virusY[i] << 3, VIRUS_HEIGHT, shotY[j], SHOT_HEIGHT)) {
                shotFree(j);
                virusDestroy(i);
                if(virusY[i] <= 10) {
                    playerAddScore(400);
                } else if(virusY[i] <= 14) {
                    playerAddScore(800);
                } else {
                    playerAddScore(1600);
                }
                gameKillCount++;
                //TODO: Find issue with underflow
                if(gameKillCount > gameVirusesTotal) {
                    gameKillCount = gameVirusesTotal;
                }
                PrintByte(29, 3, gameVirusesTotal - gameKillCount, 0);
            }
            j++;
        }
        i++;
    }
    
    //Check to see if viral shot kills player
    i = SHOT_VIRAL_COUNT + SHOT_VIRAL_START;
    while(i-- > SHOT_VIRAL_START) {
        if(shotIsViral[i] && shotY[i] > (PLAYER_Y - 1) << 3 && shotActive[i]) {
            playerKill();
            break;
        }
    }
}

//checks a single collision
u8 gameCheckCollision(u8 y1, u8 h1, u8 y2, u8 h2) {
    if(y1 + h1 >= y2 && y1 < y2 + h2) {
        return 1;
    }

    return 0;
}

//Checks to see if player is currently active and in playfield
u8 gameIsCurrentlyPlaying() {
    return playerDieTime == 0 && gameReadyStageTime == 0;
}

u8 gameIsReadyTick() {
    return playerDieTime == 30;
}
