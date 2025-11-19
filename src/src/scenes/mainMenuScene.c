#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/scenes/mainMenuScene.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/handlers/inputHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/commonStructHandler.h"

static const u16 NUMBERS_HEX[10] = {0x5F, 0x60, 0x61, 0x62, 0x63,
                                    0x64, 0x65, 0x66, 0x67, 0x68};
static const u16 MENU_TEXT[10] = {0x38, 0x28, 0x3E, 0x5B, BORDER_FILL,
                                  0x43, 0x28, 0x36, 0x47, 0x48};
static const u16 NEW_GAME_TEXT[8] = {0x39,        0x3F, 0x20, 0x1E,
                                     BORDER_FILL, 0x21, 0x46, 0x1E};
static const u16 LOAD_GAME_TEXT[11] = {0x27, 0x1E, 0x20, 0x1E, 0x3E, 0x48,
                                       0x1E, 0x2B, 0x32, 0x48, 0x32};
static const u16 LOAD_GAME_SLOT_TEXT[13] = {
    0x31,        0x3F,        0x3D,        0x33,        0x46,
    0x36,        0x1E,        BORDER_FILL, BORDER_FILL, BORDER_FILL,
    BORDER_FILL, BORDER_FILL, BORDER_FILL};
static const Vec2 MAIN_MENU_CURSOR_POSITIONS[4] = {(Vec2){3, 8}, (Vec2){4, 8},
                                                   (Vec2){3, 9}, (Vec2){4, 9}};
static const Vec2 LOAD_MENU_CURSOR_POSITIONS[20] = {
    (Vec2){22, 9},  (Vec2){21, 9},  (Vec2){22, 10}, (Vec2){21, 10},
    (Vec2){22, 11}, (Vec2){21, 11}, (Vec2){22, 12}, (Vec2){21, 12},
    (Vec2){22, 13}, (Vec2){21, 13}, (Vec2){22, 14}, (Vec2){21, 14},
    (Vec2){22, 15}, (Vec2){21, 15}, (Vec2){22, 16}, (Vec2){21, 16},
    (Vec2){22, 17}, (Vec2){21, 17}, (Vec2){22, 18}, (Vec2){21, 18}};

static MainMenuPopupData metaData;

Scene mainMenuSceneInit() {
  mainMenuSceneLoadTiles();
  PAL_setPalette(PAL1, mainScenesPalette.data, DMA);

  VDP_drawText("Brain Wipe", 15, 2);
  setRandomSeed(getTick());

  // Init popup metadata
  mainMenuMetaDataInit();

  // DRAW ENTITIES
  mainMenuDrawMainWindow();
  return createScene("main menu", 0, SCENE_MAIN_MENU);
}

void mainMenuMetaDataInit() {
  metaData.currentPopup = MAIN_MENU_POPUP_BOX;
  metaData.borderTilesData =
      (BorderTiles){BORDER_TOP_RIGHT,   BORDER_TOP_LEFT,    BORDER_BOTTOM_RIGHT,
                    BORDER_BOTTOM_LEFT, BORDER_TOP_SIDE,    BORDER_LEFT_SIDE,
                    BORDER_RIGHT_SIDE,  BORDER_BOTTOM_SIDE, BORDER_FILL};
  metaData.cursorTilesData = (CursorTiles){LEFT_CURSOR,
                                           RIGHT_CURSOR,
                                           UP_CURSOR,
                                           DOWN_CURSOR,
                                           A_SELECTOR_BUTTON,
                                           B_SELECTOR_BUTTON,
                                           0,
                                           0,
                                           0,
                                           0};
  // MainMenu data
  mainMenuMainWindowInit();
  // LoadMenu data
  mainMenuLoadWindowInit();  
}

void mainMenuLoadWindowInit() {
  metaData.loadMenuMetaData.selectorIndex = 0;
  metaData.loadMenuMetaData.selectorPosition = (Vec2){13, 7};
  metaData.loadMenuMetaData.borderPosition = (Vec2){19, 6};
  metaData.loadMenuMetaData.borderSize = (SizeBox){19, 15};
  metaData.loadMenuMetaData.verticalScroll.upPosition = (Vec2){36, 8};
  metaData.loadMenuMetaData.verticalScroll.downPosition = (Vec2){36, 19};
  memcpy(metaData.loadMenuMetaData.titleTiles, LOAD_GAME_TEXT,
         sizeof(LOAD_GAME_TEXT));
  metaData.loadMenuMetaData.titlePosition = (Vec2){23, 7};
  metaData.loadMenuMetaData.cursorRightPosition = (Vec2){22, 9};
  metaData.loadMenuMetaData.cursorLeftPosition = (Vec2){22, 8};
  metaData.loadMenuMetaData.aButtonPosition = (Vec2){21, 9};
  metaData.loadMenuMetaData.bButtonPosition = (Vec2){21, 8};  
}

