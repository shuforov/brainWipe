#include <genesis.h>
#include <../res/resources.h>
#include "../headers/miniGame.h"
#include "../headers/gameEngine.h"
#include "../headers/miniGameConstants.h"
#include "../headers/handlers/drawButtonHandler.h"

bool isRendered = false;
u16 curW = 3;
u16 curH = 3;
u16 countDown = 5;
u16 buttonCountDown = 1;
bool isCountDownGo = false;
bool isButtonAnimationActive = false;
u16 buttonAnimationType = 0;
struct popUpTransform popUpData;
struct buttonMetadata buttonsInPopUp[] = {
    {11, 9, 0},  // count down timer
    {13, 9, 0},  // end status of minigame
    {15, 9, 0},  // rounds count of minigames
    {11, 11, 4}, // X button
    {13, 11, 5}, // Y button
    {15, 11, 6}, // Z button
    {11, 13, 1}, // A button
    {13, 13, 2}, // B buutton
    {15, 13, 3}, // C button
};

void drawPopup(u16 x, u16 y, u16 w, u16 h) {
  // e.g. w = 5, h = 4 gives you a 5x4 popup box

  // corners
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_TOP_LEFT), x, y);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_TOP_RIGHT),
                   x + w - 1, y);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BOTTOM_LEFT), x,
                   y + h - 1);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BOTTOM_RIGHT),
                   x + w - 1, y + h - 1);

  // top and bottom edges
  for (u16 i = 1; i < w - 1; i++) {
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_TOP_EDGE), x + i,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BOTTOM_EDGE),
                     x + i, y + h - 1);
  }

  // left and right edges
  for (u16 j = 1; j < h - 1; j++) {
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_LEFT_EDGE), x, y + j);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_RIGHT_EDGE), x + w - 1, y + j);
  }

  // fill center
  for (u16 j = 1; j < h - 1; j++) {
    for (u16 i = 1; i < w - 1; i++) {
      VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BLACK), x + i, y + j);
    }
  }
}

void countDownGo() {
  if (isCountDownGo) {
    bool secondPass = getTick() % 240 == 0;
    if (secondPass && countDown >= 0) {
      printInt(4, 5, countDown);
      if (countDown == 0) {
	buttonsInPopUp[0].idTag = 17; // set button shape to GO state
        setCountDownGo(false);
        countDown = 5;
      } else {
	buttonsInPopUp[0].idTag = BUTTON_NUMBERS[countDown];
        countDown--;
      }
    }
  }
}

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
      buttonsInPopUp[buttonIndex].idTag = buttonType[buttonCountDown]; // Set default X shape button
      buttonCountDown = 2;
      isButtonAnimationActive = false;
    } else if (buttonCountDown == 1) {
      buttonsInPopUp[buttonIndex].idTag = buttonType[buttonCountDown]; // Set X fill shape
      buttonCountDown--;
    } else if (buttonCountDown == 2) {
      buttonsInPopUp[buttonIndex].idTag = buttonType[buttonCountDown]; // Set X fill shape and border
      buttonCountDown--;
    }
  }
}

bool isButtonAnimation() {
  return isButtonAnimationActive;
}

void drawButtons() {
  for (int i = 0; i < 9; i++) {
    drawButtonShape(buttonsInPopUp[i].x, buttonsInPopUp[i].y,
                    buttonsInPopUp[i].idTag);
  }
}

void setCountDownGo(bool value) {
  isCountDownGo = value;
}

bool popUpAnimation(u16 x, u16 y, u16 w, u16 h) {
  popUpData.x = x;
  popUpData.y = y;
  popUpData.w = w;
  popUpData.h = h;
  if (isRendered) {
    drawPopup(x, y, w, h);
    return true;
  }
  if ((getTick() % 20) == 0) { // every 1/4 of second
    if (w != curW || h != curH) {
      if (curW < w) {
        drawPopup(x, y, curW, curH);
        curW++;
      }
      if (curH < h) {
        drawPopup(x, y, curW, curH);
        curH++;
      }
    } else {
      isRendered = true;
      curH = 3;
      curW = 3;
      return true;
    }
  }
  return false;
}
