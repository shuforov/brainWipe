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
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_LEFT_EDGE), x,
                     y + j);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_RIGHT_EDGE),
                     x + w - 1, y + j);
  }

  // fill center
  for (u16 j = 1; j < h - 1; j++) {
    for (u16 i = 1; i < w - 1; i++) {
      VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BLACK), x + i,
                       y + j);
    }
  }
}

void drawButtons() {
  for (int i = 0; i < 9; i++) {
    drawButtonShape(getButtonsInPopUp()[i].x, getButtonsInPopUp()[i].y,
                    getButtonsInPopUp()[i].idTag);
  }
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

void startMgna() {
  generateMgna(0, 5, 3);
  setCountDownState(1);
  getButtonsInPopUp()[1].idTag = 0; // reset to clear shape
}

bool sizeMgnaEqlPuzzlePlayerInputArray() {
  return getMgnaCounter() == getPuzzlePlayerInputArrayCounter();
}

bool checkPuzzlePlayerPass() { return mgnaEqlPpia(); }

bool isPuzzleProcessActive() { return getPuzzleWaitPlayerInput(); }

void stopMgna() {
  resetMgnaArray();
  resetPuzzlePlayerInputArray();
  setPuzzleWaitPlayerInput(false);
  setTimerPieButtonAnimation(false, 0);
  disableCountDown();
  getButtonsInPopUp()[0].idTag = 0; // reset to clear shape
}

void lostRound() {
  getButtonsInPopUp()[1].idTag = 45; // Swap to lose shape
}

void winRound() {
  getButtonsInPopUp()[1].idTag = 46; // Swap to success shape
}
