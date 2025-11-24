#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/hideoutScene.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/handlers/inputHandler.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/entityManagerHandler.h"
#include "../../headers/handlers/commonFunctionsHandler.h"

typedef enum {
  MOVE_SELECTOR_UP,
  MOVE_SELECTOR_DOWN,
  MOVE_SELECTOR_RIGHT,
  MOVE_SELECTOR_LEFT,
  PRESS_Y_BUTTON
} CursorBttons;

typedef enum {
  TOP_PANEL
} InteractFocusTypes;

typedef enum {
  STATISTICS_OPTION,
  INVENTORY_OPTION,
  MAP_OPTION,
  MENU_OPTION
} TopPanelOptionTypes;

typedef struct {
  u16 indexLevel;
  u16 infoText[145];
  u16 enemiesCount;
  bool available;
} BildingLevelData;

typedef struct {
  char name[10];
  u16 infoText[145];
  u16 indexImage;
  bool available;
} BuildingData;

typedef struct {
  char name[10];
  u16 buildingCount;
  BuildingData buildings[9];
  u16 infoText[145];
  u16 indexImage;
  bool available;
} CityData;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  u16 titleTiles[11];
  Vec2 titlePosition;
  u16 selectorIndex;
  Vec2 selectorPosition;
  Vec2 aButtonPosition;
  VerticalScrollTransform verticalScroll;
  Vec2 cursorRightPosition;
} CitiesBorderData;

typedef struct {
  CityData cities[9];
  u16 textTitle[5];
  Vec2 textTitlePosition;
} MapData;

typedef struct {
  u16 textTitle[8];
  Vec2 textTitlePosition;
} InventoryData;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  Vec2 position;
  u16 nameTitle[4];
  Vec2 nameTitilePosition;
  u16 nameValue[8];
  Vec2 nameValuePosition;
  u16 healthTitle[4];
  Vec2 healthTitlePosition;
  u16 healthValue;
  Vec2 healthValuePosition;
} PlayerStatisticData;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  Vec2 position;
} PlayerStatisticAvatarData;

typedef struct {
  u16 textTitle[5];
  Vec2 textTitlePosition;
  PlayerStatisticAvatarData avatar;
  PlayerStatisticData stats;
} StatisticData;

typedef struct {
  u16 textTitle[4];
  Vec2 textTitlePosition;
} MenuData;

typedef struct {
  MenuData menuData;
  StatisticData statisticData;
  InventoryData inventoryData;
  MapData mapData;
  Vec2 borderPosition;
  SizeBox borderSize;
  Vec2 cursorRightPosition;
  u16 selectorIndex;
  Vec2 cursorPostions[4];
} TopPanelData;

typedef struct {
  TopPanelData topPanelData;
  BorderTiles borderTilesData;
  CursorTiles cursorTilesData;
  u16 currentFocus;
  Vec2 optionSpacePosition; // Position of rendering data of selected option
                            // from top panel
  SizeBox optionSpaceSize;  // Size of option box for clearing this space
  Player *playerNode;
} MetaData;

static const u16 STATISTIC_TEXT[5] = {0x42, 0x48, 0x1E, 0x48, 0x5E};
static const u16 INVENTORY_TEXT[8] = {0x2E, 0x3E, 0x20, 0x28,
                                      0x3E, 0x48, 0x1E, 0x46};
static const u16 MAP_TEXT[5] = {0x31, 0x1E, 0x46, 0x48, 0x1E};
static const u16 MENU_TEXT[4] = {0x38, 0x28, 0x3E, 0x5B};
static const Vec2 CURSOR_POSITIONS[4] = {(Vec2){3, 2}, (Vec2){11, 2},
                                         (Vec2){22, 2}, (Vec2){31, 2}};
static const u16 STATS_NAME_TITLE[4] = {0x2E, 0x3D, 0x58, 0x5C};
static const u16 STATS_NAME_DEFAULT[8] = {
    0x1C, 0x33, 0x46, 0x66, BORDER_FILL, BORDER_FILL, BORDER_FILL, BORDER_FILL};
static const u16 STATS_HEALTH_TITLE[4] = {0x27, 0x2A, 0x46, 0x5E};
static MetaData metaData;

