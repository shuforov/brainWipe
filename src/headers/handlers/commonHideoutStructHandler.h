#ifndef COMMON_HIDEOUT_STRUCT_HANDLER_H
#define COMMON_HIDEOUT_STRUCT_HANDLER_H

#include "commonStructHandler.h"
#include "entityManagerHandler.h"

typedef enum {
  MOVE_SELECTOR_UP,
  MOVE_SELECTOR_DOWN,
  MOVE_SELECTOR_RIGHT,
  MOVE_SELECTOR_LEFT,
  PRESS_X_BUTTON,
  PRESS_Y_BUTTON,
  PRESS_Z_BUTTON,
  PRESS_A_BUTTON,
  PRESS_B_BUTTON,
  PRESS_C_BUTTON
} CursorButtons;

typedef enum {
  TOP_PANEL_FOCUS,
  STATISTICS_FOCUS,
  INVENTORY_FOCUS,
  MAP_FOCUS,
  MENU_FOCUS
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
  u16 textTitle[4];
  Vec2 textTitlePosition;
} MenuData;

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

#endif
