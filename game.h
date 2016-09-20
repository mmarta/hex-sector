#ifndef GAME_H
#define GAME_H

#include "const.h"
#include "gfx.h"
#include "location.h"
#include "shot.h"
#include "player.h"
#include "virus.h"
#include "machine.h"

extern u8 gameStage;

void gameStart();
void gameUpdate();

#endif