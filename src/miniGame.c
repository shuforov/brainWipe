#include <genesis.h>
#include <../res/resources.h>
#include "miniGame.h"
#include "gameEngine.h"


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
static const u16 S_S_T_L = 0xB5; // Success shape top left
static const u16 S_S_T_R = 0xB6; // Success shape top right
static const u16 S_S_B_L = 0xB8; // Success shape bottom left
static const u16 S_S_B_R = 0xB9; // Success shape bottom right
// Lose shape
static const u16 L_S_T_L = 0xBA; // Lose shape top left
static const u16 L_S_T_R = 0xBB; // Lose shape top right
static const u16 L_S_B_L = 0xBC; // Lose shape bottom left
static const u16 L_S_B_R = 0xBD; // Lose shape bottom right
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

static const int BUTTON_NUMBERS[] = {16, 9, 8, 7, 10, 11, 12, 13, 14, 15};

bool isRendered = false;
u16 curW = 3;
u16 curH = 3;
u16 countDown = 5;
u16 buttonCountDown = 1;
bool isCountDownGo = false;
bool isButtonAnimationActive = false;
u16 buttonAnimationType = 0;
struct popUpTransform popUpData;
struct buttonMetadata buttonsInPopUp[] = {
    {11, 9, 0},  // count down timer
    {13, 9, 0},  // end status of minigame
    {15, 9, 0},  // rounds count of minigames
    {11, 11, 4}, // X button
    {13, 11, 5}, // Y button
    {15, 11, 6}, // Z button
    {11, 13, 1}, // A button
    {13, 13, 2}, // B buutton
    {15, 13, 3}, // C button
};

void drawPopup(u16 x, u16 y, u16 w, u16 h) {
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

void countDownGo() {
  if (isCountDownGo) {
    bool secondPass = getTick() % 240 == 0;
    if (secondPass && countDown >= 0) {
      printInt(4, 5, countDown);
      if (countDown == 0) {
	buttonsInPopUp[0].idTag = 17; // set button shape to GO state
        setCountDownGo(false);
        countDown = 5;
      } else {
	buttonsInPopUp[0].idTag = BUTTON_NUMBERS[countDown];
        countDown--;
      }
    }
  }
}

void buttonAnimation() {
  if (isButtonAnimationActive) {
    u16 buttonAnimationsArray[3] = {};
    switch (buttonAnimationType) {
    case 0: // X button animation
      buttonAnimationsArray[0] = 4;
      buttonAnimationsArray[1] = 18;
      buttonAnimationsArray[2] = 19;
      buttonAnimationProcess(3, buttonAnimationsArray);
      break;
    case 1: // Y button animation
      buttonAnimationsArray[0] = 5;
      buttonAnimationsArray[1] = 20;
      buttonAnimationsArray[2] = 21;
      buttonAnimationProcess(4, buttonAnimationsArray);
      break;
    case 2: // Z button animation
      buttonAnimationsArray[0] = 6;
      buttonAnimationsArray[1] = 22;
      buttonAnimationsArray[2] = 23;
      buttonAnimationProcess(5, buttonAnimationsArray);
      break;
    case 3: // A button animation
      buttonAnimationsArray[0] = 1;
      buttonAnimationsArray[1] = 24;
      buttonAnimationsArray[2] = 25;
      buttonAnimationProcess(6, buttonAnimationsArray);
      break;
    case 4: // B button animation
      buttonAnimationsArray[0] = 2;
      buttonAnimationsArray[1] = 26;
      buttonAnimationsArray[2] = 27;
      buttonAnimationProcess(7, buttonAnimationsArray);
      break;
    case 5: // C btton animation
      buttonAnimationsArray[0] = 3;
      buttonAnimationsArray[1] = 28;
      buttonAnimationsArray[2] = 29;
      buttonAnimationProcess(8, buttonAnimationsArray);
      break;
    }
  }
}

void setButtonAnimationState(u16 buttonType, bool state) {
  buttonAnimationType = buttonType;
  isButtonAnimationActive = state;
}

void buttonAnimationProcess(u16 buttonIndex, u16 buttonType[]) {
  bool passState = getTick() % 25 == 0;
  if (passState && buttonCountDown >= 0) {
    printInt(4, 6, buttonCountDown);
    if (buttonCountDown == 0) {
      buttonsInPopUp[buttonIndex].idTag = buttonType[buttonCountDown]; // Set default X shape button
      buttonCountDown = 2;
      isButtonAnimationActive = false;
    } else if (buttonCountDown == 1) {
      buttonsInPopUp[buttonIndex].idTag = buttonType[buttonCountDown]; // Set X fill shape
      buttonCountDown--;
    } else if (buttonCountDown == 2) {
      buttonsInPopUp[buttonIndex].idTag = buttonType[buttonCountDown]; // Set X fill shape and border
      buttonCountDown--;
    }
  }
}

bool isButtonAnimation() {
  return isButtonAnimationActive;
}

void drawButtons() {
  for (int i = 0; i < 9; i++) {
    drawButtonShape(buttonsInPopUp[i].x, buttonsInPopUp[i].y,
                    buttonsInPopUp[i].idTag);
  }
}

void setCountDownGo(bool value) {
  isCountDownGo = value;
}

bool popUpAnimation(u16 x, u16 y, u16 w, u16 h) {
  popUpData.x = x;
  popUpData.y = y;
  popUpData.w = w;
  popUpData.h = h;
  if (isRendered) {
    drawPopup(x, y, w, h);
    return true;
  }
  if ((getTick() % 20) == 0) { // every 1/4 of second
    if (w != curW || h != curH) {
      if (curW < w) {
        drawPopup(x, y, curW, curH);
        curW++;
      }
      if (curH < h) {
        drawPopup(x, y, curW, curH);
        curH++;
      }
    } else {
      isRendered = true;
      curH = 3;
      curW = 3;
      return true;
    }
  }
  return false;
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
  }
}
