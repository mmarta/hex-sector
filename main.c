#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <uzebox.h>

#include "gfx.h"
#include "shot.h"
#include "player.h"
#include "virus.h"
#include "vqueue.h"

u8 credits = 0, inputB[] = {0, 0, 0, 0};
const char creditString[] PROGMEM = "CREDIT";

u8 tick = 0;

void checkCoinStart();
void runAllCollisions();
u8 checkCollision(u8, u8, u8, u8);
void addCoin();

int main() {
	u8 i;
	//srand(time(NULL));

	//Set the tile table and clear.
	SetTileTable(gfxTiles);
	ClearVram();

	SetSpritesTileTable(gfxTilesSprite);
	SetSpriteVisibility(1);
	gfxLoadIndexSprite();

	playerStart();
	PrintByte(18, 27, credits, 0);
	Print(11, 27, creditString);


	while(1) {
		WaitVsync(1);

		//Temp tick code
		if(!tick) {
			vQueueEnqueue(rand() % 6, 0);
			vQueueEnqueue(rand() % 6, 40);
		}

		//Check collisions first
		runAllCollisions();

		//Update & inputs
		checkCoinStart();
		vQueueCycle(); //Any viruses to initialize?
		playerInput();
		playerUpdate();
		i = 0;
		while(i < VIRUS_POOL_TOTAL) {
			virusUpdate(i);
			i++;
		}
		playerRedrawTick = 0;

		//Sprite updates come next
		i = 0;
		while(i < (SHOT_TOTAL >> 1)) {
			shotUpdate(i);
			i++;
		}

		//Temp ticks
		tick++;
		if(tick >= 180) {
			tick = 0;
		}
	}
}

//Runs through all collisions
void runAllCollisions() {
	u8 i, j;

	i = 0;
	while(i < VIRUS_POOL_TOTAL) {
		if(!virusActive[i] || playerLocation != virusLocation[i]) {
			i++;
			continue;
		}

		j = 0;
		while(j < SHOT_TOTAL >> 1) {
			if(!shotActive[j]) {
				j++;
				continue;
			}

			if(checkCollision(virusY[i] << 3, VIRUS_HEIGHT, shotY[j], SHOT_HEIGHT)) {
				shotFree(j);
				virusDestroy(i);
				if(virusY[i] <= 10) {
					playerAddScore(100);
				} else if(virusY[i] <= 14) {
					playerAddScore(200);
				} else {
					playerAddScore(400);
				}
			}
			j++;
		}
		i++;
	}
}

//checks a single collision
u8 checkCollision(u8 y1, u8 h1, u8 y2, u8 h2) {
	if(y1 + h1 >= y2 && y1 < y2 + h2) {
		return 1;
	}

	return 0;
}

//Checks coin up & player start inputs
void checkCoinStart() {
	unsigned int padA = ReadJoypad(0);
	unsigned int padB = ReadJoypad(1);

	//Service!
	if(padA & BTN_SL) {
		if(!inputB[0]) {
			addCoin();
			inputB[0] = 1;
		}
	} else {
		inputB[0] = 0;
	}

	//Coins (dunno why mapped to strange things)
	if(padB & BTN_SR) {
		if(!inputB[1]) {
			addCoin();
			inputB[1] = 1;
		}
	} else {
		inputB[1] = 0;
	}

	if(padB & BTN_SL) {
		if(!inputB[2]) {
			addCoin();
			inputB[2] = 1;
		}
	} else {
		inputB[2] = 0;
	}

	//Player 1 Start
	if(padA & BTN_START) {
		if(!inputB[3]) {
			if(credits > 0) {
				//Start!
				credits--;
				PrintByte(18, 27, credits, 0);
				Print(11, 27, creditString);
			}
			inputB[3] = 1;
		}
	} else {
		inputB[3] = 0;
	}
}

//Adds a coin
void addCoin() {
	if(credits < 9) {
		credits++;
		PrintByte(18, 27, credits, 0);
		Print(11, 27, creditString);
	}
}
