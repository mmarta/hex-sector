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
extern const char gfxVirusCloseAngry[];

extern const char gfxVirusDieA[];
extern const char gfxVirusDieB[];
extern const char gfxVirusDieC[];
extern const char gfxVirusDieD[];

extern const char gfxPlayerDieA[];
extern const char gfxPlayerDieB[];
extern const char gfxPlayerDieC[];
extern const char gfxPlayerDieD[];

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

extern const char gfxBlockGreen[];
extern const char gfxBlockBlue[];
extern const char gfxBlockRed[];
extern const char gfxBlockYellow[];
extern const char gfxBlockPurple[];
extern const char gfxBlockCyan[];
extern const char gfxBlockAngry[];
extern const char gfxArrow[];
extern const char gfxLife[];

extern const char gfxLogoH[];
extern const char gfxLogoE[];
extern const char gfxLogoX[];

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
extern const char gfxSpriteMissileLarge[];
extern const char gfxSpriteMissileMedium[];
extern const char gfxSpriteMissileSmall[];
extern const char gfxSpriteMissileTiny[];

//Sprite memory for shots

extern u8 gfxIndexSpriteShot[];

void gfxLoadIndexSprite();

#endif
