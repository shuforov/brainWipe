#include <genesis.h>
#include <../res/resources.h>
#include "../headers/gameEngine.h"
#include "../headers/miniGame.h"
#include "../headers/handlers/debugHandler.h"
#include "../headers/handlers/buttonAnimationHandler.h"
#include "../headers/handlers/inputHandler.h"

void init() {
  // init inputs
  JOY_init();
  JOY_setEventHandler(&myJoyHandler);

  loadTiles();
  PAL_setPalette(PAL1, borderTiles.palette->data, DMA);

  // Set background color
  PAL_setColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
  VDP_drawText("Hello!", 10, 20);
  setRandomSeed(getTick());
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

void update() {
  bool popUpRendered = popUpAnimation(10, 8, 8, 8);

  if (popUpRendered) {
    drawButtons();
  }

  if (getCountDownActive()) {
    countDownStateProcess();
  }
  if (isButtonAnimation()) {
    buttonAnimation();
  }
  if (isStadyButtonsAnimation()) {
    if (getCountDownActive()) {
      stadyButtonsAnimation();
    } else {
      setPuzzleButtonAnimation(true);
      setStadyButtonsAnimation(false);
    }
  }
  if (isTimerPieButtonAnimation()) {
    if (!isDelayTimerAnimation()) {
      timerPieButtonAnimation();
      if (isPuzzleProcessActive()) {
        if (sizeMgnaEqlPuzzlePlayerInputArray()) {
          if (checkPuzzlePlayerPass()) {
            KLog("its eql");
            stopMgna();
            winRound();
          } else {
            KLog("its NOT eql");
            stopMgna();
            lostRound();
          }
        }
      }
    }
  }
  if (isPuzzleButtonAnimation()) {
    if (!isDelayTimerAnimation())
      puzzleButtonAnimation();
  }

  if (isDelayTimerAnimation()) {
    delayTimerAnimationProcess();
  }

  printInt(10, 17, getTick()); // print current frame from start of rom
}

void myJoyHandler(u16 joy, u16 changed, u16 state) {
  joyUpdate(joy, changed, state);
}
