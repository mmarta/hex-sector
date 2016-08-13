#ifndef PLAYER_H
#define PLAYER_H

#include "const.h"
#include "gfx.h"
#include "shot.h"

extern u8 playerLocation, playerLives, playerTime, playerDieTime, playerLocationTime, playerRedrawTick;
extern unsigned long playerScore;

void playerStart();
void playerInput();
void playerUpdate();

#endif
