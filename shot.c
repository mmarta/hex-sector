#include "shot.h"

u8 shotY[SHOT_TOTAL_ONSCREEN], shotActive[SHOT_TOTAL_ONSCREEN], shotIsViral[SHOT_TOTAL_ONSCREEN];
u8 shotSize[SHOT_TOTAL_ONSCREEN], shotXA[SHOT_TOTAL_ONSCREEN], shotXB[SHOT_TOTAL_ONSCREEN];

void shotInitPlayer() {
    u8 i, c = 0, len = SHOT_PLAYER_COUNT, gfxI, gfxOtherI;

    while(c < len) {
        i = SHOT_PLAYER_START + c;
        if(!shotActive[i]) {
            gfxI = gfxIndexSpriteShot[c << 1];
            gfxOtherI = gfxIndexSpriteShot[(c << 1) + 1];
            shotXA[i] = PLAYER_X << 3;
            shotXB[i] = shotXA[i] + 8;
            shotY[i] = PLAYER_Y << 3;
            shotSize[i] = 3;
            MapSprite(gfxI, gfxSpriteShotLarge);
            MapSprite(gfxOtherI, gfxSpriteShotLarge);
            MoveSprite(gfxI, shotXA[i], shotY[i], 1, 1);
            MoveSprite(gfxOtherI, shotXB[i], shotY[i], 1, 1);
            shotActive[i] = 1;
            shotIsViral[i] = 0;
            return;
        }
        c++;
    }
}

void shotInitViral(u8 y) {
    u8 i, c = 0, len = SHOT_VIRAL_COUNT, gfxI;

    if(y >= 112) {
        return;
    }

    while(c < len) {
        i = SHOT_VIRAL_START + c;
        if(!shotActive[i]) {
            gfxI = gfxIndexSpriteShot[c + SHOT_VIRAL_SPRITE_START];
            shotXA[i] = (PLAYER_X << 3) + 4;
            
            if(y < 54) {
                MapSprite(gfxI, gfxSpriteMissileTiny);
                shotSize[i] = 0;
            } else if(y < 84) {
                MapSprite(gfxI, gfxSpriteMissileSmall);
                shotSize[i] = 1;
            } else {
                MapSprite(gfxI, gfxSpriteMissileMedium);
                shotSize[i] = 1;
            }
            
            shotY[i] = y;
            MoveSprite(gfxI, shotXA[i], shotY[i], 1, 1);
            shotActive[i] = 1;
            shotIsViral[i] = 1;
            return;
        }
        c++;
    }
}

void shotUpdate(u8 i) {
    u8 gfxI, gfxOtherI;

    if(shotActive[i]) {
        if(!shotIsViral[i]) {
            gfxI = gfxIndexSpriteShot[(i - SHOT_PLAYER_START) << 1];
            gfxOtherI = gfxIndexSpriteShot[((i - SHOT_PLAYER_START) << 1) + 1];
        
            if(shotY[i] < (BG_Y << 3)) {
                shotFree(i);
            } else {
                if(shotY[i] < 54) {
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
        } else { //Viral shot
            gfxI = gfxIndexSpriteShot[i - SHOT_VIRAL_START + SHOT_VIRAL_SPRITE_START];
        
            if(shotY[i] >= 130) {
                if(shotSize[i] == 2) {
                    shotSize[i]++;
                    MapSprite(gfxI, gfxSpriteMissileLarge);
                }
                shotY[i] += 3;
            } else if(shotY[i] >= 84) {
                if(shotSize[i] == 1) {
                    shotSize[i]++;
                    MapSprite(gfxI, gfxSpriteMissileMedium);
                }
                shotY[i] += 2;
            } else if(shotY[i] >= 54) {
                if(shotSize[i] == 0) {
                    shotSize[i]++;
                    MapSprite(gfxI, gfxSpriteMissileSmall);
                }
                shotY[i] += 1;
            } else {
                shotY[i] += 1;
            }
            MoveSprite(gfxI, shotXA[i], shotY[i], 1, 1);
        }
    }
}

void shotFree(u8 i) {
    u8 gfxI, gfxOtherI;
    if(!shotIsViral[i]) {
        gfxI = gfxIndexSpriteShot[(i - SHOT_PLAYER_START) << 1];
        gfxOtherI = gfxIndexSpriteShot[((i - SHOT_PLAYER_START) << 1) + 1];

        if(shotActive[i]) {
            shotActive[i] = 0;
            MapSprite(gfxI, gfxMapSpriteBlank);
            MapSprite(gfxOtherI, gfxMapSpriteBlank);
            MoveSprite(gfxI, 0, 224, 1, 1);
            MoveSprite(gfxOtherI, 0, 224, 1, 1);
        }
    } else {
        gfxI = gfxIndexSpriteShot[i - SHOT_VIRAL_START + SHOT_VIRAL_SPRITE_START];
        
        if(shotActive[i]) {
            shotActive[i] = 0;
            MapSprite(gfxI, gfxMapSpriteBlank);
            MoveSprite(gfxI, 0, 224, 1, 1);
        }
    }
}
