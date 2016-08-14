#include "player.h"

u8 playerLocation, playerLives, playerTime, playerDieTime;
unsigned long playerScore;
u8 playerRedrawTick = 0;

//Internal vars
u8 playerLastLocation, playerLocationTime;
u8 playerLeftB, playerRightB, playerFireB;

const char scoreString[] PROGMEM = "SCORE";

const char sectorString[] PROGMEM = "SECTOR";
const char leftArrowString[] PROGMEM = "<";
const char rightArrowString[] PROGMEM = ">";
const char greenString[] PROGMEM = "GREEN";
const char blueString[] PROGMEM = "BLUE";
const char redString[] PROGMEM = "RED";
const char yellowString[] PROGMEM = "YELLOW";
const char purpleString[] PROGMEM = "PURPLE";
const char cyanString[] PROGMEM = "CYAN";

void playerFire();
void playerDraw();
void playerDrawLocation();
void playerDrawStats();
u8 playerCheckAllShotsFree();

void playerStart() {
	playerLocation = LOCATION_GREEN;
	playerLives = 3;
	playerTime = 0;
	playerDieTime = 0;

	playerLeftB = 0;
	playerRightB = 0;
	playerFireB = 0;

	playerLocationTime = 0;

	playerScore = 0;

	playerDrawLocation();
	playerDraw();
	Print(0, 0, scoreString);
	playerDrawStats();
}

void playerInput() {
	u8 i = SHOT_TOTAL >> 1;
	unsigned int pad = ReadJoypad(0);

	if(pad & BTN_LEFT) {
		if(!playerLeftB && playerLocationTime == 0 && playerCheckAllShotsFree()) {
			playerLastLocation = playerLocation;
			playerLocation--;
			playerLocationTime = 1;
			playerRedrawTick = 1;
			if(playerLocation == 255) {
				playerLocation = LOCATION_CYAN;
			}

			while(i--) {
				shotFree(i);
			}

			playerLeftB = 1;
		}
	} else {
		playerLeftB = 0;
	}

	if(pad & BTN_RIGHT) {
		if(!playerRightB && playerLocationTime == 0 && playerCheckAllShotsFree()) {
			playerLastLocation = playerLocation;
			playerLocation++;
			playerLocationTime = 1;
			playerRedrawTick = 1;
			if(playerLocation == 6) {
				playerLocation = LOCATION_GREEN;
			}

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
}

void playerUpdate() {
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
				playerDrawLocation();
			} else if(playerLocationTime >= 14) {
				playerLocationTime = 0;
				playerRedrawTick = 1;
				playerDrawLocation();
			}
		}
	}
}

void playerAddScore(u16 score) {
	playerScore += score;
	PrintLong(7, 1, playerScore);
}

//Shoot!
void playerFire() {
	shotInit();
}

//Check if all shots are free
u8 playerCheckAllShotsFree() {
	u8 i = 0;
	while(i < SHOT_TOTAL >> 1) {
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
		return;
	}

	if(playerTime < 4) {
		DrawMap(PLAYER_X, PLAYER_Y, gfxPlayerA);
	} else {
		DrawMap(PLAYER_X, PLAYER_Y, gfxPlayerB);
	}
}

void playerDrawStats() {
	PrintLong(7, 1, playerScore);
}

