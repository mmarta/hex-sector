#ifndef SHOT_H
#define SHOT_H

#include "const.h"
#include "gfx.h"
#include "audio.h"

extern u8 shotY[], shotActive[], shotIsViral[];

void shotInitPlayer();
void shotInitViral(u8);
void shotUpdate(u8);
void shotFree(u8);

#endif
