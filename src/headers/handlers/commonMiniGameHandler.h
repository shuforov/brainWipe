#ifndef COMMON_MINI_GAME_HANDLER_H
#define COMMON_MINI_GAME_HANDLER_H

#include <genesis.h>

#define M_G_N_A_MAX_SIZE 20// mini game numbers array max size

struct buttonMetadata {
  u16 x;
  u16 y;
  u16 idTag;
};

struct buttonMetadata* getButtonsInPopUp();

void generateMgna(u16 min, u16 max, u16 howMany);
void printMgna();
u16 *getMgna();
u16 getMgnaCounter();
void setPuzzleWaitPlayerInput(bool state);
bool getPuzzleWaitPlayerInput();
void pushPuzzlePlayerInputArray(u16 input);
void resetPuzzlePlayerInputArray();
void printPuzzlePlayerInputArray();
void resetMgnaArray();
u16 getPuzzlePlayerInputArrayCounter();
bool mgnaEqlPpia();

#endif
