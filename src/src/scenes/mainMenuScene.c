#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/scenes/mainMenuScene.h"
#include "../../headers/miniGame.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/handlers/inputHandler.h"
#include "../../headers/handlers/buttonAnimationHandler.h"
#include "../../headers/handlers/commonMiniGameHandler.h"

Scene mainMenuSceneInit() {
  mainMenuSceneLoadTiles();
  PAL_setPalette(PAL1, commonPalette.data, DMA);

  VDP_drawText("Brain Wipe", 15, 2);
  setRandomSeed(getTick());

  // Start render minigame
  setPopUpRenderAnimationState(true);
  return createScene("main menu", 0, SCENE_MAIN_MENU);
}

void mainMenuSceneLoadTiles() {
  u16 ind = TILE_USER_INDEX;

  VDP_loadTileSet(borderTiles.tileset, ind, DMA);
  ind += borderTiles.tileset->numTile;

  VDP_loadTileSet(alphabetUa.tileset, ind, DMA);
  ind += alphabetUa.tileset->numTile;

  VDP_loadTileSet(buttonShape.tileset, ind, DMA);
  ind += buttonShape.tileset->numTile;
}

void mainMenuSceneUpdate() {
  printInt(0, 0, getTick()); // print current frame from start of rom
}

void mainMenuInputHandler() {
  if (getJoyStates().startButton) {
  }
  if (getJoyStates().xButton) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(0);
        setButtonAnimationState(0, true);
      }
    }
  }
  if (getJoyStates().yButton) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(1);
        setButtonAnimationState(1, true);
      }
    }
  }
  if (getJoyStates().zButton) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(2);
        setButtonAnimationState(2, true);
      }
    }
  }
  if (getJoyStates().aButton) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(3);
        setButtonAnimationState(3, true);
      }
    }
  }
  if (getJoyStates().bButton) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(4);
        setButtonAnimationState(4, true);
      }
    }
  }
  if (getJoyStates().cButton) {
    if (getPuzzleWaitPlayerInput()) {
      if (!isButtonAnimation()) {
        pushPuzzlePlayerInputArray(5);
        setButtonAnimationState(5, true);
      }
    }
  }
}
