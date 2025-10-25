#include <genesis.h>
#include "../../headers/handlers/buttonAnimationHandler.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/handlers/commonMiniGameHandler.h"
#include "../../headers/handlers/timerHandler.h"
#include "../../headers/miniGameConstants.h"

bool isButtonAnimationActive = false;
bool isStadyButtonsAnimationActive = false;
bool isTimerPieButtonAnimationActive = false;
bool isPuzzleButtonANimationActive = false;
u16 stadyButtonAnimationsArray[2] = {31, 30};
u16 buttonAnimationType = 0;
u16 buttonCountDown = 1;
u16 puzzleCounter;

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
    case 6: // Stady buttons animation
      buttonAnimationsArray[0] = 31;
      buttonAnimationsArray[1] = 30;
      buttonAnimationProcess(0, buttonAnimationsArray);
      break;
    }
  }
}

void setButtonAnimationState(u16 buttonType, bool state) {
  buttonAnimationType = buttonType;
  if (buttonType >= 0 && buttonType <= 5) {
    buttonCountDown =
        2; // Set button count down timer for X Y Z A B C buttons animation
  } else if (buttonType == 6) {
    buttonCountDown =
        1; // Set button count down timer for Stady button animation
  }
  isButtonAnimationActive = state;
}

void setStadyButtonsAnimation(bool state) {
  if (state) {
    isStadyButtonsAnimationActive = true;
  } else {
    isStadyButtonsAnimationActive = false;
    getButtonsInPopUp()[3].idTag = 4; // Set to X button
    getButtonsInPopUp()[4].idTag = 5; // Set to Y button
    getButtonsInPopUp()[5].idTag = 6; // Set to Z button
    getButtonsInPopUp()[6].idTag = 1; // Set to A button
    getButtonsInPopUp()[7].idTag = 2; // Set to B button
    getButtonsInPopUp()[8].idTag = 3; // Set to C button
  }
}

void buttonAnimationProcess(u16 buttonIndex, u16 buttonType[]) {
  bool passState = getTick() % 25 == 0;
  if (passState && buttonCountDown >= 0) {
    if (buttonCountDown == 0) {
      getButtonsInPopUp()[buttonIndex].idTag = buttonType[buttonCountDown]; // Set default BUTTON shape button
      buttonCountDown = 2;
      isButtonAnimationActive = false;
    } else {
      getButtonsInPopUp()[buttonIndex].idTag = buttonType[buttonCountDown]; // Set other BUTTON shape
      buttonCountDown--;
    }
  }
}

void stadyButtonsAnimation() {
  bool passState = getTick() % 120 == 0;
  if (passState && buttonCountDown >= 0) {
    if (buttonCountDown == 0) {
      buttonCountDown = 2;
    } else {
      buttonCountDown--;
    }
    for (int index = 3; index <= 8; index++) {
      getButtonsInPopUp()[index].idTag =
          stadyButtonAnimationsArray[buttonCountDown];
    }
  }
}

void setTimerPieButtonAnimation(bool state, u16 totalTime) {
  if (state) {
    setTimerTotalTime(totalTime);
    setTimerTimeLeft(totalTime);
    getButtonsInPopUp()[1].idTag = 44;
    isTimerPieButtonAnimationActive = true;
  } else {
    isTimerPieButtonAnimationActive = false;
  }
}

void timerPieButtonAnimation() {
  bool secondPass = getTick() % 240 == 0;
  if (secondPass) {
    if (getTimerTimeLeft() >= 6) {
      getButtonsInPopUp()[0].idTag = TIMER_SEGMENT_NUMBERS[getSegmentNum()];
    } else if (getTimerTimeLeft() <= 5) {
      getButtonsInPopUp()[0].idTag =
          TIMER_LAST_SEGMENT_NUMBERS[getSegmentNum()];
    }
    if (getTimerTimeLeft() == 0) {
      getButtonsInPopUp()[1].idTag = 45;
      setTimerPieButtonAnimation(false, 0);
    } else {
      setTimerTimeLeft(getTimerTimeLeft() - 1);
    }
  }
}

void setPuzzleButtonAnimation(bool state) {
  if (state) {
    puzzleCounter = 0;
    isPuzzleButtonANimationActive = true;
  } else {
    isPuzzleButtonANimationActive = false;
  }
}

void puzzleButtonAnimation() {
  bool passState = getTick() % 120 == 0;
  if (passState) {
    if (!isButtonAnimation()) {
      setButtonAnimationState(getMgna()[puzzleCounter], true);
      if (puzzleCounter == getMgnaCounter() - 1) {
        setPuzzleButtonAnimation(false);
      } else {
        puzzleCounter++;
      }
    }
  }
}

bool isButtonAnimation() { return isButtonAnimationActive; }

bool isStadyButtonsAnimation() { return isStadyButtonsAnimationActive; }

bool isTimerPieButtonAnimation() { return isTimerPieButtonAnimationActive; }

bool isPuzzleButtonAnimation() { return isPuzzleButtonANimationActive; }
