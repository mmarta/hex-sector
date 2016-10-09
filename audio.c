#include "audio.h"

const char patchCoinUp[] PROGMEM = {
    0, PC_WAVE, 4,
    0, PC_ENV_SPEED, -20,
    0, PC_PITCH, 60,
    6, PC_NOTE_UP, 12,
    6, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchPlayerFire[] PROGMEM = {
    0, PC_WAVE, 0,
    0, PC_PITCH, 60,
    0, PC_SLIDE, -24,
    10, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchPlayerMove[] PROGMEM = {
    0, PC_WAVE, 2,
    0, PC_PITCH, 47,
    0, PC_SLIDE, 20,
    16, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchVirusKill[] PROGMEM = {
    0, PC_WAVE, 3,
    0, PC_PITCH, 190,
    0, PC_SLIDE, -100,
    6, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchFlash[] PROGMEM = {
    0, PC_WAVE, 3,
    0, PC_PITCH, 60,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    0, PC_ENV_VOL, 180,
    4, PC_PITCH, 60,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    0, PC_ENV_VOL, 110,
    4, PC_PITCH, 60,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_UP, 6,
    4, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchVirusAppear[] PROGMEM = {
    0, PC_WAVE, 9,
    0, PC_TREMOLO_LEVEL, 128,
    0, PC_PITCH, 54,
    10, PC_NOTE_UP, 2,
    0, PC_ENV_VOL, 110,
    10, PC_PITCH, 54,
    10, PC_NOTE_UP, 2,
    10, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchVirusAngryAppear[] PROGMEM = {
    0, PC_WAVE, 8,
    0, PC_TREMOLO_LEVEL, 128,
    0, PC_PITCH, 36,
    20, PC_NOTE_UP, 2,
    20, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchVirusFire[] PROGMEM = {
    0, PC_WAVE, 5,
    0, PC_PITCH, 130,
    0, PC_SLIDE, -60,
    6, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchPlayerKill[] PROGMEM = {
    0, PC_WAVE, 5,
    0, PC_PITCH, 60,
    0, PC_SLIDE, -50,
    25, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchStartA[] PROGMEM = {
    0, PC_WAVE, 5,
    0, PC_ENV_SPEED, -3,
    0, PC_PITCH, 48,
    90, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchStartB[] PROGMEM = {
    0, PC_WAVE, 1,
    0, PC_ENV_SPEED, -3,
    0, PC_PITCH, 36,
    90, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchStartC[] PROGMEM = {
    0, PC_WAVE, 5,
    0, PC_ENV_SPEED, -3,
    0, PC_PITCH, 43,
    90, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchGameOverA[] PROGMEM = {
    0, PC_WAVE, 5,
    0, PC_ENV_SPEED, 1,
    0, PC_ENV_VOL, 80,
    0, PC_PITCH, 72,
    15, PC_NOTE_DOWN, 3,
    15, PC_NOTE_DOWN, 3,
    15, PC_NOTE_DOWN, 3,
    30, PC_SLIDE, -20,
    30, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchGameOverB[] PROGMEM = {
    0, PC_WAVE, 5,
    0, PC_ENV_SPEED, 1,
    0, PC_ENV_VOL, 80,
    0, PC_PITCH, 75,
    15, PC_NOTE_DOWN, 3,
    15, PC_NOTE_DOWN, 3,
    15, PC_NOTE_DOWN, 3,
    30, PC_SLIDE, -20,
    30, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchGameOverC[] PROGMEM = {
    0, PC_WAVE, 5,
    0, PC_ENV_SPEED, 1,
    0, PC_ENV_VOL, 80,
    0, PC_PITCH, 67,
    15, PC_NOTE_DOWN, 3,
    15, PC_NOTE_DOWN, 3,
    15, PC_NOTE_DOWN, 3,
    30, PC_SLIDE, -20,
    30, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const char patchPlayerExtend[] PROGMEM = {
    0, PC_WAVE, 0,
    0, PC_ENV_SPEED, -4,
    0, PC_PITCH, 60,
    8, PC_NOTE_UP, 4,
    8, PC_NOTE_UP, 3,
    8, PC_NOTE_UP, 4,
    8, PC_NOTE_UP, 3,
    24, PC_NOTE_CUT, 0,
    0, PATCH_END
};

const struct PatchStruct patches[] PROGMEM = {
    {0, NULL, patchCoinUp, 0, 0},
    {0, NULL, patchPlayerFire, 0, 0},
    {0, NULL, patchPlayerMove, 0, 0},
    {0, NULL, patchVirusKill, 0, 0},
    {0, NULL, patchFlash, 0, 0},
    {0, NULL, patchVirusAppear, 0, 0},
    {0, NULL, patchVirusAngryAppear, 0, 0},
    {0, NULL, patchVirusFire, 0, 0},
    {0, NULL, patchPlayerKill, 0, 0},
    {0, NULL, patchStartA, 0, 0},
    {0, NULL, patchStartB, 0, 0},
    {0, NULL, patchStartC, 0, 0},
    {0, NULL, patchGameOverA, 0, 0},
    {0, NULL, patchGameOverB, 0, 0},
    {0, NULL, patchGameOverC, 0, 0},
    {0, NULL, patchPlayerExtend, 0, 0}
};
