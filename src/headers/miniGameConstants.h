#ifndef MINI_GAME_CONSTANTS_H
#define MINI_GAME_CONSTANTS_H
#include <genesis.h>

// Popup border tiles
static const u16 TILE_TOP_RIGHT = TILE_USER_INDEX + 0;
static const u16 TILE_BOTTOM_RIGHT = TILE_USER_INDEX + 1;
static const u16 TILE_BOTTOM_LEFT = TILE_USER_INDEX + 2;
static const u16 TILE_RIGHT_EDGE = TILE_USER_INDEX + 3;
static const u16 TILE_TOP_EDGE = TILE_USER_INDEX + 4;
static const u16 TILE_LEFT_EDGE = TILE_USER_INDEX + 5;
static const u16 TILE_BLACK = TILE_USER_INDEX + 6;
static const u16 TILE_BOTTOM_EDGE = TILE_USER_INDEX + 7;
static const u16 TILE_TOP_LEFT = TILE_USER_INDEX + 8;

// Button shape tiles
// Clear shape
static const u16 C_S_T_L = 0xAB; // clear shape top left
static const u16 C_S_T_R = 0xAC; // clear shape top right
static const u16 C_S_B_L = 0xB3; // clear shape bottom left
static const u16 C_S_B_R = 0xB4; // clear shape bottom right
// A shapes
// A clear shape
static const u16 A_C_S_T_L = 0x3C; // A clear shape top left
static const u16 A_C_S_T_R = 0x3D; // A clear shape top right
static const u16 A_C_S_B_L = 0x48; // A clear shape bottom left
static const u16 A_C_S_B_R = 0x49; // A clear shape bottom right
// A fill shape
static const u16 A_F_S_T_L = 0x3E; // A fill shape top left
static const u16 A_F_S_T_R = 0x3F; // A fill shape top right
static const u16 A_F_S_B_L = 0x4A; // A fill shape bottom left
static const u16 A_F_S_B_R = 0x4B; // A fill shape bottom right
// A fill shape and border
static const u16 A_F_S_B_T_L = 0x54; // A fill shape and border top left
static const u16 A_F_S_B_T_R = 0x55; // A fill shape and border top right
static const u16 A_F_S_B_B_L = 0x60; // A fill shape and border bottom left
static const u16 A_F_S_B_B_R = 0x61; // A fill shape and border bottom right
// B shapes
// B clear shape
static const u16 B_C_S_T_L = 0x40; // B clear shape top left
static const u16 B_C_S_T_R = 0x41; // B clear shape top right
static const u16 B_C_S_B_L = 0x4C; // B clear shape bottom left
static const u16 B_C_S_B_R = 0x4D; // B clear shape bottom right
// B fill shape
static const u16 B_F_S_T_L = 0x42; // B fill shape top left
static const u16 B_F_S_T_R = 0x43; // B fill shape top right
static const u16 B_F_S_B_L = 0x4E; // B fill shape bottom left
static const u16 B_F_S_B_R = 0x4F; // B fill shape bottom right
// B fill shape and border
static const u16 B_F_S_B_T_L = 0x58; // B fill shape and border top left
static const u16 B_F_S_B_T_R = 0x59; // B fill shape and border top right
static const u16 B_F_S_B_B_L = 0x64; // B fill shape and border bottom left
static const u16 B_F_S_B_B_R = 0x65; // B fill shape and border bottom right
// C shapes
// C clear shape
static const u16 C_C_S_T_L = 0x44; // C clear shape top left
static const u16 C_C_S_T_R = 0x45; // C clear shape top right
static const u16 C_C_S_B_L = 0x50; // C clear shape bottom left
static const u16 C_C_S_B_R = 0x51; // C clear shape bottom right
// C fill shape
static const u16 C_F_S_T_L = 0x46; // C fill shape top left
static const u16 C_F_S_T_R = 0x47; // C fill shape top right
static const u16 C_F_S_B_L = 0x52; // C fill shape bottom left
static const u16 C_F_S_B_R = 0x53; // C fill shape bottom right
// C fill shape and border
static const u16 C_F_S_B_T_L = 0x5C; // C fill shape and border top left
static const u16 C_F_S_B_T_R = 0x5D; // C fill shape and border top right
static const u16 C_F_S_B_B_L = 0x68; // C fill shape and border bottom left
static const u16 C_F_S_B_B_R = 0x69; // C fill shape and border bottom right
// X shpaes
// X clear shape
static const u16 X_C_S_T_L = 0x6C; // X clear shape top left
static const u16 X_C_S_T_R = 0x6D; // X clear shape top right
static const u16 X_C_S_B_L = 0x74; // X clear shape bottom left
static const u16 X_C_S_B_R = 0x75; // X clear shape bottom right
// X fill shape
static const u16 X_F_S_T_L = 0x6E; // X fill shape top left
static const u16 X_F_S_T_R = 0x6F; // X fill shape top right
static const u16 X_F_S_B_L = 0x76; // X fill shape bottom left
static const u16 X_F_S_B_R = 0x77; // X fill shape bottom right
// X fill shape and border
static const u16 X_F_S_B_T_L = 0x80; // X fill shape and border top left
static const u16 X_F_S_B_T_R = 0x81; // X fill shape and border top right
static const u16 X_F_S_B_B_L = 0x88; // X fill shape and border bottom left
static const u16 X_F_S_B_B_R = 0x89; // X fill shape and border bottom right
// Y shapes
// Y clear shape
static const u16 Y_C_S_T_L = 0x6C; // Y clear shape top left
static const u16 Y_C_S_T_R = 0x6D; // Y clear shape top right
static const u16 Y_C_S_B_L = 0x78; // Y clear shape bottom left
static const u16 Y_C_S_B_R = 0x79; // Y clear shape bottom right
// Y fill shape
static const u16 Y_F_S_T_L = 0x6E; // Y fill shape top left
static const u16 Y_F_S_T_R = 0x6F; // Y fill shape top right
static const u16 Y_F_S_B_L = 0x7A; // Y fill shape bottom left
static const u16 Y_F_S_B_R = 0x7B; // Y fill shape bottom right
// Y fill shape and border
static const u16 Y_F_S_B_T_L = 0x80; // Y fill shape and border top left
static const u16 Y_F_S_B_T_R = 0x81; // Y fill shape and border top right
static const u16 Y_F_S_B_B_L = 0x8C; // Y fill shape and border bottom left
static const u16 Y_F_S_B_B_R = 0x8D; // Y fill shape and border bottom right
// Z shapes
// Z clear shape
static const u16 Z_C_S_T_L = 0x70; // Z clear shape top left
static const u16 Z_C_S_T_R = 0x71; // Z clear shape top right
static const u16 Z_C_S_B_L = 0x7C; // Z clear shape bottom left
static const u16 Z_C_S_B_R = 0x7D; // Z clear shape bottom right
// Z fill shape
static const u16 Z_F_S_T_L = 0x72; // Z fill shape top left
static const u16 Z_F_S_T_R = 0x73; // Z fill shape top right
static const u16 Z_F_S_B_L = 0x7E; // Z fill shape bottom left
static const u16 Z_F_S_B_R = 0x7F; // Z fill shape bottom right
// Z fill shape and border
static const u16 Z_F_S_B_T_L = 0x84; // Z fill shape and border top left
static const u16 Z_F_S_B_T_R = 0x85; // Z fill shape and border top right
static const u16 Z_F_S_B_B_L = 0x90; // Z fill shape and border bottom left
static const u16 Z_F_S_B_B_R = 0x91; // Z fill shape and border bottom right
// Go shape
static const u16 G_S_T_L = 0xA9; // GO shape top left
static const u16 G_S_T_R = 0xAA; // GO shape top right
static const u16 G_S_B_L = 0xB1; // GO shape bottom left
static const u16 G_S_B_R = 0xB2; // GO shape bottom right
// Success shape
static const u16 S_S_T_L = 0xB7; // Success shape top left
static const u16 S_S_T_R = 0xB8; // Success shape top right
static const u16 S_S_B_L = 0xC3; // Success shape bottom left
static const u16 S_S_B_R = 0xC4; // Success shape bottom right
// Wait input shape
static const u16 WI_S_T_L = 0xBD; // Wait input shape top left
static const u16 WI_S_T_R = 0xBE; // Wait input shape rop right
static const u16 WI_S_B_L = 0xC9; // Wait input shape bottom left
static const u16 WI_S_B_R = 0xCA; // Wait input shape bottom right
// Lose shape
static const u16 L_S_T_L = 0xB5; // Lose shape top left
static const u16 L_S_T_R = 0xB6; // Lose shape top right
static const u16 L_S_B_L = 0xC1; // Lose shape bottom left
static const u16 L_S_B_R = 0xC2; // Lose shape bottom right
// Zero shape
static const u16 ZERO_S_T_L = 0x44; // Zero shape top left
static const u16 ZERO_S_T_R = 0x94; // Zero shape top right
static const u16 ZERO_S_B_L = 0x9B; // Zero shape bottom left
static const u16 ZERO_S_B_R = 0x4D; // Zero shape bottom right
// One shape
static const u16 O_S_T_L = 0x95; // One shape top left
static const u16 O_S_T_R = 0x96; // One shape top right
static const u16 O_S_B_L = 0x9C; // One shape bottom left
static const u16 O_S_B_R = 0x9D; // One shape bottom right
// Two shape
static const u16 T_S_T_L = 0x97; // Two shape top left
static const u16 T_S_T_R = 0x41; // Two shape top right
static const u16 T_S_B_L = 0x9E; // Two shape bottom left
static const u16 T_S_B_R = 0x9F; // Two shape bottom right
// Three shape
static const u16 THR_S_T_L = 0x70; // Three shape top left
static const u16 THR_S_T_R = 0x71; // Three shape top right
static const u16 THR_S_B_L = 0xA0; // Three shape bottom left
static const u16 THR_S_B_R = 0xA1; // Three shape bottom right
// Four shape
static const u16 F_S_T_L = 0x98; // Four shape top left
static const u16 F_S_T_R = 0x99; // Four shape top right
static const u16 F_S_B_L = 0xA2; // Four shape bottom left
static const u16 F_S_B_R = 0xA3; // Four shape bottom right
// Five shape
static const u16 FIVE_S_T_L = 0x40; // Five shape top left
static const u16 FIVE_S_T_R = 0x9A; // Five shape top right
static const u16 FIVE_S_B_L = 0xA0; // Five shape bottom left
static const u16 FIVE_S_B_R = 0x4D; // Five shape bottom right
// Six shape
static const u16 SIX_S_T_L = 0xA4; // Six shape top left
static const u16 SIX_S_T_R = 0xA5; // Six shape top right
static const u16 SIX_S_B_L = 0x50; // Six shape bottom left
static const u16 SIX_S_B_R = 0x4D; // Six shape bottom right
// Seven shape
static const u16 SEVEN_S_T_L = 0xA6; // Seven shape top left
static const u16 SEVEN_S_T_R = 0xA7; // Seven shape top right
static const u16 SEVEN_S_B_L = 0xAD; // Seven shape bottom left
static const u16 SEVEN_S_B_R = 0xAE; // Seven shape bottom right
// Eight shape
static const u16 E_S_T_L = 0xA8; // Eight shape top left
static const u16 E_S_T_R = 0x41; // Eight shape top right
static const u16 E_S_B_L = 0x50; // Eight shape bottom left
static const u16 E_S_B_R = 0x4D; // Eight shape bottom right
// Nine shape
static const u16 N_S_T_L = 0xA8; // Nine shape top left
static const u16 N_S_T_R = 0x94; // Nine shape top right
static const u16 N_S_B_L = 0xAF; // Nine shape bottom left
static const u16 N_S_B_R = 0xB0; // Nine shape bottom right

