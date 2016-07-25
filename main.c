#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <uzebox.h>

#include "gfx.h"

int main() {
	//srand(time(NULL));

	//Set the tile table and clear.
	SetTileTable(gfxTiles);
	//SetSpritesTileTable(gfxTilesSprite);
	//SetSpriteVisibility(1);
	ClearVram();

	while(1) {
		WaitVsync(1);
	}
}