Scene hideoutSceneInit() {
  hideoutSceneLoadTiles();
  PAL_setPalette(PAL1, mainScenesPalette.data, DMA);
  PAL_setColor(0, 0x0000); // Set 0 index color to transparent

  hideoutTopPanelInit();
  hideoutDrawTopPanel();
  return createScene("hideout", 0, SCENE_HIDEOUT);
}

void hideoutSceneLoadTiles() {
  u16 ind = TILE_USER_INDEX;

  VDP_loadTileSet(scenesBorder.tileset, ind, DMA);
  ind += scenesBorder.tileset->numTile;

  VDP_loadTileSet(scenesAlphabetUa.tileset, ind, DMA);
  ind += scenesAlphabetUa.tileset->numTile;

  VDP_loadTileSet(scenesSelectorButtons.tileset, ind, DMA);
  ind += scenesSelectorButtons.tileset->numTile;

  VDP_loadTileSet(playerAvatar.tileset, ind, DMA);
  ind += playerAvatar.tileset->numTile;
}

void hideoutTopPanelInit() {
  metaData.playerNode = EMH_getPlayerNode();
  metaData.topPanelData.borderPosition = (Vec2){1, 1};
  metaData.topPanelData.borderSize = (SizeBox){38, 3};
  metaData.borderTilesData =
      (BorderTiles){BORDER_TOP_RIGHT,   BORDER_TOP_LEFT,    BORDER_BOTTOM_RIGHT,
                    BORDER_BOTTOM_LEFT, BORDER_TOP_SIDE,    BORDER_LEFT_SIDE,
                    BORDER_RIGHT_SIDE,  BORDER_BOTTOM_SIDE, BORDER_FILL};
  metaData.cursorTilesData =
      (CursorTiles){LEFT_CURSOR,       RIGHT_CURSOR,      UP_CURSOR,
                    DOWN_CURSOR,       A_SELECTOR_BUTTON, B_SELECTOR_BUTTON,
                    C_SELECTOR_BUTTON, X_SELECTOR_BUTTON, Y_SELECTOR_BUTTON,
                    Z_SELECTOR_BUTTON};
  memcpy(metaData.topPanelData.statisticData.textTitle, STATISTIC_TEXT,
         sizeof(STATISTIC_TEXT));
  memcpy(metaData.topPanelData.inventoryData.textTitle, INVENTORY_TEXT,
         sizeof(INVENTORY_TEXT));
  memcpy(metaData.topPanelData.mapData.textTitle, MAP_TEXT, sizeof(MAP_TEXT));
  memcpy(metaData.topPanelData.menuData.textTitle, MENU_TEXT,
         sizeof(MENU_TEXT));
  hideoutTopPanelStatisticDataInit();
  hideoutTopPanelInventoryDataInit();
  hideoutTopPanelMapDataInit();
  hideoutTopPanelMenuDataInit();
  metaData.topPanelData.cursorRightPosition = (Vec2){3, 2};
  metaData.topPanelData.selectorIndex = 0;
  memcpy(metaData.topPanelData.cursorPostions, CURSOR_POSITIONS,
         sizeof(CURSOR_POSITIONS));
  metaData.optionSpacePosition = (Vec2){1, 5};
  metaData.optionSpaceSize = (SizeBox){38, 25};
}

void hideoutTopPanelStatisticDataInit() {
  // TopPanel title name
  metaData.topPanelData.statisticData.textTitlePosition = (Vec2){4, 2};
  // Player avatar data Border
  metaData.topPanelData.statisticData.avatar.borderPosition = (Vec2){1, 5};
  metaData.topPanelData.statisticData.avatar.borderSize = (SizeBox){10, 10};
  // Player avatar data Position
  metaData.topPanelData.statisticData.avatar.position = (Vec2){2, 6};
  // Player stats data Border
  metaData.topPanelData.statisticData.stats.borderPosition = (Vec2){12, 5};
  metaData.topPanelData.statisticData.stats.borderSize = (SizeBox){15, 5};
  // Player stats data name
  memcpy(metaData.topPanelData.statisticData.stats.nameTitle, STATS_NAME_TITLE,
         sizeof(STATS_NAME_TITLE));
  metaData.topPanelData.statisticData.stats.nameTitilePosition = (Vec2){13, 6};
  metaData.topPanelData.statisticData.stats.nameValuePosition = (Vec2){18, 6};
  memcpy(metaData.topPanelData.statisticData.stats.nameValue,
         STATS_NAME_DEFAULT, sizeof(STATS_NAME_DEFAULT));
  // Player stats data health
  memcpy(metaData.topPanelData.statisticData.stats.healthTitle,
         STATS_HEALTH_TITLE, sizeof(STATS_HEALTH_TITLE));
  metaData.topPanelData.statisticData.stats.healthTitlePosition = (Vec2){13, 7};
  metaData.topPanelData.statisticData.stats.healthValue =
      metaData.playerNode->stats.health;
  metaData.topPanelData.statisticData.stats.healthValuePosition = (Vec2){18, 7};
}

