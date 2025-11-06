#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/scenes/mainMenuScene.h"
#include "../../headers/miniGame.h"
#include "../../headers/handlers/debugHandler.h"

Scene mainMenuSceneInit() {
  mainMenuSceneLoadTiles();
  PAL_setPalette(PAL1, commonPalette.data, DMA);

  // Set background color
  PAL_setColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
  VDP_drawText("Hello!", 10, 20);
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
  miniGameUpdate();

  printInt(10, 17, getTick()); // print current frame from start of rom
}
