#include <genesis.h>
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/hideoutSceneStatsTopPanelHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"

static const u16 STATS_TOP_MENU_STAT_NAME[5] = {0x42, 0x48, 0x1E, 0x48, 0x5E};
static const u16 STATS_TOP_MENU_OFFENSIVE_NAME[5] = {0x19, 0x48, 0x1E, 0x36,
                                                     0x1E};
static const u16 STATS_TOP_MENU_DEFENSIVE_NAME[6] = {0x27, 0x1E, 0x50,
                                                     0x32, 0x47, 0x48};
static const u16 STATS_TOP_MENU_UTILITY_NAME[9] = {0x23, 0x3F, 0x40, 0x3F, 0x3D,
                                                   0x33, 0x2B, 0x3E, 0x33};
static const Vec2 STATS_TOP_MENU_SELECTOR_POSITIONS[4] = {
    (Vec2){4, 6}, (Vec2){11, 6}, (Vec2){18, 6}, (Vec2){26, 6}};

void HSSTPH_dataInit(MetaData *metaData) {
  // Top stats options data
  metaData->hintOptionData.statisticData.topMenuData.leftHintPosition =
      (Vec2){2, 6};
  metaData->hintOptionData.statisticData.topMenuData.rightHintPosition =
      (Vec2){37, 6};
  metaData->hintOptionData.statisticData.topMenuData.selectorData
      .hintButtonPosition = (Vec2){3, 6};
  metaData->hintOptionData.statisticData.topMenuData.selectorData
      .hintButtonTile = metaData->cursorTilesData.xButton;
  metaData->hintOptionData.statisticData.topMenuData.selectorData
      .selectorPosition = (Vec2){4, 6};
  metaData->hintOptionData.statisticData.topMenuData.selectorData.selectorTile =
      metaData->cursorTilesData.right;
  metaData->hintOptionData.statisticData.topMenuData.selectorData
      .selectorIndex = 0;
  metaData->hintOptionData.statisticData.topMenuData.optionsData.statPositiona =
      (Vec2){5, 6};
  memcpy(metaData->hintOptionData.statisticData.topMenuData.optionsData
             .statTextTitles,
         STATS_TOP_MENU_STAT_NAME, sizeof(STATS_TOP_MENU_STAT_NAME));
  metaData->hintOptionData.statisticData.topMenuData.optionsData
      .offensivePosition = (Vec2){12, 6};
  memcpy(metaData->hintOptionData.statisticData.topMenuData.optionsData
             .offensiveTextTitles,
         STATS_TOP_MENU_OFFENSIVE_NAME, sizeof(STATS_TOP_MENU_OFFENSIVE_NAME));
  metaData->hintOptionData.statisticData.topMenuData.optionsData
      .defensivePosition = (Vec2){19, 6};
  memcpy(metaData->hintOptionData.statisticData.topMenuData.optionsData
             .defensiveTextTitles,
         STATS_TOP_MENU_DEFENSIVE_NAME, sizeof(STATS_TOP_MENU_DEFENSIVE_NAME));
  metaData->hintOptionData.statisticData.topMenuData.optionsData
      .utilityPosition = (Vec2){27, 6};
  memcpy(metaData->hintOptionData.statisticData.topMenuData.optionsData
             .utilityTextTitles,
         STATS_TOP_MENU_UTILITY_NAME, sizeof(STATS_TOP_MENU_UTILITY_NAME));
  // Current focus state
  metaData->hintOptionData.statisticData.topMenuData.currentFocus = STATISTICS_TOP_MENU_FOCUS;
}

void HSSTPH_drawSelector(MetaData *metaData) {
  for (u16 i = 0; i < 4; i++) {
    Vec2 selectorPosition = STATS_TOP_MENU_SELECTOR_POSITIONS[i];
    // Clear selector
    drawTile(selectorPosition, metaData->borderTilesData.fill);
    // Clear hint button selector
    drawTile((Vec2){selectorPosition.x - 1, selectorPosition.y},
             metaData->borderTilesData.fill);
  }
  drawTile(metaData->hintOptionData.statisticData.topMenuData.selectorData
               .hintButtonPosition,
           metaData->hintOptionData.statisticData.topMenuData.selectorData
               .hintButtonTile);
  drawTile(metaData->hintOptionData.statisticData.topMenuData.selectorData
               .selectorPosition,
           metaData->hintOptionData.statisticData.topMenuData.selectorData
               .selectorTile);
}

