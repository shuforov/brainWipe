#include <genesis.h>
#include "../../headers/miniGameConstants.h"
#include "../../headers/handlers/drawButtonHandler.h"

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
  }
}
