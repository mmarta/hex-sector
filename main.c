#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <uzebox.h>

#include "gfx.h"
#include "shot.h"
#include "player.h"

u8 credits = 0, inputB[] = {0, 0, 0, 0};
const char creditString[] PROGMEM = "CREDIT";

void checkCoinStart();
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
		checkCoinStart();
		playerInput();
		playerUpdate();

		i = 0;
		while(i < (SHOT_TOTAL >> 1)) {
			shotUpdate(i);
			i++;
		}
	}
}

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

void addCoin() {
	if(credits < 9) {
		credits++;
		PrintByte(18, 27, credits, 0);
		Print(11, 27, creditString);
	}
}
