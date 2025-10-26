#ifndef MINI_GAME_H
#define MINI_GAME_H

#include <genesis.h>

struct popUpTransform {
  u16 x;
  u16 y;
  u16 w;
  u16 h;
};

void drawPopup(u16 x, u16 y, u16 w, u16 h);
bool popUpAnimation(u16 x, u16 y, u16 w, u16 h);
void drawButtons();
void startMgna();
bool sizeMgnaEqlPuzzlePlayerInputArray();
bool checkPuzzlePlayerPass();
bool isPuzzleProcessActive();
void stopMgna();
void lostRound();
void winRound();

#endif // MINI_GAME_H