void HSSTPH_drawTopMenuOptions(MetaData *metaData) {
  // Draw common border
  drawBorder(metaData->hintOptionData.statisticData.borderPosition,
             metaData->hintOptionData.statisticData.borderSize,
             metaData->borderTilesData);
  // Draw options and selectors
  drawTile(metaData->hintOptionData.statisticData.topMenuData.leftHintPosition,
           metaData->cursorTilesData.left);
  drawTile(metaData->hintOptionData.statisticData.topMenuData.rightHintPosition,
           metaData->cursorTilesData.right);
  // Draw selector
  HSSTPH_drawSelector(metaData);
  drawTextTiles(metaData->hintOptionData.statisticData.topMenuData.optionsData
                    .statPositiona,
                metaData->hintOptionData.statisticData.topMenuData.optionsData
                    .statTextTitles,
                ARRAY_LEN(metaData->hintOptionData.statisticData.topMenuData
                              .optionsData.statTextTitles));
  drawTextTiles(metaData->hintOptionData.statisticData.topMenuData.optionsData
                    .offensivePosition,
                metaData->hintOptionData.statisticData.topMenuData.optionsData
                    .offensiveTextTitles,
                ARRAY_LEN(metaData->hintOptionData.statisticData.topMenuData
                              .optionsData.offensiveTextTitles));
  drawTextTiles(metaData->hintOptionData.statisticData.topMenuData.optionsData
                    .defensivePosition,
                metaData->hintOptionData.statisticData.topMenuData.optionsData
                    .defensiveTextTitles,
                ARRAY_LEN(metaData->hintOptionData.statisticData.topMenuData
                              .optionsData.defensiveTextTitles));
  drawTextTiles(metaData->hintOptionData.statisticData.topMenuData.optionsData
                    .utilityPosition,
                metaData->hintOptionData.statisticData.topMenuData.optionsData
                    .utilityTextTitles,
                ARRAY_LEN(metaData->hintOptionData.statisticData.topMenuData
                              .optionsData.utilityTextTitles));
}

void HSSTPH_selectorMovementHandler(MetaData *metaData, u16 typeButton) {
  if (typeButton == MOVE_SELECTOR_LEFT) {
    if (metaData->hintOptionData.statisticData.topMenuData.selectorData
            .selectorIndex > 0) {
      metaData->hintOptionData.statisticData.topMenuData.selectorData
          .selectorIndex--;
      metaData->hintOptionData.statisticData.topMenuData.selectorData
          .selectorPosition =
          STATS_TOP_MENU_SELECTOR_POSITIONS[metaData->hintOptionData
                                                .statisticData.topMenuData
                                                .selectorData.selectorIndex];
      Vec2 selectorPosition = metaData->hintOptionData.statisticData.topMenuData
                                  .selectorData.selectorPosition;
      metaData->hintOptionData.statisticData.topMenuData.selectorData
          .hintButtonPosition =
          (Vec2){selectorPosition.x - 1, selectorPosition.y};
      HSSTPH_drawSelector(metaData);
    }
  } else if (typeButton == MOVE_SELECTOR_RIGHT) {
    if (metaData->hintOptionData.statisticData.topMenuData.selectorData
            .selectorIndex < 3) {
      metaData->hintOptionData.statisticData.topMenuData.selectorData
          .selectorIndex++;
      metaData->hintOptionData.statisticData.topMenuData.selectorData
          .selectorPosition =
          STATS_TOP_MENU_SELECTOR_POSITIONS[metaData->hintOptionData
                                                .statisticData.topMenuData
                                                .selectorData.selectorIndex];
      Vec2 selectorPosition = metaData->hintOptionData.statisticData.topMenuData
                                  .selectorData.selectorPosition;
      metaData->hintOptionData.statisticData.topMenuData.selectorData
          .hintButtonPosition =
          (Vec2){selectorPosition.x - 1, selectorPosition.y};
      HSSTPH_drawSelector(metaData);
    }
  }
}
