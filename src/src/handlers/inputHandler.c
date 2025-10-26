#include <genesis.h>
#include "../../headers/handlers/inputHandler.h"
#include "../../headers/handlers/buttonAnimationHandler.h"
#include "../../headers/handlers/commonMiniGameHandler.h"
#include "../../headers/miniGame.h"

void joyUpdate(u16 joy, u16 chaged, u16 state) {
  if (joy == JOY_1) {
    joyOne(joy, chaged, state);
  }
}

void joyOne(u16 joy, u16 changed, u16 state) {
  if (state & BUTTON_START) {
    /* setCountDownState(1); */
    /* if (!isButtonAnimation()) { */
    /*   setButtonAnimationState(6, true); */
    /* } */
    /* setTimerPieButtonAnimation(true, 12); // 12 sec of coundown timer
     * animation */
    startMgna();
  }
  if (state & BUTTON_X) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(0);
        setButtonAnimationState(0, true);
      }
    }
  }
  if (state & BUTTON_Y) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(1);
        setButtonAnimationState(1, true);
      }
    }
  }
  if (state & BUTTON_Z) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(2);
        setButtonAnimationState(2, true);
      }
    }
  }
  if (state & BUTTON_A) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(3);
        setButtonAnimationState(3, true);
      }
    }
  }
  if (state & BUTTON_B) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(4);
        setButtonAnimationState(4, true);
      }
    }
  }
  if (state & BUTTON_C) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(5);
        setButtonAnimationState(5, true);
      }
    }
  }
}
