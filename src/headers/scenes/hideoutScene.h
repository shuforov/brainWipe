#ifndef HIDEOUT_SCENE_H
#define HIDEOUT_SCENE_H

#include "../scenes/scene.h"
#include "../handlers/commonStructHandler.h"

Scene hideoutSceneInit();
void hideoutSceneUpdate();
void hideoutSceneInputHandler();
void hideoutTopPanelInit();
void hideoutDrawTopPanel();
void hideoutSceneLoadTiles();
void hideoutDrawTopPanelCursor();
void hideoutSceneSelectorHandle(u16 typeFocus, u16 typeButton);
void hideoutSceneClearOptionSpace();

#endif
