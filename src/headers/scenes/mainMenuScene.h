#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "scene.h"
#include "../handlers/commonStructHandler.h"

typedef enum {
  MAIN_MENU_POPUP_BOX,
  MAIN_MENU_LOAD_POPUP_BOX
} MainMenuPopupTypes;

typedef enum {
  MAIN_MENU_MOVE_SELECTOR_UP,
  MAIN_MENU_MOVE_SELECTOR_DOWN
} MainMenuPopupDiraction;

typedef struct {
  u16 mainSelectorIndex;
  u16 loadSelectorIndex;
  Vec2 mainSelectorPosition;
  Vec2 loadSelectorPosition;
  u16 currentPopup;
  Vec2 borderPosition;
  SizeBox borderSize;
  BorderTiles borderTilesData;
  VerticalScrollTransform verticalScrollMainWindow;
  VerticalScrollTransform verticalScrollLoadWindow;
  Vec2 mainAButtonPosition;
  Vec2 loadAButtonPosition;
  Vec2 loadBButtonPosition;
  CursorTiles cursorTilesData;
  Vec2 mainCursorRightPosition;
  u16 mainMenuTextTiles[4];
  Vec2 mainMenuTextPosition;
} MainMenuPopupData;

Scene mainMenuSceneInit();
void mainMenuSceneLoadTiles();
void mainMenuSceneUpdate();
void mainMenuSceneInputHandler();
void mainMenuSceneSelectorHandle(u16 typePopUp, u16 typeDiraction);
void mainMenuSceneUnloadTiles();

#endif