// Stady buttons
// Stady button shape
static const u16 STDY_S_T_L = 0xB9; // Stady shape top left
static const u16 STDY_S_T_R = 0xBA; // Stady shape top right
static const u16 STDY_S_B_L = 0xC5; // Stady shape bottom left
static const u16 STDY_S_B_R = 0xC6; // Stady shape bottom right

// Stady fill shape
static const u16 STDY_F_S_T_L = 0xBB; // Stady fill shape top left
static const u16 STDY_F_S_T_R = 0xBC; // Stady fill shape top right
static const u16 STDY_F_S_B_L = 0xC7; // Stady fill shape bottom left
static const u16 STDY_F_S_B_R = 0xC8; // Stady fill shape bottom right

// Timer pie
// 11 point
static const u16 EL_P_S_T_L = 0xCD; // 11 point shape top left
static const u16 EL_P_S_T_R = 0xCE; // 11 point shape top right
static const u16 EL_P_S_B_L = 0xCF; // 11 point shape bottom left
static const u16 EL_P_S_B_R = 0xD0; // 11 point shape bottom right

// 9 point
static const u16 NIN_P_S_T_L = 0xAB; // 9 point shape top left
static const u16 NIN_P_S_T_R = 0xCE; // 9 point shape top right
static const u16 NIN_P_S_B_L = 0xCF; // 9 point shape bottom left
static const u16 NIN_P_S_B_R = 0xD0; // 9 point shape bottom right

