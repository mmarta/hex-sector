#ifndef VQUEUE_H
#define VQUEUE_H

#include "const.h"
#include "virus.h"

extern u8 vQueueSize;

void vQueueClear();
u8 vQueueEnqueue(u8, u8, u8);
void vQueueCycle();

#endif
