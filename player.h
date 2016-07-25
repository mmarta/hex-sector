#ifndef PLAYER_H
#define PLAYER_H

#include "const.h"
#include "gfx.h"

extern u8 playerLocation, playerLives, playerTime, playerDieTime;

void playerStart();
void playerInput();
void playerUpdate();

#endif
