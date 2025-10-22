#include <genesis.h>
#include <../res/resources.h>
#include "gameEngine.h"
#include "miniGame.h"

u16 counter = 60;
u16 currentFrame = 0;

void init() {
  // init inputs
  JOY_init();
  JOY_setEventHandler(&myJoyHandler);

  loadTiles();
  PAL_setPalette(PAL1, borderTiles.palette->data, DMA);

  // Set background color
  PAL_setColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
  VDP_drawText("Hello!", 10, 20);
}

void loadTiles() {
  u16 ind = TILE_USER_INDEX;

  VDP_loadTileSet(borderTiles.tileset, ind, DMA);
  ind += borderTiles.tileset->numTile;

  VDP_loadTileSet(alphabetUa.tileset, ind, DMA);
  ind += alphabetUa.tileset->numTile;

  VDP_loadTileSet(buttonShape.tileset, ind, DMA);
  ind += buttonShape.tileset->numTile;
}

void printInt(u16 x, u16 y, u16 printNumber) {
  char currentFrameChar[6];

  sprintf(currentFrameChar, "%d", printNumber);
  VDP_clearTextArea(x, y, 5, 1);
  VDP_drawText(currentFrameChar, x, y);
}

void update() {
  bool popUpRendered = popUpAnimation(10, 8, 8, 8);

  if (popUpRendered) {
    drawButtons();
  }

  countDownGo();
  buttonAnimation();

  printInt(10, 17, getTick());
}

void myJoyHandler(u16 joy, u16 changed, u16 state) {
  if (joy == JOY_1) {
    if (state & BUTTON_START) {
      setCountDownGo(true);
    }
    if (state & BUTTON_X) {
      if (!isButtonAnimation()) {
        setButtonAnimationState(0, true);
      }
    }
    if (state & BUTTON_Y) {
      if (!isButtonAnimation()) {
        setButtonAnimationState(1, true);
      }
    }
    if (state & BUTTON_Z) {
      if (!isButtonAnimation()) {
        setButtonAnimationState(2, true);
      }
    }
    if (state & BUTTON_A) {
      if (!isButtonAnimation()) {
        setButtonAnimationState(3, true);
      }
    }
    if (state & BUTTON_B) {
      if (!isButtonAnimation()) {
        setButtonAnimationState(4, true);
      }
    }
    if (state & BUTTON_C) {
      if (!isButtonAnimation()) {
        setButtonAnimationState(5, true);
      }
    }
  }
}
