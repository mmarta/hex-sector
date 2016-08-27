#ifndef CONST_H
#define CONST_H

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <uzebox.h>

#define LOCATION_GREEN 0
#define LOCATION_BLUE 1
#define LOCATION_RED 2
#define LOCATION_YELLOW 3
#define LOCATION_PURPLE 4
#define LOCATION_CYAN 5
#define LOCATION_COUNT 6

#define BG_Y 5

#define PLAYER_X 14
#define PLAYER_Y 22

#define SHOT_TOTAL 6
#define SHOT_HEIGHT 8

#define VIRUS_POOL_TOTAL 6
#define VIRUS_X 14
#define VIRUS_HEIGHT 16
#define VIRUS_NEXT_MOVE_START 32

#define V_QUEUE_LENGTH 8

#define SPRITE_TOTAL 20

#endif
