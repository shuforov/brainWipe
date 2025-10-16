#include <genesis.h>
#include <../res/resources.h>
#include "miniGame.h"

// tile indices in your sheet

const u16 TILE_TOP_RIGHT = TILE_USER_INDEX + 0;
const u16 TILE_BOTTOM_RIGHT = TILE_USER_INDEX + 1;
const u16 TILE_BOTTOM_LEFT = TILE_USER_INDEX + 2;
const u16 TILE_RIGHT_EDGE = TILE_USER_INDEX + 3;
const u16 TILE_TOP_EDGE = TILE_USER_INDEX + 4;
const u16 TILE_LEFT_EDGE = TILE_USER_INDEX + 5;
const u16 TILE_BLACK = TILE_USER_INDEX + 6;
const u16 TILE_BOTTOM_EDGE = TILE_USER_INDEX + 7;
const u16 TILE_TOP_LEFT = TILE_USER_INDEX + 8;

void drawPopup(u16 x, u16 y, u16 w, u16 h) {
  // w and h are in number of 16x16 tiles (minimum 3x3)
  // e.g. w = 5, h = 4 gives you a 5x4 popup box
    
  // corners
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_TOP_LEFT), x, y);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_TOP_RIGHT),
                   x + w - 1, y);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BOTTOM_LEFT), x,
                   y + h - 1);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BOTTOM_RIGHT),
                   x + w - 1, y + h - 1);

  // top and bottom edges
  for (u16 i = 1; i < w - 1; i++) {
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_TOP_EDGE), x + i,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BOTTOM_EDGE),
                     x + i, y + h - 1);
  }

  // left and right edges
  for (u16 j = 1; j < h - 1; j++) {
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_LEFT_EDGE), x, y + j);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_RIGHT_EDGE), x + w - 1, y + j);
  }

  // fill center
  for (u16 j = 1; j < h - 1; j++) {
    for (u16 i = 1; i < w - 1; i++) {
      VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BLACK), x + i, y + j);
    }
  }
}
