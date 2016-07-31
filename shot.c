#include "shot.h"

u8 shotY[SHOT_TOTAL >> 1], shotActive[SHOT_TOTAL >> 1];
u8 shotSize[SHOT_TOTAL >> 1], shotXA[SHOT_TOTAL >> 1], shotXB[SHOT_TOTAL >> 1];

void shotInit() {
	u8 i = 0, len = SHOT_TOTAL >> 1, gfxI, gfxOtherI;

	while(i < len) {
		if(!shotActive[i]) {
			gfxI = gfxIndexSpriteShot[i << 1];
			gfxOtherI = gfxIndexSpriteShot[(i << 1) + 1];
			shotXA[i] = PLAYER_X << 3;
			shotXB[i] = shotXA[i] + 8;
			shotY[i] = PLAYER_Y << 3;
			shotSize[i] = 3;
			MapSprite(gfxI, gfxSpriteShotLarge);
			MapSprite(gfxOtherI, gfxSpriteShotLarge);
			MoveSprite(gfxI, shotXA[i], shotY[i], 1, 1);
			MoveSprite(gfxOtherI, shotXB[i], shotY[i], 1, 1);
			shotActive[i] = 1;
			return;
		}
		i++;
	}
}

void shotUpdate(u8 i) {
	u8 gfxI = gfxIndexSpriteShot[i << 1], gfxOtherI = gfxIndexSpriteShot[(i << 1) + 1];

	if(shotActive[i]) {
		if(shotY[i] < (BG_Y << 3)) {
			shotFree(i);
		} else {
			if(shotY[i] < 66) {
				if(shotSize[i] == 1) {
					shotSize[i]--;
					shotXA[i]++;
					shotXB[i]--;
					MapSprite(gfxI, gfxSpriteShotTiny);
					MapSprite(gfxOtherI, gfxSpriteShotTiny);
				}
				shotY[i] -= 2;
			} else if(shotY[i] < 84) {
				if(shotSize[i] == 2) {
					shotSize[i]--;
					shotXA[i]++;
					shotXB[i]--;
					MapSprite(gfxI, gfxSpriteShotSmall);
					MapSprite(gfxOtherI, gfxSpriteShotSmall);
				}
				shotY[i] -= 3;
			} else if(shotY[i] < 130) {
				if(shotSize[i] == 3) {
					shotSize[i]--;
					shotXA[i]++;
					shotXB[i]--;
					MapSprite(gfxI, gfxSpriteShotMedium);
					MapSprite(gfxOtherI, gfxSpriteShotMedium);
				}
				shotY[i] -= 4;
			} else {
				shotY[i] -= 6;
			}
			MoveSprite(gfxI, shotXA[i], shotY[i], 1, 1);
			MoveSprite(gfxOtherI, shotXB[i], shotY[i], 1, 1);
		}
	}
}

void shotFree(u8 i) {
	u8 gfxI = gfxIndexSpriteShot[i << 1], gfxOtherI = gfxIndexSpriteShot[(i << 1) + 1];

	if(shotActive[i]) {
		shotActive[i] = 0;
		MapSprite(gfxI, gfxMapSpriteBlank);
		MapSprite(gfxOtherI, gfxMapSpriteBlank);
		MoveSprite(gfxI, 0, 224, 1, 1);
		MoveSprite(gfxOtherI, 0, 224, 1, 1);
	}
}
