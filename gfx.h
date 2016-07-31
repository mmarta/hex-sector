#ifndef GFX_H
#define GFX_H

#include "const.h"

//Standard GFX tiles

extern const char gfxTiles[];

extern const char gfxPlayerA[];
extern const char gfxPlayerB[];

extern const char gfxVirusCloseGreen[];
extern const char gfxVirusCloseBlue[];
extern const char gfxVirusCloseRed[];
extern const char gfxVirusCloseYellow[];
extern const char gfxVirusClosePurple[];
extern const char gfxVirusCloseCyan[];

extern const char gfxBorderGreenLeft[];
extern const char gfxBorderGreenRight[];
extern const char gfxBorderBlueLeft[];
extern const char gfxBorderBlueRight[];
extern const char gfxBorderRedLeft[];
extern const char gfxBorderRedRight[];
extern const char gfxBorderYellowLeft[];
extern const char gfxBorderYellowRight[];
extern const char gfxBorderPurpleLeft[];
extern const char gfxBorderPurpleRight[];
extern const char gfxBorderCyanLeft[];
extern const char gfxBorderCyanRight[];

extern const char gfxMapBlank8[];
extern const char gfxMapBlank16[];
extern const char gfxMapBigBlank[];
extern const char gfxMapLongBlank[];

//Sprite tiles

extern const char gfxTilesSprite[];

extern const char gfxMapSpriteBlank[];

extern const char gfxSpriteShotLarge[];
extern const char gfxSpriteShotMedium[];
extern const char gfxSpriteShotSmall[];
extern const char gfxSpriteShotTiny[];

//Sprite memory for shots

extern u8 gfxIndexSpriteShot[];

void gfxLoadIndexSprite();

#endif
