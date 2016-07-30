#include "player.h"

u8 playerLocation, playerLives, playerTime, playerDieTime;
unsigned long playerScore;

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

void playerDraw();
void playerDrawLocation();
void playerDrawStats();

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
	int pad = ReadJoypad(0);

	if(pad & BTN_LEFT) {
		if(!playerLeftB && playerLocationTime == 0) {
			playerLastLocation = playerLocation;
			playerLocation--;
			playerLocationTime = 1;
			if(playerLocation == 255) {
				playerLocation = LOCATION_CYAN;
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
			if(playerLocation == 6) {
				playerLocation = LOCATION_GREEN;
			}

			playerRightB = 1;
		}
	} else {
		playerRightB = 0;
	}

	if(pad & BTN_A) {
		if(!playerFireB && playerLocationTime == 0) {
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
				playerDrawLocation();
			}
		}
	}
}

//Drawing function-sections
void playerDraw() {
	if(playerDieTime > 0) {
		return;
	}

	if(playerTime < 4) {
		DrawMap(14, 24, gfxPlayerA);
	} else {
		DrawMap(14, 24, gfxPlayerB);
	}
}

void playerDrawStats() {
	PrintLong(7, 1, playerScore);
}

void playerDrawLocation() {
	if(playerLocationTime == 0) {
		DrawMap(1, 6, gfxMapBigBlank);
		DrawMap(23, 6, gfxMapBigBlank);

		//Draw two of the same view map
		switch(playerLocation) {
			case LOCATION_GREEN:
				DrawMap(11, 6, gfxBorderGreenLeft);
				DrawMap(16, 6, gfxBorderGreenRight);
				DrawMap(8, 14, gfxBorderGreenLeft);
				DrawMap(19, 14, gfxBorderGreenRight);

				Print(9, 27, greenString);
				Print(15, 27, sectorString);
				Print(3, 26, cyanString);
				Print(23, 26, blueString);
				break;
			case LOCATION_BLUE:
				DrawMap(11, 6, gfxBorderBlueLeft);
				DrawMap(16, 6, gfxBorderBlueRight);
				DrawMap(8, 14, gfxBorderBlueLeft);
				DrawMap(19, 14, gfxBorderBlueRight);

				Print(9, 27, blueString);
				Print(15, 27, sectorString);
				Print(3, 26, greenString);
				Print(24, 26, redString);
				break;
			case LOCATION_RED:
				DrawMap(11, 6, gfxBorderRedLeft);
				DrawMap(16, 6, gfxBorderRedRight);
				DrawMap(8, 14, gfxBorderRedLeft);
				DrawMap(19, 14, gfxBorderRedRight);

				Print(10, 27, redString);
				Print(14, 27, sectorString);
				Print(3, 26, blueString);
				Print(21, 26, yellowString);
				break;
			case LOCATION_YELLOW:
				DrawMap(11, 6, gfxBorderYellowLeft);
				DrawMap(16, 6, gfxBorderYellowRight);
				DrawMap(8, 14, gfxBorderYellowLeft);
				DrawMap(19, 14, gfxBorderYellowRight);

				Print(8, 27, yellowString);
				Print(16, 27, sectorString);
				Print(3, 26, redString);
				Print(21, 26, purpleString);
				break;
			case LOCATION_PURPLE:
				DrawMap(11, 6, gfxBorderPurpleLeft);
				DrawMap(16, 6, gfxBorderPurpleRight);
				DrawMap(8, 14, gfxBorderPurpleLeft);
				DrawMap(19, 14, gfxBorderPurpleRight);

				Print(8, 27, purpleString);
				Print(16, 27, sectorString);
				Print(3, 26, yellowString);
				Print(23, 26, cyanString);
				break;
			default:
				DrawMap(11, 6, gfxBorderCyanLeft);
				DrawMap(16, 6, gfxBorderCyanRight);
				DrawMap(8, 14, gfxBorderCyanLeft);
				DrawMap(19, 14, gfxBorderCyanRight);

				Print(9, 27, cyanString);
				Print(15, 27, sectorString);
				Print(3, 26, purpleString);
				Print(22, 26, greenString);
		}

		Print(1, 26, leftArrowString);
		Print(28, 26, rightArrowString);
	} else if(playerLocationTime == 2) {
		//Draw one map in one color, and the other in the previous
		DrawMap(8, 6, gfxMapBigBlank);
		DrawMap(16, 6, gfxMapBigBlank);
		DrawMap(0, 26, gfxMapLongBlank);

		switch(playerLocation) {
			case LOCATION_GREEN:
				if(playerLastLocation == LOCATION_CYAN) {
					DrawMap(1, 6, gfxBorderCyanRight);
					DrawMap(4, 14, gfxBorderCyanRight);
				} else {
					DrawMap(26, 6, gfxBorderBlueLeft);
					DrawMap(23, 14, gfxBorderBlueLeft);
				}
				break;
			case LOCATION_BLUE:
				if(playerLastLocation == LOCATION_GREEN) {
					DrawMap(1, 6, gfxBorderGreenRight);
					DrawMap(4, 14, gfxBorderGreenRight);
				} else {
					DrawMap(26, 6, gfxBorderRedLeft);
					DrawMap(23, 14, gfxBorderRedLeft);
				}
				break;
			case LOCATION_RED:
				if(playerLastLocation == LOCATION_BLUE) {
					DrawMap(1, 6, gfxBorderBlueRight);
					DrawMap(4, 14, gfxBorderBlueRight);
				} else {
					DrawMap(26, 6, gfxBorderYellowLeft);
					DrawMap(23, 14, gfxBorderYellowLeft);
				}
				break;
			case LOCATION_YELLOW:
				if(playerLastLocation == LOCATION_RED) {
					DrawMap(1, 6, gfxBorderRedRight);
					DrawMap(4, 14, gfxBorderRedRight);
				} else {
					DrawMap(26, 6, gfxBorderPurpleLeft);
					DrawMap(23, 14, gfxBorderPurpleLeft);
				}
				break;
			case LOCATION_PURPLE:
				if(playerLastLocation == LOCATION_YELLOW) {
					DrawMap(1, 6, gfxBorderYellowRight);
					DrawMap(4, 14, gfxBorderYellowRight);
				} else {
					DrawMap(26, 6, gfxBorderCyanLeft);
					DrawMap(23, 14, gfxBorderCyanLeft);
				}
				break;
			default:
				if(playerLastLocation == LOCATION_PURPLE) {
					DrawMap(1, 6, gfxBorderPurpleRight);
					DrawMap(4, 14, gfxBorderPurpleRight);
				} else {
					DrawMap(26, 6, gfxBorderGreenLeft);
					DrawMap(23, 14, gfxBorderGreenLeft);
				}
		}
	} else {
		//Draw one map in one color, and the other in the previous
		DrawMap(1, 6, gfxMapBigBlank);
		DrawMap(23, 6, gfxMapBigBlank);

		switch(playerLocation) {
			case LOCATION_GREEN:
				if(playerLastLocation == LOCATION_CYAN) {
					DrawMap(26, 6, gfxBorderGreenLeft);
					DrawMap(23, 14, gfxBorderGreenLeft);
				} else {
					DrawMap(1, 6, gfxBorderGreenRight);
					DrawMap(4, 14, gfxBorderGreenRight);
				}
				break;
			case LOCATION_BLUE:
				if(playerLastLocation == LOCATION_GREEN) {
					DrawMap(26, 6, gfxBorderBlueLeft);
					DrawMap(23, 14, gfxBorderBlueLeft);
				} else {
					DrawMap(1, 6, gfxBorderBlueRight);
					DrawMap(4, 14, gfxBorderBlueRight);
				}
				break;
			case LOCATION_RED:
				if(playerLastLocation == LOCATION_BLUE) {
					DrawMap(26, 6, gfxBorderRedLeft);
					DrawMap(23, 14, gfxBorderRedLeft);
				} else {
					DrawMap(1, 6, gfxBorderRedRight);
					DrawMap(4, 14, gfxBorderRedRight);
				}
				break;
			case LOCATION_YELLOW:
				if(playerLastLocation == LOCATION_RED) {
					DrawMap(26, 6, gfxBorderYellowLeft);
					DrawMap(23, 14, gfxBorderYellowLeft);
				} else {
					DrawMap(1, 6, gfxBorderYellowRight);
					DrawMap(4, 14, gfxBorderYellowRight);
				}
				break;
			case LOCATION_PURPLE:
				if(playerLastLocation == LOCATION_YELLOW) {
					DrawMap(26, 6, gfxBorderPurpleLeft);
					DrawMap(23, 14, gfxBorderPurpleLeft);
				} else {
					DrawMap(1, 6, gfxBorderPurpleRight);
					DrawMap(4, 14, gfxBorderPurpleRight);
				}
				break;
			default:
				if(playerLastLocation == LOCATION_PURPLE) {
					DrawMap(26, 6, gfxBorderCyanLeft);
					DrawMap(23, 14, gfxBorderCyanLeft);
				} else {
					DrawMap(1, 6, gfxBorderCyanRight);
					DrawMap(4, 14, gfxBorderCyanRight);
				}
		}
	}
}
