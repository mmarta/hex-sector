#ifndef MACHINE_H
#define MACHINE_H

#include "const.h"
#include "gfx.h"
#include "audio.h"

extern u8 machineCredits, machineTitleMode, machineInputB[];
extern unsigned long machineHi;
extern const char machineCreditString[], machineHiString[];

void machineInit();
void machineCheckCoin();
u8 machineCheckStart();

#endif
