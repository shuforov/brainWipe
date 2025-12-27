#include <genesis.h>
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/hideoutSceneHintOptionHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/hideoutSceneCommonFunctions.h"

static const u16 HINT_MENU_OPTION_STATS_NAME[5] = {0x42, 0x48, 0x1E, 0x48,
                                                   0x5E};
static const u16 HINT_MENU_OPTION_INVENTORY_NAME[8] = {0x2E, 0x3E, 0x20, 0x28,
                                                       0x3E, 0x48, 0x1E, 0x46};
static const u16 HINT_MENU_OPTION_MAP_NAME[4] = {0x38, 0x1E, 0x40, 0x1E};
static const u16 HINT_MENU_OPTION_MENU_NAME[4] = {0x38, 0x28, 0x3E, 0x5B};
static const Vec2 HINT_MENU_OPTION_SELECTOR_POSITIONS[4] = {
    (Vec2){3, 2}, (Vec2){3, 3}, (Vec2){3, 4}, (Vec2){3, 5}};

void HSHOH_dataInit(MetaData *metaData) {
  // Main hint box data
  metaData->hintOptionData.borderPosition = (Vec2){1, 1};
  metaData->hintOptionData.borderSize = (SizeBox){4, 3};
  metaData->hintOptionData.hintButtonPosition = (Vec2){2, 2};
  metaData->hintOptionData.hintIconPosition = (Vec2){3, 2};
  // Main hint Menu data
  metaData->hintOptionData.menuData.borderPosition = (Vec2){1, 1};
  metaData->hintOptionData.menuData.borderSize = (SizeBox){13, 6};
  metaData->hintOptionData.menuData.selectorData.selectorIndex =
      STATISTICS_OPTION;
  metaData->hintOptionData.menuData.selectorData.selectorPosition =
      (Vec2){3, 2};
  metaData->hintOptionData.menuData.selectorData.selectorTile =
      metaData->cursorTilesData.right;
  metaData->hintOptionData.menuData.selectorData.hintButtonPosition =
      (Vec2){2, 2};
  metaData->hintOptionData.menuData.selectorData.hintButtonTile =
      metaData->cursorTilesData.aButton;
  // Menu options data
  metaData->hintOptionData.menuData.optionsData.statsPosition = (Vec2){4, 2};
  memcpy(metaData->hintOptionData.menuData.optionsData.statsTiles,
         HINT_MENU_OPTION_STATS_NAME, sizeof(HINT_MENU_OPTION_STATS_NAME));
  metaData->hintOptionData.menuData.optionsData.inventoryPosition =
      (Vec2){4, 3};
  memcpy(metaData->hintOptionData.menuData.optionsData.inventoryTiles,
         HINT_MENU_OPTION_INVENTORY_NAME,
         sizeof(HINT_MENU_OPTION_INVENTORY_NAME));
  metaData->hintOptionData.menuData.optionsData.mapPosition = (Vec2){4, 4};
  memcpy(metaData->hintOptionData.menuData.optionsData.mapTiles,
         HINT_MENU_OPTION_MAP_NAME, sizeof(HINT_MENU_OPTION_MAP_NAME));
  metaData->hintOptionData.menuData.optionsData.menuPosition = (Vec2){4, 5};
  memcpy(metaData->hintOptionData.menuData.optionsData.menuTiles,
         HINT_MENU_OPTION_MENU_NAME, sizeof(HINT_MENU_OPTION_MENU_NAME));
}

void HSHOH_drawHintMenu(MetaData *metaData) {
  // Draw border
  drawBorder(metaData->hintOptionData.borderPosition,
             metaData->hintOptionData.borderSize, metaData->borderTilesData);
  // Draw hint button
  drawTile(metaData->hintOptionData.hintButtonPosition, metaData->cursorTilesData.yButton);
  // Draw hint drop down icon
  drawTile(metaData->hintOptionData.hintIconPosition,
           metaData->cursorTilesData.dropDownIcon);
}

void HSHOH_drawHintMenuSelector(MetaData *metaData) {
  drawTile(metaData->hintOptionData.menuData.selectorData.selectorPosition,
           metaData->hintOptionData.menuData.selectorData.selectorTile);
  drawTile(metaData->hintOptionData.menuData.selectorData.hintButtonPosition,
           metaData->hintOptionData.menuData.selectorData.hintButtonTile);
}

