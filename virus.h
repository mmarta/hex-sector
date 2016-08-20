#ifndef VIRUS_H
#define VIRUS_H

#include "const.h"
#include "gfx.h"
#include "player.h"

extern u8 virusY[], virusTime[], virusLocation[], virusActive[], virusDieTime[];

void virusInit(u8);
void virusUpdate(u8);
void virusDestroy(u8);

#endif
