#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <genesis.h>

typedef struct {
  bool startButton;
  bool xButton;
  bool yButton;
  bool zButton;
  bool aButton;
  bool bButton;
  bool cButton;
  bool upButton;
  bool downButton;
  bool leftButton;
  bool rightButton;
} InputStates;

void joyUpdate(u16 joy, u16 changed, u16 state);
void joyOne(u16 joy, u16 changed, u16 state);
InputStates getJoyStates();

#endif
