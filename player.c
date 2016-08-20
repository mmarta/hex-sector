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

const char readyString[] PROGMEM = "READY!";

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
	playerLocationTime = 0;

	playerLeftB = 0;
	playerRightB = 0;
	playerFireB = 0;

	playerScore = 0;

	playerDrawLocation();
	playerDraw();
	Print(0, 0, scoreString);
	playerDrawStats();
}

void playerInput() {
	u8 i = SHOT_TOTAL >> 1;
	unsigned int pad;

	if(playerDieTime > 0) {
		return; //No input if player is dying.
	}

	pad = ReadJoypad(0);

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
				playerDrawLocation();
			} else if(playerLocationTime >= 14) {
				playerLocationTime = 0;
				playerRedrawTick = 1;
				playerDrawLocation();
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
			DrawMap(1, BG_Y, gfxMapBigBlank);
			DrawMap(8, BG_Y, gfxMapBigBlank);
			DrawMap(16, BG_Y, gfxMapBigBlank);
			DrawMap(23, BG_Y, gfxMapBigBlank);

			DrawMap(0, PLAYER_Y + 2, gfxMapLongBlank);
			Print(12, 13, readyString);

			//Clear shots
			i = 0;
			while(i < SHOT_TOTAL >> 1) {
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
			playerDrawLocation();
			return;
		}

		playerDieTime++;
	}
}

void playerKill() {
	playerDieTime = 1;
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
	PrintLong(7, 1, playerScore);
}

void playerDrawLocation() {
	u8 i = 0;
	if(playerLocationTime == 0) {
		DrawMap(0, BG_Y, gfxMapBigBlank);
		DrawMap(22, BG_Y, gfxMapBigBlank);

		//Draw two of the same view map
		switch(playerLocation) {
			case LOCATION_GREEN:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderGreenLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderGreenRight);
					i++;
				}

				Print(9, PLAYER_Y + 3, greenString);
				Print(15, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, cyanString);
				Print(23, PLAYER_Y + 2, blueString);
				break;
			case LOCATION_BLUE:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderBlueLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderBlueRight);
					i++;
				}

				Print(9, PLAYER_Y + 3, blueString);
				Print(15, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, greenString);
				Print(24, PLAYER_Y + 2, redString);
				break;
			case LOCATION_RED:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderRedLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderRedRight);
					i++;
				}

				Print(10, PLAYER_Y + 3, redString);
				Print(14, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, blueString);
				Print(21, PLAYER_Y + 2, yellowString);
				break;
			case LOCATION_YELLOW:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderYellowLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderYellowRight);
					i++;
				}

				Print(8, PLAYER_Y + 3, yellowString);
				Print(16, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, redString);
				Print(21, PLAYER_Y + 2, purpleString);
				break;
			case LOCATION_PURPLE:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderPurpleLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderPurpleRight);
					i++;
				}

				Print(8, PLAYER_Y + 3, purpleString);
				Print(16, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, yellowString);
				Print(23, PLAYER_Y + 2, cyanString);
				break;
			default:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderCyanLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderCyanRight);
					i++;
				}

				Print(9, PLAYER_Y + 3, cyanString);
				Print(15, PLAYER_Y + 3, sectorString);
				Print(3, PLAYER_Y + 2, purpleString);
				Print(22, PLAYER_Y + 2, greenString);
		}

		Print(1, PLAYER_Y + 2, leftArrowString);
		Print(28, PLAYER_Y + 2, rightArrowString);
	} else if(playerLocationTime == 2) {
		//Draw one map in one color, and the other in the previous
		DrawMap(6, BG_Y, gfxMapBigBlank);
		DrawMap(16, BG_Y, gfxMapBigBlank);
		DrawMap(0, PLAYER_Y + 2, gfxMapLongBlank);

		switch(playerLocation) {
			case LOCATION_GREEN:
				if(playerLastLocation == LOCATION_CYAN) {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderCyanRight);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderBlueLeft);
						i++;
					}
				}
				break;
			case LOCATION_BLUE:
				if(playerLastLocation == LOCATION_GREEN) {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderGreenRight);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderRedLeft);
						i++;
					}
				}
				break;
			case LOCATION_RED:
				if(playerLastLocation == LOCATION_BLUE) {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderBlueRight);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderYellowLeft);
						i++;
					}
				}
				break;
			case LOCATION_YELLOW:
				if(playerLastLocation == LOCATION_RED) {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderRedRight);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderPurpleLeft);
						i++;
					}
				}
				break;
			case LOCATION_PURPLE:
				if(playerLastLocation == LOCATION_YELLOW) {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderYellowRight);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderCyanLeft);
						i++;
					}
				}
				break;
			default:
				if(playerLastLocation == LOCATION_PURPLE) {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderPurpleRight);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderGreenLeft);
						i++;
					}
				}
		}
	} else {
		//Draw one map in one color, and the other in the previous
		DrawMap(0, BG_Y, gfxMapBigBlank);
		DrawMap(22, BG_Y, gfxMapBigBlank);

		switch(playerLocation) {
			case LOCATION_GREEN:
				if(playerLastLocation == LOCATION_CYAN) {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderGreenLeft);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderGreenRight);
						i++;
					}
				}
				break;
			case LOCATION_BLUE:
				if(playerLastLocation == LOCATION_GREEN) {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderBlueLeft);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderBlueRight);
						i++;
					}
				}
				break;
			case LOCATION_RED:
				if(playerLastLocation == LOCATION_BLUE) {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderRedLeft);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderRedRight);
						i++;
					}
				}
				break;
			case LOCATION_YELLOW:
				if(playerLastLocation == LOCATION_RED) {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderYellowLeft);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderYellowRight);
						i++;
					}
				}
				break;
			case LOCATION_PURPLE:
				if(playerLastLocation == LOCATION_YELLOW) {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderPurpleLeft);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderPurpleRight);
						i++;
					}
				}
				break;
			default:
				if(playerLastLocation == LOCATION_PURPLE) {
					while(i < 8) {
						DrawMap(29 - i, BG_Y + (i << 1), gfxBorderCyanLeft);
						i++;
					}
				} else {
					while(i < 8) {
						DrawMap(0 + i, BG_Y + (i << 1), gfxBorderCyanRight);
						i++;
					}
				}
		}
	}
}