void hideoutTopPanelInventoryDataInit() {
  metaData.topPanelData.inventoryData.textTitlePosition = (Vec2){12, 2};
}

void hideoutTopPanelMapDataInit() {
  metaData.topPanelData.mapData.textTitlePosition = (Vec2){23, 2};
}

void hideoutTopPanelMenuDataInit() {
  metaData.topPanelData.menuData.textTitlePosition = (Vec2){32, 2};
}

void hideoutDrawTopPanel() {
  // Draw border
  drawBorder(metaData.topPanelData.borderPosition,
             metaData.topPanelData.borderSize, metaData.borderTilesData);
  // Draw Text in border
  // Draw statistic title
  drawTextTiles(metaData.topPanelData.statisticData.textTitlePosition,
                metaData.topPanelData.statisticData.textTitle,
                ARRAY_LEN(metaData.topPanelData.statisticData.textTitle));
  // Draw inventory title
  drawTextTiles(metaData.topPanelData.inventoryData.textTitlePosition,
                metaData.topPanelData.inventoryData.textTitle,
                ARRAY_LEN(metaData.topPanelData.inventoryData.textTitle));
  // Draw map title
  drawTextTiles(metaData.topPanelData.mapData.textTitlePosition,
                metaData.topPanelData.mapData.textTitle,
                ARRAY_LEN(metaData.topPanelData.mapData.textTitle));
  // Draw menu title
  drawTextTiles(metaData.topPanelData.menuData.textTitlePosition,
                metaData.topPanelData.menuData.textTitle,
                ARRAY_LEN(metaData.topPanelData.menuData.textTitle));
  // Draw Right cursor arrow button
  hideoutDrawTopPanelCursor();
}

void hideoutSceneClearOptionSpace() {
  drawFillBox(metaData.optionSpacePosition, metaData.optionSpaceSize, 0x00);
}

void hideoutSceneDrawPlayerAvatar(Vec2 avatarPosition) {
  PAL_setPalette(PAL1, hideoutStatisticPalette.data, DMA);
  PAL_setColor(0, 0x0000); // set 0 index collor transparent
  VDP_drawImageEx(BG_A, &playerAvatar, TILE_ATTR_FULL(PAL1, 0, 0, 0, 0x7A),
                  avatarPosition.x, avatarPosition.y, 0, CPU);
}

void hideoutSceneDrawStatisticsOption() {
  // Draw border avatar
  drawBorder(metaData.topPanelData.statisticData.avatar.borderPosition,
             metaData.topPanelData.statisticData.avatar.borderSize,
             metaData.borderTilesData);
  // Draw avatar
  hideoutSceneDrawPlayerAvatar(
      metaData.topPanelData.statisticData.avatar.position);
  // Draw border stats
  drawBorder(metaData.topPanelData.statisticData.stats.borderPosition,
             metaData.topPanelData.statisticData.stats.borderSize,
             metaData.borderTilesData);
  // Draw name text title stats
  drawTextTiles(metaData.topPanelData.statisticData.stats.nameTitilePosition,
                metaData.topPanelData.statisticData.stats.nameTitle,
                ARRAY_LEN(metaData.topPanelData.statisticData.stats.nameTitle));
  // Draw name stats
  drawTextTiles(metaData.topPanelData.statisticData.stats.nameValuePosition,
                metaData.topPanelData.statisticData.stats.nameValue,
                ARRAY_LEN(metaData.topPanelData.statisticData.stats.nameValue));
  // Draw health text title stats
  drawTextTiles(
      metaData.topPanelData.statisticData.stats.healthTitlePosition,
      metaData.topPanelData.statisticData.stats.healthTitle,
      ARRAY_LEN(metaData.topPanelData.statisticData.stats.healthTitle));
  // Draw health stats
  CFH_SplitDigits u16ToSplitDigits =
      CFH_splitDigits(metaData.topPanelData.statisticData.stats.healthValue);
  SceneTransformDigits splitDigitsToHex =
      sceneTransformDigitsToHex(u16ToSplitDigits);
  drawTextTiles(metaData.topPanelData.statisticData.stats.healthValuePosition,
                splitDigitsToHex.hexDigits, splitDigitsToHex.count);
}

