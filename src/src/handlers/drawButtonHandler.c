#include <genesis.h>
#include "../../headers/miniGameConstants.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/commonStructHandler.h"

void drawFillBox(Vec2 position, SizeBox fillSize, u16 fillTile) {
  for (u16 j = 0; j < fillSize.h; j++) {
    for (u16 i = 0; i < fillSize.w; i++) {
      VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, fillTile),
                       position.x + i, position.y + j);
    }
  }
}

void drawTextTiles(Vec2 position, u16 tiles[], u16 tilesSize) {
  // Using special for drawing of text symbol array
  for (u16 i = 0; i < tilesSize; i++) {
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tiles[i]),
                     position.x + i, position.y);
  }
}

void drawTextTilesWHLimits(Vec2 position, u16 tiles[], u16 tilesSize, Vec2 limitPosition) {
  // Draw text tiles with width and height limitation coordinations
  if (position.x < limitPosition.x && position.y <= limitPosition.y) {
    Vec2 startPosition = position;
    Vec2 tilePosition = startPosition;
    for (u16 i = 0; i < tilesSize; i++) {
      if (tilePosition.y > limitPosition.y) {
        break;
      }
      if (tilePosition.x < limitPosition.x) {
        drawTile(tilePosition, tiles[i]);
        tilePosition.x++;
      } else if (tilePosition.x == limitPosition.x) {
        drawTile(tilePosition, tiles[i]);
        tilePosition.x = startPosition.x;
        tilePosition.y++;
      }
    }
  }
}

void drawTile(Vec2 position, u16 tile) {
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tile), position.x,
                   position.y);
}

void drawVerticalScroll(Vec2 upPosition, Vec2 downPosition,
                        CursorTiles tilesData) {
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.up),
                   upPosition.x, upPosition.y);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.down),
                   downPosition.x, downPosition.y);
}

void drawBorder(Vec2 position, SizeBox size, BorderTiles tilesData) {
  // corners
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.topLeft),
                   position.x, position.y);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.topRight),
                   position.x + size.w - 1, position.y);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.bottomLeft),
                   position.x, position.y + size.h - 1);
  VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.bottomRight),
                   position.x + size.w - 1, position.y + size.h - 1);

  // top and bottom edges
  for (u16 i = 1; i < size.w - 1; i++) {
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.topSide),
                     position.x + i, position.y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.bottomSide),
                     position.x + i, position.y + size.h - 1);
  }

  // left and right edges
  for (u16 j = 1; j < size.h - 1; j++) {
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.leftSide),
                     position.x, position.y + j);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.rightSide),
                     position.x + size.w - 1, position.y + j);
  }

  // fill center
  for (u16 j = 1; j < size.h - 1; j++) {
    for (u16 i = 1; i < size.w - 1; i++) {
      VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tilesData.fill),
                       position.x + i, position.y + j);
    }
  }
}

