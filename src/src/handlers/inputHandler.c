#include <genesis.h>
#include "../../headers/handlers/inputHandler.h"
#include "../../headers/scenes/scene.h"

InputStates joyStates = {0}; // init all values to false state

void joyUpdate(u16 joy, u16 chaged, u16 state) {
  if (joy == JOY_1) {
    joyOne(joy, chaged, state);
  }
}

void joyOne(u16 joy, u16 changed, u16 state) {
  if (changed & BUTTON_START) {
    joyStates.startButton = !joyStates.startButton;
  }
  if (changed & BUTTON_X) {
    joyStates.xButton = !joyStates.xButton;
  }
  if (changed & BUTTON_Y) {
    joyStates.yButton = !joyStates.yButton;
  }
  if (changed & BUTTON_Z) {
    joyStates.zButton = !joyStates.zButton;
  }
  if (changed & BUTTON_A) {
    joyStates.aButton = !joyStates.aButton;
  }
  if (changed & BUTTON_B) {
    joyStates.bButton = !joyStates.bButton;
  }
  if (changed & BUTTON_C) {
    joyStates.cButton = !joyStates.cButton;
  }
  if (changed & BUTTON_UP) {
    joyStates.upButton = !joyStates.upButton;
  }
  if (changed & BUTTON_DOWN) {
    joyStates.downButton = !joyStates.downButton;
  }
  if (changed & BUTTON_LEFT) {
    joyStates.leftButton = !joyStates.leftButton;
  }
  if (changed & BUTTON_RIGHT) {
    joyStates.rightButton = !joyStates.rightButton;
  }
  if (state & BUTTON_START) {
    sceneInputHandle();
  }
  if (state & BUTTON_X) {
    sceneInputHandle();
  }
  if (state & BUTTON_Y) {
    sceneInputHandle();
  }
  if (state & BUTTON_Z) {
    sceneInputHandle();
  }
  if (state & BUTTON_A) {
    sceneInputHandle();
  }
  if (state & BUTTON_B) {
    sceneInputHandle();
  }
  if (state & BUTTON_C) {
    sceneInputHandle();
  }
  if (state & BUTTON_UP) {
    sceneInputHandle();
  }
  if (state & BUTTON_DOWN) {
    sceneInputHandle();
  }
  if (state & BUTTON_LEFT) {
    sceneInputHandle();
  }
  if (state & BUTTON_RIGHT) {
    sceneInputHandle();
  }
}

InputStates getJoyStates() { return joyStates; }
