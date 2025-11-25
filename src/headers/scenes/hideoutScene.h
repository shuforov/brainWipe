#ifndef HIDEOUT_SCENE_H
#define HIDEOUT_SCENE_H

#include "../scenes/scene.h"
#include "../handlers/commonStructHandler.h"

Scene hideoutSceneInit();
void hideoutSceneUpdate();
void hideoutSceneInputHandler();
void hideoutSceneLoadTiles();
void hideoutSceneSelectorHandle(u16 typeFocus, u16 typeButton);
void hideoutSceneDrawPlayerAvatar(Vec2 avatarPosition);

#endif