void mainMenuMainWindowInit() {
  metaData.mainMenuMetaData.selectorIndex = 0;
  metaData.mainMenuMetaData.borderPosition = (Vec2){2, 5};
  metaData.mainMenuMetaData.borderSize = (SizeBox){17, 9};
  metaData.mainMenuMetaData.verticalScroll.upPosition = (Vec2){17, 7};
  metaData.mainMenuMetaData.verticalScroll.downPosition = (Vec2){17, 12};
  metaData.mainMenuMetaData.aButtonPosition = (Vec2){3, 8};
  metaData.mainMenuMetaData.cursorRightPosition = (Vec2){4, 8};
  memcpy(metaData.mainMenuMetaData.titleTiles, MENU_TEXT, sizeof(MENU_TEXT));
  metaData.mainMenuMetaData.titlePosition = (Vec2){4, 6};
  memcpy(metaData.mainMenuMetaData.newGameTiles, NEW_GAME_TEXT,
         sizeof(NEW_GAME_TEXT));
  metaData.mainMenuMetaData.newGamePosition = (Vec2){5, 8};
  memcpy(metaData.mainMenuMetaData.loadTiles, LOAD_GAME_TEXT,
         sizeof(LOAD_GAME_TEXT));
  metaData.mainMenuMetaData.loadPosition = (Vec2){5, 9};
}

void mainMenuDrawMainWindow() {
  // Draw border
  drawBorder(metaData.mainMenuMetaData.borderPosition, metaData.mainMenuMetaData.borderSize,
             metaData.borderTilesData);
  // Draw vertical scroll
  drawVerticalScroll(metaData.mainMenuMetaData.verticalScroll.upPosition,
                     metaData.mainMenuMetaData.verticalScroll.downPosition,
                     metaData.cursorTilesData);
  // Draw cursor  
  mainMenuDrawMainCursor();
  // Draw Text in border
  // Draw title
  drawTextTiles(metaData.mainMenuMetaData.titlePosition,
                metaData.mainMenuMetaData.titleTiles,
                ARRAY_LEN(metaData.mainMenuMetaData.titleTiles));
  // Draw new game text
  drawTextTiles(metaData.mainMenuMetaData.newGamePosition,
                metaData.mainMenuMetaData.newGameTiles,
                ARRAY_LEN(metaData.mainMenuMetaData.newGameTiles));
  // Draw load game text
  drawTextTiles(metaData.mainMenuMetaData.loadPosition,
                metaData.mainMenuMetaData.loadTiles,
                ARRAY_LEN(metaData.mainMenuMetaData.loadTiles));
}

void mainMenuDrawMainCursor() {
  // Clear tiles
  for (u16 i = 0; i < ARRAY_LEN(MAIN_MENU_CURSOR_POSITIONS); i++) {
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.borderTilesData.fill),
        MAIN_MENU_CURSOR_POSITIONS[i].x, MAIN_MENU_CURSOR_POSITIONS[i].y);
  }
  // Draw A cursor button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.aButton),
      metaData.mainMenuMetaData.aButtonPosition.x,
      metaData.mainMenuMetaData.aButtonPosition.y);
  // Draw Right cursor arrow button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.right),
      metaData.mainMenuMetaData.cursorRightPosition.x,
      metaData.mainMenuMetaData.cursorRightPosition.y);
}

void mainMenuDrawLoadWindow() {
  // Draw border
  drawBorder(metaData.loadMenuMetaData.borderPosition,
             metaData.loadMenuMetaData.borderSize, metaData.borderTilesData);
  // Draw vertical scroll
  drawVerticalScroll(metaData.loadMenuMetaData.verticalScroll.upPosition,
                     metaData.loadMenuMetaData.verticalScroll.downPosition,
                     metaData.cursorTilesData);
  // Draw text in border
  // Draw title
  drawTextTiles(metaData.loadMenuMetaData.titlePosition,
                metaData.loadMenuMetaData.titleTiles,
                ARRAY_LEN(metaData.loadMenuMetaData.titleTiles));
  // Draw cursor
  mainMenuDrawLoadCursor();
  // Draw slots
  SaveData testArraySlots[9] = {(SaveData){0x27, 0x1F, 0x28, 0x46, 0x28, 0x2B,
                                           0x28, 0x3E, 0x3E, 0x5C, 0x60,
                                           BORDER_FILL, BORDER_FILL}};
  for (u16 i = 1; i < 9; i++) {
    u16 tempArray[13] = {};
    memcpy(tempArray, LOAD_GAME_SLOT_TEXT, sizeof(LOAD_GAME_SLOT_TEXT));
    tempArray[7] = BORDER_FILL;
    tempArray[8] = NUMBERS_HEX[i];
    memcpy(&testArraySlots[i], tempArray, sizeof(tempArray));
  }

  for (u16 i = 0; i < 9; i++) {
    if (ARRAY_LEN(testArraySlots[i].nameHex) > 0) {
      drawTextTiles((Vec2){23, 9 + i}, testArraySlots[i].nameHex,
                    ARRAY_LEN(testArraySlots[i].nameHex));
    }
  }
}

