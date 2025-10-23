#include <genesis.h>
#include "../../headers/handlers/buttonAnimationHandler.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/handlers/commonMiniGameHandler.h"

bool isButtonAnimationActive = false;
u16 buttonAnimationType = 0;
u16 buttonCountDown = 1;

void buttonAnimation() {
  if (isButtonAnimationActive) {
    u16 buttonAnimationsArray[3] = {};
    switch (buttonAnimationType) {
    case 0: // X button animation
      buttonAnimationsArray[0] = 4;
      buttonAnimationsArray[1] = 18;
      buttonAnimationsArray[2] = 19;
      buttonAnimationProcess(3, buttonAnimationsArray);
      break;
    case 1: // Y button animation
      buttonAnimationsArray[0] = 5;
      buttonAnimationsArray[1] = 20;
      buttonAnimationsArray[2] = 21;
      buttonAnimationProcess(4, buttonAnimationsArray);
      break;
    case 2: // Z button animation
      buttonAnimationsArray[0] = 6;
      buttonAnimationsArray[1] = 22;
      buttonAnimationsArray[2] = 23;
      buttonAnimationProcess(5, buttonAnimationsArray);
      break;
    case 3: // A button animation
      buttonAnimationsArray[0] = 1;
      buttonAnimationsArray[1] = 24;
      buttonAnimationsArray[2] = 25;
      buttonAnimationProcess(6, buttonAnimationsArray);
      break;
    case 4: // B button animation
      buttonAnimationsArray[0] = 2;
      buttonAnimationsArray[1] = 26;
      buttonAnimationsArray[2] = 27;
      buttonAnimationProcess(7, buttonAnimationsArray);
      break;
    case 5: // C btton animation
      buttonAnimationsArray[0] = 3;
      buttonAnimationsArray[1] = 28;
      buttonAnimationsArray[2] = 29;
      buttonAnimationProcess(8, buttonAnimationsArray);
      break;
    }
  }
}

void setButtonAnimationState(u16 buttonType, bool state) {
  buttonAnimationType = buttonType;
  isButtonAnimationActive = state;
}

void buttonAnimationProcess(u16 buttonIndex, u16 buttonType[]) {
  bool passState = getTick() % 25 == 0;
  if (passState && buttonCountDown >= 0) {
    printInt(4, 6, buttonCountDown);
    if (buttonCountDown == 0) {
      getButtonsInPopUp()[buttonIndex].idTag = buttonType[buttonCountDown]; // Set default X shape button
      buttonCountDown = 2;
      isButtonAnimationActive = false;
    } else if (buttonCountDown == 1) {
      getButtonsInPopUp()[buttonIndex].idTag = buttonType[buttonCountDown]; // Set X fill shape
      buttonCountDown--;
    } else if (buttonCountDown == 2) {
      getButtonsInPopUp()[buttonIndex].idTag = buttonType[buttonCountDown]; // Set X fill shape and border
      buttonCountDown--;
    }
  }
}

bool isButtonAnimation() {
  return isButtonAnimationActive;
}
