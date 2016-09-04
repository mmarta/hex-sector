#ifndef LOCATION_H
#define LOCATION_H

#include "const.h"
#include "gfx.h"

void locationUpdate(u8);
void locationDraw(u8, u8, u8);
void locationClear();
void locationClearThreat(u8);
void locationShowAll(u8);
void locationMoveArrow(u8);
void locationSetMaxIntensity(u8, u8, u8);

#endif