void mainMenuDrawLoadCursor() {
  // Clear tiles
  for (u16 i = 0; i < ARRAY_LEN(LOAD_MENU_CURSOR_POSITIONS); i++) {
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.borderTilesData.fill),
        LOAD_MENU_CURSOR_POSITIONS[i].x, LOAD_MENU_CURSOR_POSITIONS[i].y);
  }
  // Draw A cursor button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.aButton),
      metaData.loadMenuMetaData.aButtonPosition.x,
      metaData.loadMenuMetaData.aButtonPosition.y);
  // Draw Right cursor arrow button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.right),
      metaData.loadMenuMetaData.cursorRightPosition.x,
      metaData.loadMenuMetaData.cursorRightPosition.y);
  // Draw B cursor button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.bButton),
      metaData.loadMenuMetaData.bButtonPosition.x,
      metaData.loadMenuMetaData.bButtonPosition.y);
  // Draw Left cursor arrow button
  VDP_setTileMapXY(BG_A,
                   TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.left),
                   metaData.loadMenuMetaData.cursorLeftPosition.x,
                   metaData.loadMenuMetaData.cursorLeftPosition.y);
}

void mainMenuSceneLoadTiles() {
  u16 ind = TILE_USER_INDEX;

  VDP_loadTileSet(scenesBorder.tileset, ind, DMA);
  ind += scenesBorder.tileset->numTile;

  VDP_loadTileSet(scenesAlphabetUa.tileset, ind, DMA);
  ind += scenesAlphabetUa.tileset->numTile;

  VDP_loadTileSet(scenesSelectorButtons.tileset, ind, DMA);
  ind += scenesAlphabetUa.tileset->numTile;
}

void mainMenuSceneUnloadTiles() {
  VDP_resetScreen();
}

void mainMenuSceneUpdate() {
  printInt(0, 0, getTick()); // print current frame from start of rom
}

void mainMenuSceneSelectorHandle(u16 typePopUp, u16 typeDiraction) {
  if (typePopUp == MAIN_MENU_POPUP_BOX) {
    if (typeDiraction == MAIN_MENU_MOVE_SELECTOR_UP) {
      if (metaData.mainMenuMetaData.selectorIndex > 0) {
        metaData.mainMenuMetaData.selectorIndex--;
        metaData.mainMenuMetaData.cursorRightPosition.y--;
        metaData.mainMenuMetaData.aButtonPosition.y--;
	mainMenuDrawMainCursor();        
      }
    } else if (typeDiraction == MAIN_MENU_MOVE_SELECTOR_DOWN) {
      if (metaData.mainMenuMetaData.selectorIndex < 1) {
        metaData.mainMenuMetaData.selectorIndex++;
        metaData.mainMenuMetaData.cursorRightPosition.y++;
        metaData.mainMenuMetaData.aButtonPosition.y++;
        mainMenuDrawMainCursor();
      }
    }
  } else if (typePopUp == MAIN_MENU_LOAD_POPUP_BOX) {
    if (typeDiraction == MAIN_MENU_MOVE_SELECTOR_UP) {
      if (metaData.loadMenuMetaData.selectorIndex > 0) {
        metaData.loadMenuMetaData.selectorIndex--;
        metaData.loadMenuMetaData.cursorRightPosition.y--;
        metaData.loadMenuMetaData.aButtonPosition.y--;
	mainMenuDrawLoadCursor();
      }
    } else if (typeDiraction == MAIN_MENU_MOVE_SELECTOR_DOWN) {
      if (metaData.loadMenuMetaData.selectorIndex < 9) {
        metaData.loadMenuMetaData.selectorIndex++;
        metaData.loadMenuMetaData.cursorRightPosition.y++;
        metaData.loadMenuMetaData.aButtonPosition.y++;
        mainMenuDrawLoadCursor();
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
      if (metaData.mainMenuMetaData.selectorIndex == 1) {
        metaData.currentPopup = MAIN_MENU_LOAD_POPUP_BOX;
        mainMenuDrawLoadWindow();
      } else if (metaData.mainMenuMetaData.selectorIndex == 0) {
        mainMenuSceneUnloadTiles();
        setScene(SCENE_HIDEOUT);
      }
    }
  }
  if (getJoyStates().bButton) {
    if (metaData.currentPopup == MAIN_MENU_LOAD_POPUP_BOX) {
      metaData.currentPopup = MAIN_MENU_POPUP_BOX;
      drawFillBox(metaData.loadMenuMetaData.borderPosition, metaData.loadMenuMetaData.borderSize, 0x0);
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
