#ifndef PLAYER_H
#define PLAYER_H

#include "const.h"
#include "gfx.h"
#include "audio.h"
#include "machine.h"
#include "location.h"
#include "shot.h"

extern u8 playerLocation, playerLives, playerTime, playerDieTime, playerLocationTime, playerRedrawTick, playerFlashTick;
extern unsigned long playerScore;

void playerStart();
void playerInput();
void playerUpdate();
void playerKill();
void playerAddScore(u16);

#endif