// 7 point
static const u16 SVN_P_S_T_L = 0xAB; // 7 point shape top left
static const u16 SVN_P_S_T_R = 0xCE; // 7 point shape top right
static const u16 SVN_P_S_B_L = 0xD1; // 7 point shape bottom left
static const u16 SVN_P_S_B_R = 0xD0; // 7 point shape bottom right

// 6 point
static const u16 SIX_P_S_T_L = 0xAB; // 6 point shape top left
static const u16 SIX_P_S_T_R = 0xCE; // 6 point shape top right
static const u16 SIX_P_S_B_L = 0xB3; // 6 point shape bottom left
static const u16 SIX_P_S_B_R = 0xD0; // 6 point shape bottom right

// 5 point
static const u16 FIVE_P_S_T_L = 0xAB; // 5 point shape top left
static const u16 FIVE_P_S_T_R = 0xC0; // 5 point shape top right
static const u16 FIVE_P_S_B_L = 0xB3; // 5 point shape bottom left
static const u16 FIVE_P_S_B_R = 0xD2; // 5 point shape bottom right

// 3 point
static const u16 THREE_P_S_T_L = 0xAB; // 3 point shape top left
static const u16 THREE_P_S_T_R = 0xC0; // 3 point shape top right
static const u16 THREE_P_S_B_L = 0xB3; // 3 point shape bottom left
static const u16 THREE_P_S_B_R = 0xB4; // 3 point shape bottom right

