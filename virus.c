#include "virus.h"

u8 virusY[VIRUS_POOL_TOTAL], virusTime[VIRUS_POOL_TOTAL], virusLocation[VIRUS_POOL_TOTAL];
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

	virusTime[i]++;
	if(virusTime[i] == virusNextMoveTime[i]) {
		virusTime[i] = 0;

		//Erase previous virus stuff (if same loc)
		if(virusLocation[i] == playerLocation) {
			virusErase(i);
		}

		virusY[i]++;
		if(virusY[i] > 11) {
			virusNextMoveTime[i] -= 2;
		}

		//Virus too close? Eliminate it
		if(virusY[i] >= PLAYER_Y - 2) {
			virusActive[i] = 0;
			virusErase(i);
		} else if(virusLocation[i] == playerLocation) {
			//Draw new virus (if same loc)
			virusDraw(i);
		}
	}
}

void virusDestroy(u8 i) {
	virusErase(i);
	virusActive[i] = 0;
}

void virusErase(u8 i) {
	DrawMap(VIRUS_X, virusY[i], gfxMapBlank16);
}

void virusDraw(u8 i) {
	if(!virusActive[i] || virusLocation[i] != playerLocation || playerLocationTime > 0) {
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
