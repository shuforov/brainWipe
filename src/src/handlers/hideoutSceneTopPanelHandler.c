#include <genesis.h>
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/hideoutSceneTopPanelHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/hideoutSceneCommonFunctions.h"
#include "../../headers/handlers/hideoutSceneStatsHandler.h"

static const Vec2 CURSOR_POSITIONS[4] = {(Vec2){3, 2}, (Vec2){11, 2},
                                         (Vec2){22, 2}, (Vec2){31, 2}};

void HSTPH_dataInit(MetaData *metaData) {
  metaData->topPanelData.borderPosition = (Vec2){1, 1};
  metaData->topPanelData.borderSize = (SizeBox){38, 3};
  metaData->borderTilesData =
      (BorderTiles){BORDER_TOP_RIGHT,   BORDER_TOP_LEFT,    BORDER_BOTTOM_RIGHT,
                    BORDER_BOTTOM_LEFT, BORDER_TOP_SIDE,    BORDER_LEFT_SIDE,
                    BORDER_RIGHT_SIDE,  BORDER_BOTTOM_SIDE, BORDER_FILL};
  metaData->cursorTilesData =
      (CursorTiles){LEFT_CURSOR,       RIGHT_CURSOR,      UP_CURSOR,
                    DOWN_CURSOR,       A_SELECTOR_BUTTON, B_SELECTOR_BUTTON,
                    C_SELECTOR_BUTTON, X_SELECTOR_BUTTON, Y_SELECTOR_BUTTON,
                    Z_SELECTOR_BUTTON};
  metaData->topPanelData.cursorRightPosition = (Vec2){3, 2};
  metaData->topPanelData.selectorIndex = 0;
  memcpy(metaData->topPanelData.cursorPostions, CURSOR_POSITIONS,
         sizeof(CURSOR_POSITIONS));
  metaData->optionSpacePosition = (Vec2){1, 5};
  metaData->optionSpaceSize = (SizeBox){38, 25};
}

void HSTPH_drawTopPanelCursor(MetaData *metaData) {
  // Clear tiles
  for (u16 i = 0; i < ARRAY_LEN(metaData->topPanelData.cursorPostions); i++) {
    // Clear cursor tile
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData->borderTilesData.fill),
        metaData->topPanelData.cursorPostions[i].x,
        metaData->topPanelData.cursorPostions[i].y);
    // Clear Y button
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData->borderTilesData.fill),
        metaData->topPanelData.cursorPostions[i].x - 1,
        metaData->topPanelData.cursorPostions[i].y);
  }
  // Draw right cursor arrow button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData->cursorTilesData.right),
      metaData->topPanelData.cursorRightPosition.x,
      metaData->topPanelData.cursorRightPosition.y);
  // Draw Y button
  VDP_setTileMapXY(
      BG_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, metaData->cursorTilesData.cButton),
      metaData->topPanelData.cursorRightPosition.x - 1,
      metaData->topPanelData.cursorRightPosition.y);
}

void HSTPH_drawTopPanel(MetaData *metaData) {
  // Draw border
  drawBorder(metaData->topPanelData.borderPosition,
             metaData->topPanelData.borderSize, metaData->borderTilesData);
  // Draw Text in border
  // Draw statistic title
  drawTextTiles(metaData->topPanelData.statisticData.textTitlePosition,
                metaData->topPanelData.statisticData.textTitle,
                ARRAY_LEN(metaData->topPanelData.statisticData.textTitle));
  // Draw inventory title
  drawTextTiles(metaData->topPanelData.inventoryData.textTitlePosition,
                metaData->topPanelData.inventoryData.textTitle,
                ARRAY_LEN(metaData->topPanelData.inventoryData.textTitle));
  // Draw map title
  drawTextTiles(metaData->topPanelData.mapData.textTitlePosition,
                metaData->topPanelData.mapData.textTitle,
                ARRAY_LEN(metaData->topPanelData.mapData.textTitle));
  // Draw menu title
  drawTextTiles(metaData->topPanelData.menuData.textTitlePosition,
                metaData->topPanelData.menuData.textTitle,
                ARRAY_LEN(metaData->topPanelData.menuData.textTitle));
  // Draw Right cursor arrow button
  HSTPH_drawTopPanelCursor(metaData);
}

void HSTPH_selectorTopPanelHandle(MetaData *metaData, u16 typeButton) {
  if (typeButton == MOVE_SELECTOR_LEFT) {
    if (metaData->topPanelData.selectorIndex > 0) {
      metaData->topPanelData.selectorIndex--;
      metaData->topPanelData.cursorRightPosition =
          metaData->topPanelData
              .cursorPostions[metaData->topPanelData.selectorIndex];
      HSTPH_drawTopPanelCursor(metaData);
    }
  } else if (typeButton == MOVE_SELECTOR_RIGHT) {
    if (metaData->topPanelData.selectorIndex < 3) {
      metaData->topPanelData.selectorIndex++;
      metaData->topPanelData.cursorRightPosition =
          metaData->topPanelData
              .cursorPostions[metaData->topPanelData.selectorIndex];
      HSTPH_drawTopPanelCursor(metaData);
    }
  } else if (typeButton == PRESS_C_BUTTON) {
    if (metaData->topPanelData.selectorIndex == STATISTICS_OPTION) {
      HSCF_clearOptionSpace(metaData);
      HSSH_drawStatisticsOption(metaData);
      metaData->currentFocus = STATISTICS_FOCUS;
    } else if (metaData->topPanelData.selectorIndex == INVENTORY_OPTION) {
      HSCF_clearOptionSpace(metaData);
      VDP_drawText("Inventory option", 10, 10);
      metaData->currentFocus = INVENTORY_FOCUS;
    } else if (metaData->topPanelData.selectorIndex == MAP_OPTION) {
      HSCF_clearOptionSpace(metaData);
      VDP_drawText("Map option", 10, 10);
      metaData->currentFocus = MAP_FOCUS;
    } else if (metaData->topPanelData.selectorIndex == MENU_OPTION) {
      HSCF_clearOptionSpace(metaData);
      VDP_drawText("Menu option", 10, 10);
      metaData->currentFocus = MENU_FOCUS;
    }
  }
}