void HSHOH_drawHintPopUpMenu(MetaData *metaData) {
  drawBorder(metaData->hintOptionData.menuData.borderPosition,
             metaData->hintOptionData.menuData.borderSize,
             metaData->borderTilesData);
  HSHOH_drawHintMenuSelector(metaData);
  // Draw all menu options
  drawTextTiles(
      metaData->hintOptionData.menuData.optionsData.statsPosition,
      metaData->hintOptionData.menuData.optionsData.statsTiles,
      ARRAY_LEN(metaData->hintOptionData.menuData.optionsData.statsTiles));
  drawTextTiles(
      metaData->hintOptionData.menuData.optionsData.inventoryPosition,
      metaData->hintOptionData.menuData.optionsData.inventoryTiles,
      ARRAY_LEN(metaData->hintOptionData.menuData.optionsData.inventoryTiles));
  drawTextTiles(
      metaData->hintOptionData.menuData.optionsData.mapPosition,
      metaData->hintOptionData.menuData.optionsData.mapTiles,
      ARRAY_LEN(metaData->hintOptionData.menuData.optionsData.mapTiles));
  drawTextTiles(
      metaData->hintOptionData.menuData.optionsData.menuPosition,
      metaData->hintOptionData.menuData.optionsData.menuTiles,
      ARRAY_LEN(metaData->hintOptionData.menuData.optionsData.menuTiles));
}

void HSHOH_redrawHintMenuSelector(MetaData *metaData) {
  // Clear tiles
  for (u16 i = 0; i < ARRAY_LEN(HINT_MENU_OPTION_SELECTOR_POSITIONS); i++) {
    Vec2 positionSelector = HINT_MENU_OPTION_SELECTOR_POSITIONS[i];
    // Clear selector cursor
    drawTile(positionSelector, metaData->borderTilesData.fill);
    // Clear selector hint button
    drawTile((Vec2){positionSelector.x - 1, positionSelector.y},
             metaData->borderTilesData.fill);
  }
  HSHOH_drawHintMenuSelector(metaData);
}

void HSHO_selectorStatsHandle(MetaData *metaData, u16 typeButton) {
  if (typeButton == MOVE_SELECTOR_UP) {
    if (metaData->hintOptionData.menuData.selectorData.selectorIndex > 0) {
      metaData->hintOptionData.menuData.selectorData.selectorIndex--;
      metaData->hintOptionData.menuData.selectorData.selectorPosition.y--;
      metaData->hintOptionData.menuData.selectorData.hintButtonPosition.y--;
      HSHOH_redrawHintMenuSelector(metaData);
    }
  } else if (typeButton == MOVE_SELECTOR_DOWN) {
    if (metaData->hintOptionData.menuData.selectorData.selectorIndex < 3) {
      metaData->hintOptionData.menuData.selectorData.selectorIndex++;
      metaData->hintOptionData.menuData.selectorData.selectorPosition.y++;
      metaData->hintOptionData.menuData.selectorData.hintButtonPosition.y++;
      HSHOH_redrawHintMenuSelector(metaData);
    }
  } else if (typeButton == PRESS_Y_BUTTON) {
    if (metaData->currentFocus != HINT_MENU_OPTION_FOCUS) {
      // Render hint popup menu
      HSHOH_drawHintPopUpMenu(metaData);
      // Change current focus
      metaData->currentFocus = HINT_MENU_OPTION_FOCUS;
    }
  } else if (typeButton == PRESS_A_BUTTON) {
    if (metaData->currentFocus == HINT_MENU_OPTION_FOCUS) {
      metaData->reRenderTrigger = true;
      // change focus to selected menu option
      if (metaData->hintOptionData.menuData.selectorData.selectorIndex ==
          STATISTICS_OPTION) {
        metaData->currentFocus = STATISTICS_FOCUS;
      } else if (metaData->hintOptionData.menuData.selectorData.selectorIndex ==
                 INVENTORY_OPTION) {
        metaData->currentFocus = INVENTORY_FOCUS;
      } else if (metaData->hintOptionData.menuData.selectorData.selectorIndex ==
                 MAP_OPTION) {
        metaData->currentFocus = MAP_FOCUS;
      } else if (metaData->hintOptionData.menuData.selectorData.selectorIndex ==
                 MENU_OPTION) {
        metaData->currentFocus = MENU_FOCUS;
      }
    }
  }
}
