#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/scenes/mainMenuScene.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/handlers/inputHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/scenes/mainMenuConstantsScene.h"
#include "../../headers/handlers/commonStructHandler.h"

MainMenuPopupData metaData;

Scene mainMenuSceneInit() {
  mainMenuSceneLoadTiles();
  PAL_setPalette(PAL1, mainMenuPalette.data, DMA);

  VDP_drawText("Brain Wipe", 15, 2);
  setRandomSeed(getTick());

  // Init popup metadata
  metaData.mainSelectorIndex = 0;
  metaData.loadSelectorIndex = 0;
  metaData.loadSelectorPosition.x = 3;
  metaData.loadSelectorPosition.y = 1;
  metaData.mainSelectorPosition.x = 1;
  metaData.mainSelectorPosition.y = 1;
  metaData.currentPopup = MAIN_MENU_POPUP_BOX;
  metaData.borderPosition.x = 2;
  metaData.borderPosition.y = 2;
  metaData.borderSize.w = 8;
  metaData.borderSize.h = 9;
  metaData.borderTilesData.topRight = BORDER_TOP_RIGHT;
  metaData.borderTilesData.topLeft = BORDER_TOP_LEFT;
  metaData.borderTilesData.bottomRight = BORDER_BOTTOM_RIGHT;
  metaData.borderTilesData.bottomLeft = BORDER_BOTTOM_LEFT;
  metaData.borderTilesData.topSide = BORDER_TOP_SIDE;
  metaData.borderTilesData.leftSide = BORDER_LEFT_SIDE;
  metaData.borderTilesData.rightSide = BORDER_RIGHT_SIDE;
  metaData.borderTilesData.bottomSide = BORDER_BOTTOM_SIDE;
  metaData.borderTilesData.fill = BORDER_FILL;
  metaData.cursorTilesData.up = UP_CURSOR;
  metaData.cursorTilesData.down = DOWN_CURSOR;
  metaData.cursorTilesData.aButton = A_SELECTOR_BUTTON;
  metaData.cursorTilesData.right = RIGHT_CURSOR;
  metaData.verticalScrollMainWindow.upPosition.x = 8;
  metaData.verticalScrollMainWindow.upPosition.y = 4;
  metaData.verticalScrollMainWindow.downPosition.x = 8;
  metaData.verticalScrollMainWindow.downPosition.y = 8;
  metaData.mainAButtonPosition.x = 3;
  metaData.mainAButtonPosition.y = 5;
  metaData.mainCursorRightPosition.x = 4;
  metaData.mainCursorRightPosition.y = 5;

  return createScene("main menu", 0, SCENE_MAIN_MENU);
}

void mainMenuSceneLoadTiles() {
  u16 ind = TILE_USER_INDEX;

  VDP_loadTileSet(mainMenuBorder.tileset, ind, DMA);
  ind += mainMenuBorder.tileset->numTile;

  VDP_loadTileSet(mainMenuAlphabetUa.tileset, ind, DMA);
  ind += mainMenuAlphabetUa.tileset->numTile;

  VDP_loadTileSet(mainMenuSelectorButtons.tileset, ind, DMA);
  ind += mainMenuAlphabetUa.tileset->numTile;
}

void mainMenuSceneUnloadTiles() {
  VDP_resetScreen();
}

void mainMenuSceneUpdate() {
  drawBorder(metaData.borderPosition, metaData.borderSize,
             metaData.borderTilesData);

  drawVerticalScroll(metaData.verticalScrollMainWindow.upPosition,
                     metaData.verticalScrollMainWindow.downPosition,
                     metaData.cursorTilesData);
  // Draw A cursor button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.aButton),
      metaData.mainAButtonPosition.x, metaData.mainAButtonPosition.y);
  // Draw Right cursor arrow button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.right),
      metaData.mainCursorRightPosition.x, metaData.mainCursorRightPosition.y);
  // Draw Text in border

  printInt(0, 0, getTick()); // print current frame from start of rom
}

void mainMenuSceneSelectorHandle(u16 typePopUp, u16 typeDiraction) {
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

void mainMenuSceneInputHandler() {
  if (getJoyStates().startButton) {
  }
  if (getJoyStates().xButton) {
  }
  if (getJoyStates().yButton) {
  }
  if (getJoyStates().zButton) {
  }
  if (getJoyStates().aButton) {
    if (metaData.currentPopup == MAIN_MENU_POPUP_BOX) {
      if (metaData.mainSelectorIndex == 1) {
        metaData.currentPopup = MAIN_MENU_LOAD_POPUP_BOX;
      } else if (metaData.mainSelectorIndex == 0) {
        mainMenuSceneUnloadTiles();
        setScene(SCENE_HIDEOUT);
      }
    }
  }
  if (getJoyStates().bButton) {
    if (metaData.currentPopup == MAIN_MENU_LOAD_POPUP_BOX) {
      metaData.currentPopup = MAIN_MENU_POPUP_BOX;
    }
  }
  if (getJoyStates().cButton) {
  }
  if (getJoyStates().upButton) {
    if (metaData.currentPopup == MAIN_MENU_POPUP_BOX) {
      mainMenuSceneSelectorHandle(MAIN_MENU_POPUP_BOX,
                                  MAIN_MENU_MOVE_SELECTOR_UP);
    } else if (metaData.currentPopup == MAIN_MENU_LOAD_POPUP_BOX) {
      mainMenuSceneSelectorHandle(MAIN_MENU_LOAD_POPUP_BOX,
                                  MAIN_MENU_MOVE_SELECTOR_UP);
    }
  }
  if (getJoyStates().downButton) {
    if (metaData.currentPopup == MAIN_MENU_POPUP_BOX) {
      mainMenuSceneSelectorHandle(MAIN_MENU_POPUP_BOX,
                                  MAIN_MENU_MOVE_SELECTOR_DOWN);
    } else if (metaData.currentPopup == MAIN_MENU_LOAD_POPUP_BOX) {
      mainMenuSceneSelectorHandle(MAIN_MENU_LOAD_POPUP_BOX,
                                  MAIN_MENU_MOVE_SELECTOR_DOWN);
    }
  }
}