// 2 points
// 5 countdown point
static const u16 TWO_F_P_S_T_L = 0x40; // 2 point countdown 5 shape top left
static const u16 TWO_F_P_S_T_R = 0xD3; // 2 point countdown 5 shape top right
static const u16 TWO_F_P_S_B_L = 0xA0; // 2 point countdown 5 shape bottom left
static const u16 TWO_F_P_S_B_R = 0x4D; // 2 point countdown 5 shape bottom right

// 4 countdown point
static const u16 TWO_FR_P_S_T_L = 0x98; // 2 point countdown 4 shape top left
static const u16 TWO_FR_P_S_T_R = 0xD4; // 2 point countdown 4 shape top right
static const u16 TWO_FR_P_S_B_L = 0xA2; // 2 point countdown 4 shape bottom left
static const u16 TWO_FR_P_S_B_R = 0xA3; // 2 point countdown 4 shape bottom right

// 3 countdown point
static const u16 TWO_THR_P_S_T_L = 0x70; // 2 point countdown 3 shape top left
static const u16 TWO_THR_P_S_T_R = 0xD5; // 2 point countdown 3 shape top right
static const u16 TWO_THR_P_S_B_L = 0xA0; // 2 point countdown 3 shape bottom left
static const u16 TWO_THR_P_S_B_R = 0xA1; // 2 point countdown 3 shape bottom right

// 2 countdown point
static const u16 TWO_TWO_P_S_T_L = 0x97; // 2 point countdown 2 shape top left
static const u16 TWO_TWO_P_S_T_R = 0xD6; // 2 point countdown 2 shape top right
static const u16 TWO_TWO_P_S_B_L = 0x9E; // 2 point countdown 2 shape bottom left
static const u16 TWO_TWO_P_S_B_R = 0x9F; // 2 point countdown 2 shape bottom right

// 1 countdown point
static const u16 TWO_ONE_P_S_T_L = 0x95; // 2 point countdown 1 shape top left
static const u16 TWO_ONE_P_S_T_R = 0xD7; // 2 point countdown 1 shape top right
static const u16 TWO_ONE_P_S_B_L = 0x9C; // 2 point countdown 1 shape bottom left
static const u16 TWO_ONE_P_S_B_R = 0x9D; // 2 point countdown 1 shape bottom right

// Time out point
static const u16 TIME_OUT_P_S_T_L = 0xD8; // Time out point shape top left
static const u16 TIME_OUT_P_S_T_R = 0xD9; // Time out point shape top right
static const u16 TIME_OUT_P_S_B_L = 0xDA; // Time out point shape bottom left
static const u16 TIME_OUT_P_S_B_R = 0xDB; // Time out point shape bottom right

static const int BUTTON_NUMBERS[] = {16, 9, 8, 7, 10, 11, 12, 13, 14, 15};

static const u16 TIMER_SEGMENT_NUMBERS[] = {32, 33, 34, 35, 36, 37};
static const u16 TIMER_LAST_SEGMENT_NUMBERS[] = {43, 42, 41, 40, 39, 38};
#endif
