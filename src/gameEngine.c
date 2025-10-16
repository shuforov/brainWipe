#include "gameEngine.h"
#include "miniGame.h"
#include <../res/resources.h>
#include <genesis.h>

void init() {
  loadAllTileSets();
  PAL_setPalette(PAL1, borderTiles.palette->data, DMA);

  PAL_setColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
  drawPopup(10, 8, 12, 8);

  VDP_drawText("Hello Mega Drive World!", 10, 20);
}

void loadAllTileSets() {
  u16 ind = TILE_USER_INDEX;

  VDP_loadTileSet(borderTiles.tileset, ind, DMA);
  ind += borderTiles.tileset->numTile;

  VDP_loadTileSet(alphabetUa.tileset, ind, DMA);
  ind += alphabetUa.tileset->numTile;

  VDP_loadTileSet(buttonShape.tileset, ind, DMA);
  ind += buttonShape.tileset->numTile;
}
