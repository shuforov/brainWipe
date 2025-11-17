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
  u16 selectorIndex;
  Vec2 borderPosition;
  SizeBox borderSize;
  VerticalScrollTransform verticalScroll;
  Vec2 aButtonPosition;
  u16 titleTiles[10];
  Vec2 titlePosition;
  u16 newGameTiles[8];
  Vec2 newGamePosition;
  u16 loadTiles[11];
  Vec2 loadPosition;
  Vec2 cursorRightPosition;
} MainMenuWindowData;

typedef struct {
  u16 titleTiles[11];
  Vec2 titlePosition;
  u16 slotTiles[7];
  Vec2 slotPosition;
  u16 selectorIndex;
  Vec2 selectorPosition;
  Vec2 aButtonPosition;
  Vec2 bButtonPosition;
  Vec2 borderPosition;
  SizeBox borderSize;
  VerticalScrollTransform verticalScroll;
  Vec2 cursorRightPosition;
  Vec2 cursorLeftPosition;
} LoadMenuWindowData;

typedef struct {
  MainMenuWindowData mainMenuMetaData;
  LoadMenuWindowData loadMenuMetaData;
  u16 currentPopup;
  BorderTiles borderTilesData;
  VerticalScrollTransform verticalScrollLoadWindow;
  CursorTiles cursorTilesData;
} MainMenuPopupData;

Scene mainMenuSceneInit();
void mainMenuSceneLoadTiles();
void mainMenuSceneUpdate();
void mainMenuSceneInputHandler();
void mainMenuSceneSelectorHandle(u16 typePopUp, u16 typeDiraction);
void mainMenuSceneUnloadTiles();
void mainMenuDrawMainWindow();
void mainMenuDrawMainCursor();
void mainMenuDrawLoadWindow();
void mainMenuMainWindowInit();
void mainMenuLoadWindowInit();
void mainMenuDrawLoadCursor();
void mainMenuMetaDataInit();

#endif
