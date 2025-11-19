#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/hideoutScene.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/handlers/inputHandler.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/drawButtonHandler.h"

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
  u16 textTitle[5];
  Vec2 textTitlePosition;
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
  Vec2 optionSpacePosition; // Position of rendering data of selected option from top
                       // panel
  SizeBox optionSpaceSize;  // Size of option box for clearing this space
} MetaData;

static const u16 STATISTIC_TEXT[5] = {0x42, 0x48, 0x1E, 0x48, 0x5E};
static const u16 INVENTORY_TEXT[8] = {0x2E, 0x3E, 0x20, 0x28,
                                      0x3E, 0x48, 0x1E, 0x46};
static const u16 MAP_TEXT[5] = {0x31, 0x1E, 0x46, 0x48, 0x1E};
static const u16 MENU_TEXT[4] = {0x38, 0x28, 0x3E, 0x5B};
static const Vec2 CURSOR_POSITIONS[4] = {(Vec2){3, 2}, (Vec2){11, 2}, (Vec2){22, 2}, (Vec2){31, 2}};
static MetaData metaData;

Scene hideoutSceneInit() {
  hideoutSceneLoadTiles();
  PAL_setPalette(PAL1, mainScenesPalette.data, DMA);

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
  ind += scenesAlphabetUa.tileset->numTile;
}

void hideoutTopPanelInit() {
  metaData.topPanelData.borderPosition = (Vec2){1, 1};
  metaData.topPanelData.borderSize = (SizeBox){38, 3};
  metaData.borderTilesData =
      (BorderTiles){BORDER_TOP_RIGHT,   BORDER_TOP_LEFT,    BORDER_BOTTOM_RIGHT,
                    BORDER_BOTTOM_LEFT, BORDER_TOP_SIDE,    BORDER_LEFT_SIDE,
                    BORDER_RIGHT_SIDE,  BORDER_BOTTOM_SIDE, BORDER_FILL};
  metaData.cursorTilesData = (CursorTiles){LEFT_CURSOR,
                                           RIGHT_CURSOR,
                                           UP_CURSOR,
                                           DOWN_CURSOR,
                                           A_SELECTOR_BUTTON,
                                           B_SELECTOR_BUTTON,
                                           C_SELECTOR_BUTTON,
                                           X_SELECTOR_BUTTON,
                                           Y_SELECTOR_BUTTON,
                                           Z_SELECTOR_BUTTON};
  memcpy(metaData.topPanelData.statisticData.textTitle, STATISTIC_TEXT,
         sizeof(STATISTIC_TEXT));
  memcpy(metaData.topPanelData.inventoryData.textTitle, INVENTORY_TEXT,
         sizeof(INVENTORY_TEXT));
  memcpy(metaData.topPanelData.mapData.textTitle, MAP_TEXT, sizeof(MAP_TEXT));
  memcpy(metaData.topPanelData.menuData.textTitle, MENU_TEXT,
         sizeof(MENU_TEXT));
  metaData.topPanelData.statisticData.textTitlePosition = (Vec2){4, 2};
  metaData.topPanelData.inventoryData.textTitlePosition = (Vec2){12, 2};
  metaData.topPanelData.mapData.textTitlePosition = (Vec2){23, 2};
  metaData.topPanelData.menuData.textTitlePosition = (Vec2){32, 2};
  metaData.topPanelData.cursorRightPosition = (Vec2){3, 2};
  metaData.topPanelData.selectorIndex = 0;
  memcpy(metaData.topPanelData.cursorPostions, CURSOR_POSITIONS,
         sizeof(CURSOR_POSITIONS));
  metaData.optionSpacePosition = (Vec2){1, 5};
  metaData.optionSpaceSize = (SizeBox){38, 25};
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

void hideoutSceneClearOptionSpace() {
  drawFillBox(metaData.optionSpacePosition, metaData.optionSpaceSize, 0x00);
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
        VDP_drawText("Statistic option", 10, 10);
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
