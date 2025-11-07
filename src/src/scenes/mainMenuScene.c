#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/scenes/mainMenuScene.h"
#include "../../headers/miniGame.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/handlers/inputHandler.h"
#include "../../headers/handlers/buttonAnimationHandler.h"
#include "../../headers/handlers/commonMiniGameHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/commonMiniGameHandler.h"

MainMenuPopupData metaData;

Scene mainMenuSceneInit() {
  mainMenuSceneLoadTiles();
  PAL_setPalette(PAL1, commonPalette.data, DMA);

  VDP_drawText("Brain Wipe", 15, 2);
  setRandomSeed(getTick());

  // Start render minigame
  setPopUpRenderAnimationState(true);

  // Init popup metadata
  metaData.mainSelectorIndex = 0;
  metaData.loadSelectorIndex = 0;
  metaData.loadSelectorPosition.x = 3;
  metaData.loadSelectorPosition.y = 1;
  metaData.mainSelectorPosition.x = 1;
  metaData.mainSelectorPosition.y = 1;
  metaData.currentPopup = MAIN_MENU_POPUP_BOX;

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
  drawButtonShape(metaData.mainSelectorPosition.x,
                  metaData.mainSelectorPosition.y, 0);
  drawButtonShape(metaData.loadSelectorPosition.x,
                  metaData.loadSelectorPosition.y, 0);
  printInt(0, 0, getTick()); // print current frame from start of rom
}

void mainMenuSelectorHandle(u16 typePopUp, u16 typeDiraction) {
  if (typePopUp == MAIN_MENU_POPUP_BOX) {
    if (typeDiraction == MAIN_MENU_MOVE_SELECTOR_UP) {
      if (metaData.mainSelectorIndex > 0) {
        drawButtonShape(metaData.mainSelectorPosition.x,
                        metaData.mainSelectorPosition.y, 47);
        metaData.mainSelectorIndex--;
        metaData.mainSelectorPosition.y--;
      }
    } else if (typeDiraction == MAIN_MENU_MOVE_SELECTOR_DOWN) {
      if (metaData.mainSelectorIndex < 1) {
        drawButtonShape(metaData.mainSelectorPosition.x,
                        metaData.mainSelectorPosition.y, 47);
        metaData.mainSelectorIndex++;
        metaData.mainSelectorPosition.y++;
      }
    }
  } else if (typePopUp == MAIN_MENU_LOAD_POPUP_BOX) {
    if (typeDiraction == MAIN_MENU_MOVE_SELECTOR_UP) {
      if (metaData.loadSelectorIndex > 0) {
        drawButtonShape(metaData.loadSelectorPosition.x,
                        metaData.loadSelectorPosition.y, 47);
        metaData.loadSelectorIndex--;
        metaData.loadSelectorPosition.y--;
      }
    } else if (typeDiraction == MAIN_MENU_MOVE_SELECTOR_DOWN) {
      if (metaData.loadSelectorIndex < 1) {
        drawButtonShape(metaData.loadSelectorPosition.x,
                        metaData.loadSelectorPosition.y, 47);
        metaData.loadSelectorIndex++;
        metaData.loadSelectorPosition.y++;
      }
    }
  }
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
    if (metaData.currentPopup == MAIN_MENU_POPUP_BOX) {
      metaData.currentPopup = MAIN_MENU_LOAD_POPUP_BOX;
    }
  }
  if (getJoyStates().bButton) {
    if (metaData.currentPopup == MAIN_MENU_LOAD_POPUP_BOX) {
      metaData.currentPopup = MAIN_MENU_POPUP_BOX;
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
  if (getJoyStates().upButton) {
    if (metaData.currentPopup == MAIN_MENU_POPUP_BOX) {
      mainMenuSelectorHandle(MAIN_MENU_POPUP_BOX, MAIN_MENU_MOVE_SELECTOR_UP);
    } else if (metaData.currentPopup == MAIN_MENU_LOAD_POPUP_BOX) {
      mainMenuSelectorHandle(MAIN_MENU_LOAD_POPUP_BOX,
                             MAIN_MENU_MOVE_SELECTOR_UP);
    }
  }
  if (getJoyStates().downButton) {
    if (metaData.currentPopup == MAIN_MENU_POPUP_BOX) {
      mainMenuSelectorHandle(MAIN_MENU_POPUP_BOX, MAIN_MENU_MOVE_SELECTOR_DOWN);
    } else if (metaData.currentPopup == MAIN_MENU_LOAD_POPUP_BOX) {
      mainMenuSelectorHandle(MAIN_MENU_LOAD_POPUP_BOX,
                             MAIN_MENU_MOVE_SELECTOR_DOWN);
    }
  }
}
