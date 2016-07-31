#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <uzebox.h>

#include "gfx.h"
#include "shot.h"
#include "player.h"

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

	while(1) {
		WaitVsync(1);
		playerInput();
		playerUpdate();

		i = 0;
		while(i < (SHOT_TOTAL >> 1)) {
			shotUpdate(i);
			i++;
		}
	}
}