void hideoutSceneSelectorHandle(u16 typePopUp, u16 typeButton) {
  if (typePopUp == TOP_PANEL) {
    if (typeButton == MOVE_SELECTOR_LEFT) {
      if (metaData.topPanelData.selectorIndex > 0) {
        metaData.topPanelData.selectorIndex--;
        metaData.topPanelData.cursorRightPosition =
            metaData.topPanelData
                .cursorPostions[metaData.topPanelData.selectorIndex];
        hideoutDrawTopPanelCursor();
      }
    } else if (typeButton == MOVE_SELECTOR_RIGHT) {
      if (metaData.topPanelData.selectorIndex < 3) {
        metaData.topPanelData.selectorIndex++;
        metaData.topPanelData.cursorRightPosition =
            metaData.topPanelData
                .cursorPostions[metaData.topPanelData.selectorIndex];
        hideoutDrawTopPanelCursor();
      }
    } else if (typeButton == PRESS_Y_BUTTON) {
      if (metaData.topPanelData.selectorIndex == STATISTICS_OPTION) {
        hideoutSceneClearOptionSpace();
        hideoutSceneDrawStatisticsOption();
      } else if (metaData.topPanelData.selectorIndex == INVENTORY_OPTION) {
        hideoutSceneClearOptionSpace();
        VDP_drawText("Inventory option", 10, 10);
      } else if (metaData.topPanelData.selectorIndex == MAP_OPTION) {
        hideoutSceneClearOptionSpace();
        VDP_drawText("Map option", 10, 10);
      } else if (metaData.topPanelData.selectorIndex == MENU_OPTION) {
        hideoutSceneClearOptionSpace();
        VDP_drawText("Menu option", 10, 10);
      }
    }
  }
}

void hideoutDrawTopPanelCursor() {
  // Clear tiles
  for (u16 i = 0; i < ARRAY_LEN(metaData.topPanelData.cursorPostions); i++) {
    // Clear cursor tile
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.borderTilesData.fill),
        metaData.topPanelData.cursorPostions[i].x,
        metaData.topPanelData.cursorPostions[i].y);
    // Clear Y button
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.borderTilesData.fill),
        metaData.topPanelData.cursorPostions[i].x - 1,
        metaData.topPanelData.cursorPostions[i].y);
  }
  // Draw right cursor arrow button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.right),
      metaData.topPanelData.cursorRightPosition.x,
      metaData.topPanelData.cursorRightPosition.y);
  // Draw Y button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData.cursorTilesData.yButton),
      metaData.topPanelData.cursorRightPosition.x - 1,
      metaData.topPanelData.cursorRightPosition.y);
}

void hideoutSceneUpdate() {
  printInt(0, 0, getTick()); // print current frame from start of rom
}

void hideoutSceneInputHandler() {
  if (getJoyStates().leftButton) {
    if (metaData.currentFocus == TOP_PANEL) {
      hideoutSceneSelectorHandle(TOP_PANEL, MOVE_SELECTOR_LEFT);
    }
  }
  if (getJoyStates().rightButton) {
    if (metaData.currentFocus == TOP_PANEL) {
      hideoutSceneSelectorHandle(TOP_PANEL, MOVE_SELECTOR_RIGHT);
    }
  }
  if (getJoyStates().yButton) {
    if (metaData.currentFocus == TOP_PANEL) {
      hideoutSceneSelectorHandle(TOP_PANEL, PRESS_Y_BUTTON);
    }
  }
}