void playerDrawLocation() {
	if(playerLocationTime == 0) {
		DrawMap(1, BG_Y, gfxMapBigBlank);
		DrawMap(23, BG_Y, gfxMapBigBlank);

		//Draw two of the same view map
		switch(playerLocation) {
			case LOCATION_GREEN:
				DrawMap(11, BG_Y, gfxBorderGreenLeft);
				DrawMap(16, BG_Y, gfxBorderGreenRight);
				DrawMap(8, BG_Y + 8, gfxBorderGreenLeft);
				DrawMap(19, BG_Y + 8, gfxBorderGreenRight);

				Print(9, PLAYER_Y + 3, greenString);
				Print(15, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, cyanString);
				Print(23, PLAYER_Y + 2, blueString);
				break;
			case LOCATION_BLUE:
				DrawMap(11, BG_Y, gfxBorderBlueLeft);
				DrawMap(16, BG_Y, gfxBorderBlueRight);
				DrawMap(8, BG_Y + 8, gfxBorderBlueLeft);
				DrawMap(19, BG_Y + 8, gfxBorderBlueRight);

				Print(9, PLAYER_Y + 3, blueString);
				Print(15, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, greenString);
				Print(24, PLAYER_Y + 2, redString);
				break;
			case LOCATION_RED:
				DrawMap(11, BG_Y, gfxBorderRedLeft);
				DrawMap(16, BG_Y, gfxBorderRedRight);
				DrawMap(8, BG_Y + 8, gfxBorderRedLeft);
				DrawMap(19, BG_Y + 8, gfxBorderRedRight);

				Print(10, PLAYER_Y + 3, redString);
				Print(14, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, blueString);
				Print(21, PLAYER_Y + 2, yellowString);
				break;
			case LOCATION_YELLOW:
				DrawMap(11, BG_Y, gfxBorderYellowLeft);
				DrawMap(16, BG_Y, gfxBorderYellowRight);
				DrawMap(8, BG_Y + 8, gfxBorderYellowLeft);
				DrawMap(19, BG_Y + 8, gfxBorderYellowRight);

				Print(8, PLAYER_Y + 3, yellowString);
				Print(16, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, redString);
				Print(21, PLAYER_Y + 2, purpleString);
				break;
			case LOCATION_PURPLE:
				DrawMap(11, BG_Y, gfxBorderPurpleLeft);
				DrawMap(16, BG_Y, gfxBorderPurpleRight);
				DrawMap(8, BG_Y + 8, gfxBorderPurpleLeft);
				DrawMap(19, BG_Y + 8, gfxBorderPurpleRight);

				Print(8, PLAYER_Y + 3, purpleString);
				Print(16, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, yellowString);
				Print(23, PLAYER_Y + 2, cyanString);
				break;
			default:
				DrawMap(11, BG_Y, gfxBorderCyanLeft);
				DrawMap(16, BG_Y, gfxBorderCyanRight);
				DrawMap(8, BG_Y + 8, gfxBorderCyanLeft);
				DrawMap(19, BG_Y + 8, gfxBorderCyanRight);

				Print(9, PLAYER_Y + 3, cyanString);
				Print(15, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, purpleString);
				Print(22, PLAYER_Y + 2, greenString);
		}

		Print(1, PLAYER_Y + 2, leftArrowString);
		Print(28, PLAYER_Y + 2, rightArrowString);
	} else if(playerLocationTime == 2) {
		//Draw one map in one color, and the other in the previous
		DrawMap(8, BG_Y, gfxMapBigBlank);
		DrawMap(16, BG_Y, gfxMapBigBlank);
		DrawMap(0, PLAYER_Y + 2, gfxMapLongBlank);

		switch(playerLocation) {
			case LOCATION_GREEN:
				if(playerLastLocation == LOCATION_CYAN) {
					DrawMap(1, BG_Y, gfxBorderCyanRight);
					DrawMap(4, BG_Y + 8, gfxBorderCyanRight);
				} else {
					DrawMap(26, BG_Y, gfxBorderBlueLeft);
					DrawMap(23, BG_Y + 8, gfxBorderBlueLeft);
				}
				break;
			case LOCATION_BLUE:
				if(playerLastLocation == LOCATION_GREEN) {
					DrawMap(1, BG_Y, gfxBorderGreenRight);
					DrawMap(4, BG_Y + 8, gfxBorderGreenRight);
				} else {
					DrawMap(26, BG_Y, gfxBorderRedLeft);
					DrawMap(23, BG_Y + 8, gfxBorderRedLeft);
				}
				break;
			case LOCATION_RED:
				if(playerLastLocation == LOCATION_BLUE) {
					DrawMap(1, BG_Y, gfxBorderBlueRight);
					DrawMap(4, BG_Y + 8, gfxBorderBlueRight);
				} else {
					DrawMap(26, BG_Y, gfxBorderYellowLeft);
					DrawMap(23, BG_Y + 8, gfxBorderYellowLeft);
				}
				break;
			case LOCATION_YELLOW:
				if(playerLastLocation == LOCATION_RED) {
					DrawMap(1, BG_Y, gfxBorderRedRight);
					DrawMap(4, BG_Y + 8, gfxBorderRedRight);
				} else {
					DrawMap(26, BG_Y, gfxBorderPurpleLeft);
					DrawMap(23, BG_Y + 8, gfxBorderPurpleLeft);
				}
				break;
			case LOCATION_PURPLE:
				if(playerLastLocation == LOCATION_YELLOW) {
					DrawMap(1, BG_Y, gfxBorderYellowRight);
					DrawMap(4, BG_Y + 8, gfxBorderYellowRight);
				} else {
					DrawMap(26, BG_Y, gfxBorderCyanLeft);
					DrawMap(23, BG_Y + 8, gfxBorderCyanLeft);
				}
				break;
			default:
				if(playerLastLocation == LOCATION_PURPLE) {
					DrawMap(1, BG_Y, gfxBorderPurpleRight);
					DrawMap(4, BG_Y + 8, gfxBorderPurpleRight);
				} else {
					DrawMap(26, BG_Y, gfxBorderGreenLeft);
					DrawMap(23, BG_Y + 8, gfxBorderGreenLeft);
				}
		}
	} else {
		//Draw one map in one color, and the other in the previous
		DrawMap(1, BG_Y, gfxMapBigBlank);
		DrawMap(23, BG_Y, gfxMapBigBlank);

		switch(playerLocation) {
			case LOCATION_GREEN:
				if(playerLastLocation == LOCATION_CYAN) {
					DrawMap(26, BG_Y, gfxBorderGreenLeft);
					DrawMap(23, BG_Y + 8, gfxBorderGreenLeft);
				} else {
					DrawMap(1, BG_Y, gfxBorderGreenRight);
					DrawMap(4, BG_Y + 8, gfxBorderGreenRight);
				}
				break;
			case LOCATION_BLUE:
				if(playerLastLocation == LOCATION_GREEN) {
					DrawMap(26, BG_Y, gfxBorderBlueLeft);
					DrawMap(23, BG_Y + 8, gfxBorderBlueLeft);
				} else {
					DrawMap(1, BG_Y, gfxBorderBlueRight);
					DrawMap(4, BG_Y + 8, gfxBorderBlueRight);
				}
				break;
			case LOCATION_RED:
				if(playerLastLocation == LOCATION_BLUE) {
					DrawMap(26, BG_Y, gfxBorderRedLeft);
					DrawMap(23, BG_Y + 8, gfxBorderRedLeft);
				} else {
					DrawMap(1, BG_Y, gfxBorderRedRight);
					DrawMap(4, BG_Y + 8, gfxBorderRedRight);
				}
				break;
			case LOCATION_YELLOW:
				if(playerLastLocation == LOCATION_RED) {
					DrawMap(26, BG_Y, gfxBorderYellowLeft);
					DrawMap(23, BG_Y + 8, gfxBorderYellowLeft);
				} else {
					DrawMap(1, BG_Y, gfxBorderYellowRight);
					DrawMap(4, BG_Y + 8, gfxBorderYellowRight);
				}
				break;
			case LOCATION_PURPLE:
				if(playerLastLocation == LOCATION_YELLOW) {
					DrawMap(26, BG_Y, gfxBorderPurpleLeft);
					DrawMap(23, BG_Y + 8, gfxBorderPurpleLeft);
				} else {
					DrawMap(1, BG_Y, gfxBorderPurpleRight);
					DrawMap(4, BG_Y + 8, gfxBorderPurpleRight);
				}
				break;
			default:
				if(playerLastLocation == LOCATION_PURPLE) {
					DrawMap(26, BG_Y, gfxBorderCyanLeft);
					DrawMap(23, BG_Y + 8, gfxBorderCyanLeft);
				} else {
					DrawMap(1, BG_Y, gfxBorderCyanRight);
					DrawMap(4, BG_Y + 8, gfxBorderCyanRight);
				}
		}
	}
}
