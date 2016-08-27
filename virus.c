#include "virus.h"

u8 virusY[VIRUS_POOL_TOTAL], virusTime[VIRUS_POOL_TOTAL], virusLocation[VIRUS_POOL_TOTAL], virusDieTime[VIRUS_POOL_TOTAL];
u8 virusActive[VIRUS_POOL_TOTAL];
u8 virusNextMoveTime[VIRUS_POOL_TOTAL];

void virusDraw(u8);
void virusErase(u8);

//Create a new virus
void virusInit(u8 loc) {
	u8 i = 0;
	while(i < VIRUS_POOL_TOTAL) {
		if(!virusActive[i]) {
			virusY[i] = BG_Y;
			virusTime[i] = 0;
			virusLocation[i] = loc;
			virusNextMoveTime[i] = VIRUS_NEXT_MOVE_START;
			virusActive[i] = 1;
			virusDieTime[i] = 0;
			virusDraw(i);
			return;
		}

		i++;
	}
}

void virusUpdate(u8 i) {
	if(!virusActive[i]) {
		return;
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
		virusNextMoveTime[i]--;
		
		if(virusY[i] <= 10) {
			locationSetMaxIntensity(virusLocation[i], 1);
		} else if(virusY[i] <= 14) {
			locationSetMaxIntensity(virusLocation[i], 2);
		} else {
			locationSetMaxIntensity(virusLocation[i], 3);
		}

		//Virus too close? Kill the player
		if(virusY[i] >= PLAYER_Y - 2) {
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