void drawButtonShape(u16 x, u16 y, int buttonType) {
  switch (buttonType) {
  case 0: // Clear button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_S_B_R), x + 1,
                     y + 1);
    break;
  case 1: // A button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_C_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_C_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_C_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_C_S_B_R), x + 1,
                     y + 1);
    break;
  case 2: // B button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_C_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_C_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_C_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_C_S_B_R), x + 1,
                     y + 1);
    break;
  case 3: // C button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_C_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_C_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_C_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_C_S_B_R), x + 1,
                     y + 1);
    break;
  case 4: // X button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_C_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_C_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_C_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_C_S_B_R), x + 1,
                     y + 1);
    break;
  case 5: // Y button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_C_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_C_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_C_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_C_S_B_R), x + 1,
                     y + 1);
    break;
  case 6: // Z button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_C_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_C_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_C_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_C_S_B_R), x + 1,
                     y + 1);
    break;
  case 7: // Three button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, THR_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, THR_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, THR_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, THR_S_B_R), x + 1,
                     y + 1);
    break;
  case 8: // Two button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, T_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, T_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, T_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, T_S_B_R), x + 1,
                     y + 1);
    break;
  case 9: // One button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, O_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, O_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, O_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, O_S_B_R), x + 1,
                     y + 1);
    break;
  case 10: // Four button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, F_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, F_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, F_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, F_S_B_R), x + 1,
                     y + 1);
    break;
  case 11: // Five button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FIVE_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FIVE_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FIVE_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FIVE_S_B_R), x + 1,
                     y + 1);
    break;
  case 12: // Six button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SIX_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SIX_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SIX_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SIX_S_B_R), x + 1,
                     y + 1);
    break;
  case 13: // Seven button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SEVEN_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SEVEN_S_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SEVEN_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SEVEN_S_B_R), x + 1,
                     y + 1);
    break;
  case 14: // Eight button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, E_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, E_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, E_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, E_S_B_R), x + 1,
                     y + 1);
    break;
  case 15: // Nine button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, N_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, N_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, N_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, N_S_B_R), x + 1,
                     y + 1);
    break;
  case 16: // Zero button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ZERO_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ZERO_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ZERO_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, ZERO_S_B_R), x + 1,
                     y + 1);
    break;
  case 17: // Go button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, G_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, G_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, G_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, G_S_B_R), x + 1,
                     y + 1);
    break;
  case 18: // X fill shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_F_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_F_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_F_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_F_S_B_R), x + 1,
                     y + 1);
    break;
  case 19: // X fill shape and border
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_F_S_B_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_F_S_B_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_F_S_B_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, X_F_S_B_B_R), x + 1,
                     y + 1);
    break;
  case 20: // Y fill shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_F_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_F_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_F_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_F_S_B_R), x + 1,
                     y + 1);
    break;
  case 21: // Y fill shape and border
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_F_S_B_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_F_S_B_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_F_S_B_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Y_F_S_B_B_R), x + 1,
                     y + 1);
    break;
  case 22: // Z fill shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_F_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_F_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_F_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_F_S_B_R), x + 1,
                     y + 1);
    break;
  case 23: // Z fill shape and border
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_F_S_B_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_F_S_B_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_F_S_B_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, Z_F_S_B_B_R), x + 1,
                     y + 1);
    break;
  case 24: // A fill shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_F_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_F_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_F_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_F_S_B_R), x + 1,
                     y + 1);
    break;
  case 25: // A fill shape and border
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_F_S_B_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_F_S_B_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_F_S_B_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, A_F_S_B_B_R), x + 1,
                     y + 1);
    break;
  case 26: // B fill shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_F_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_F_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_F_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_F_S_B_R), x + 1,
                     y + 1);
    break;
  case 27: // B fill shape and border
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_F_S_B_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_F_S_B_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_F_S_B_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, B_F_S_B_B_R), x + 1,
                     y + 1);
    break;
  case 28: // C fill shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_F_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_F_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_F_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_F_S_B_R), x + 1,
                     y + 1);
    break;
  case 29: // C fill shape and border
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_F_S_B_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_F_S_B_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_F_S_B_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, C_F_S_B_B_R), x + 1,
                     y + 1);
    break;
  case 30: // Stady button shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, STDY_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, STDY_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, STDY_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, STDY_S_B_R), x + 1,
                     y + 1);
    break;
  case 31: // Stady fill shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, STDY_F_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, STDY_F_S_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, STDY_F_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, STDY_F_S_B_R), x + 1,
                     y + 1);
    break;
  case 32: // Timer pie 11 point
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, EL_P_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, EL_P_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, EL_P_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, EL_P_S_B_R), x + 1,
                     y + 1);
    break;
  case 33: // Timer pie 9 point
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, NIN_P_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, NIN_P_S_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, NIN_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, NIN_P_S_B_R), x + 1,
                     y + 1);
    break;
  case 34: // Timer pie 7 point
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SVN_P_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SVN_P_S_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SVN_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SVN_P_S_B_R), x + 1,
                     y + 1);
    break;
  case 35: // Timer pie 6 point
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SIX_P_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SIX_P_S_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SIX_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, SIX_P_S_B_R), x + 1,
                     y + 1);
    break;
  case 36: // Timer pie 5 point
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FIVE_P_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FIVE_P_S_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FIVE_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, FIVE_P_S_B_R), x + 1,
                     y + 1);
    break;
  case 37: // Timer pie 3 point
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, THREE_P_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, THREE_P_S_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, THREE_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, THREE_P_S_B_R), x + 1,
                     y + 1);
    break;
  case 38: // Timer pie 2 point 5 countdown
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_F_P_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_F_P_S_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_F_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_F_P_S_B_R), x + 1,
                     y + 1);
    break;
  case 39: // Timer pie 2 point 4 countdown
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_FR_P_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_FR_P_S_T_R), x + 1,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_FR_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_FR_P_S_B_R), x + 1,
                     y + 1);
    break;
  case 40: // Timer pie 2 point 3 countdown
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_THR_P_S_T_L), x,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_THR_P_S_T_R),
                     x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_THR_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_THR_P_S_B_R),
                     x + 1, y + 1);
    break;
  case 41: // Timer pie 2 point 2 countdown
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_TWO_P_S_T_L), x,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_TWO_P_S_T_R),
                     x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_TWO_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_TWO_P_S_B_R),
                     x + 1, y + 1);
    break;
  case 42: // Timer pie 2 point 1 countdown
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_ONE_P_S_T_L), x,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_ONE_P_S_T_R),
                     x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_ONE_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TWO_ONE_P_S_B_R),
                     x + 1, y + 1);
    break;
  case 43: // Time out point
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TIME_OUT_P_S_T_L), x,
                     y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TIME_OUT_P_S_T_R),
                     x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TIME_OUT_P_S_B_L), x,
                     y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TIME_OUT_P_S_B_R),
                     x + 1, y + 1);
    break;
  case 44: // Wait input shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, WI_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, WI_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, WI_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, WI_S_B_R), x + 1,
                     y + 1);
    break;
  case 45: // Lose shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, L_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, L_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, L_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, L_S_B_R), x + 1,
                     y + 1);
    break;
  case 46: // Success shape
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, S_S_T_L), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, S_S_T_R), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, S_S_B_L), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, S_S_B_R), x + 1,
                     y + 1);
    break;
  case 47: // Blank black square
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BLACK), x, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BLACK), x + 1, y);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BLACK), x, y + 1);
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BLACK), x + 1,
                     y + 1);
    break;
  }
}
