#include <genesis.h>
#include "../../headers/scenes/hideoutScene.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/scenes/scene.h"

Scene hideoutSceneInit() {
  VDP_drawText("Hideout Scene", 15, 2);
  return createScene("hideout", 0, SCENE_HIDEOUT);
}

void hideoutSceneUpdate() {
  printInt(0, 0, getTick()); // print current frame from start of rom
}

void hideoutSceneInputHandler() {}
