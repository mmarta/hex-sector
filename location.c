#include "location.h"

const char leftArrowString[] PROGMEM = "<";
const char rightArrowString[] PROGMEM = ">";

u8 locationIntensity[LOCATION_COUNT];
u8 locationTime[LOCATION_COUNT];

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
		locationDrawBlock(i);
	} else {
		DrawMap(12 + i, PLAYER_Y + 3, gfxMapBlank8);
	}
}

//Draw full location
void locationDraw(u8 playerLocation, u8 playerLastLocation, u8 playerLocationTime) {
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
				break;
			case LOCATION_BLUE:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderBlueLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderBlueRight);
					i++;
				}

				break;
			case LOCATION_RED:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderRedLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderRedRight);
					i++;
				}
				break;
			case LOCATION_YELLOW:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderYellowLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderYellowRight);
					i++;
				}
				break;
			case LOCATION_PURPLE:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderPurpleLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderPurpleRight);
					i++;
				}
				break;
			default:
				while(i < 8) {
					DrawMap(13 - i, BG_Y + (i << 1), gfxBorderCyanLeft);
					DrawMap(16 + i, BG_Y + (i << 1), gfxBorderCyanRight);
					i++;
				}
		}

		Print(1, PLAYER_Y + 2, leftArrowString);
		Print(28, PLAYER_Y + 2, rightArrowString);
	} else if(playerLocationTime == 2) {
		//Draw one map in one color, and the other in the previous
		DrawMap(6, BG_Y, gfxMapBigBlank);
		DrawMap(16, BG_Y, gfxMapBigBlank);
		
		DrawMap(1, PLAYER_Y + 2, gfxMapBlank8);
		DrawMap(28, PLAYER_Y + 2, gfxMapBlank8);

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

void locationSetMaxIntensity(u8 location, u8 intensity) {
	if(locationIntensity[location] < intensity) {
		locationIntensity[location] = intensity;
		locationTime[location] = 0;
	}
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