#include <genesis.h>
#include <../res/resources.h>
#include "../headers/miniGame.h"
#include "../headers/gameEngine.h"
#include "../headers/miniGameConstants.h"
#include "../headers/handlers/drawButtonHandler.h"
#include "../headers/handlers/buttonAnimationHandler.h"
#include "../headers/handlers/commonMiniGameHandler.h"
#include "../headers/handlers/debugHandler.h"

bool isRendered = false;
u16 curW = 3;
u16 curH = 3;
u16 countDown = 5;
bool countDownActive = false;
u16 countDownCurrentState;
struct popUpTransform popUpData;

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

void setCountDownState(u16 state) {
  switch (state) {
  case 0: // set button shape to GO state
    countDownCurrentState = 17;
    enableCountDown();
    break;
  case 1: // set button shape to Stady state
    countDownCurrentState = 31;
    enableCountDown();
    setStadyButtonsAnimation(true);
    break;
  }
}

void countDownStateProcess() {
  bool secondPass = getTick() % 240 == 0;
  if (secondPass && countDown >= 0) {
    if (countDown == 0) {
      getButtonsInPopUp()[0].idTag = countDownCurrentState;
      disableCountDown();
      setStadyButtonsAnimation(false);
      countDown = 5;
    } else {
      getButtonsInPopUp()[0].idTag = BUTTON_NUMBERS[countDown];
      countDown--;
    }
  }
}

void drawButtons() {
  for (int i = 0; i < 9; i++) {
    drawButtonShape(getButtonsInPopUp()[i].x, getButtonsInPopUp()[i].y,
                    getButtonsInPopUp()[i].idTag);
  }
}

void enableCountDown() { countDownActive = true; }

void disableCountDown() { countDownActive = false; }

bool getCountDownActive() { return countDownActive; }

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
