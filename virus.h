#ifndef VIRUS_H
#define VIRUS_H

#include "const.h"
#include "gfx.h"
#include "location.h"
#include "player.h"

extern u8 virusY[], virusTime[], virusLocation[], virusActive[], virusDieTime[];

u8 virusInit(u8, u8);
void virusUpdate(u8, u8);
void virusDestroy(u8);

#endif
