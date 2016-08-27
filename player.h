#ifndef PLAYER_H
#define PLAYER_H

#include "const.h"
#include "gfx.h"
#include "location.h"
#include "shot.h"

extern u8 playerLocation, playerLives, playerTime, playerDieTime, playerLocationTime, playerRedrawTick;
extern unsigned long playerScore, hi;

extern const char hiString[];

void playerStart();
void playerInput();
void playerUpdate();
void playerKill();
void playerAddScore(u16);

#endif
