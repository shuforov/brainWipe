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
} MainMenuPopupData;

Scene mainMenuSceneInit();
void mainMenuSceneLoadTiles();
void mainMenuSceneUpdate();
void mainMenuInputHandler();
void mainMenuSelectorHandle(u16 typePopUp, u16 typeDiraction);

#endif
