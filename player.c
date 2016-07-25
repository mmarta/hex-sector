#include "player.h"

u8 playerLocation, playerLives, playerTime, playerDieTime;


//Internal vars
u8 playerLastLocation, playerLocationTime;
u8 playerLeftB, playerRightB, playerFireB;

void playerDrawLocation();

void playerStart() {
	playerLocation = LOCATION_GREEN;
	playerLives = 3;
	playerTime = 0;
	playerDieTime = 0;

	playerLeftB = 0;
	playerRightB = 0;
	playerFireB = 0;

	playerLocationTime = 0;
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

		if(playerLocationTime > 0) {
			if(playerLocationTime == 1) {

			} else if(playerLocationTime == 9) {

			} else if(playerLocationTime >= 17) {

				playerLocationTime = 0;
			}

			playerLocationTime++;
		}
	}
}

//Drawing ffunction-sections
void playerDrawLocation() {
	if(playerLocationTime == 0) {
		//Draw two of the same view map
	} else {
		//Draw one map in one color, and the other in the previous
	}
}
