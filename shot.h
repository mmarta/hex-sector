#ifndef SHOT_H
#define SHOT_H

#include "const.h"
#include "gfx.h"

extern u8 shotY[], shotActive[];

void shotInit();
void shotUpdate(u8);
void shotFree(u8);

#endif
