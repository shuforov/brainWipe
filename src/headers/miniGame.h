#ifndef MINI_GAME_H
#define MINI_GAME_H

#include <genesis.h>

struct popUpTransform {
  u16 x;
  u16 y;
  u16 w;
  u16 h;
};

struct buttonMetadata {
  u16 x;
  u16 y;
  u16 idTag;
};

void drawPopup(u16 x, u16 y, u16 w, u16 h);
bool popUpAnimation(u16 x, u16 y, u16 w, u16 h);
void drawButtons();
void countDownGo();
void setCountDownGo(bool value);
void buttonAnimation();
void buttonAnimationProcess(u16 buttonIndex, u16 buttonType[]);
void setButtonAnimationState(u16 buttonType, bool state);
bool isButtonAnimation();

#endif // MINI_GAME_H
