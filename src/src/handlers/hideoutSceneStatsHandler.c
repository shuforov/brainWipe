#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/hideoutSceneStatsHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"

typedef enum {
  TMS_STATS,
  TMS_OFFENSIVE,
  TMS_DEFENSIVE,
  TMS_UTILITY
} TopMenuStates;
static const u16 STATISTIC_TEXT[5] = {0x42, 0x48, 0x1E, 0x48, 0x5E};
static const u16 STATS_NAME_TITLE[4] = {0x2E, 0x3D, 0x58, 0x5C};
static const u16 STATS_NAME_DEFAULT[8] = {
    0x1C, 0x33, 0x46, 0x66, BORDER_FILL, BORDER_FILL, BORDER_FILL, BORDER_FILL};
static const u16 STATS_HEALTH_TITLE[4] = {0x27, 0x2A, 0x46, 0x5E};
static const u16 STATS_TOP_MENU_STAT_NAME[5] = {0x42, 0x48, 0x1E, 0x48, 0x5E};
static const u16 STATS_TOP_MENU_OFFENSIVE_NAME[5] = {0x19, 0x48, 0x1E, 0x36,
                                                     0x1E};
static const u16 STATS_TOP_MENU_DEFENSIVE_NAME[6] = {0x27, 0x1E, 0x50,
                                                     0x32, 0x47, 0x48};
static const u16 STATS_TOP_MENU_UTILITY_NAME[9] = {0x23, 0x3F, 0x40, 0x3F, 0x3D,
                                                   0x33, 0x2B, 0x3E, 0x33};
static const Vec2 STATS_TOP_MENU_SELECTOR_POSITIONS[4] = {
    (Vec2){4, 6}, (Vec2){11, 6}, (Vec2){18, 6}, (Vec2){26, 6}};

u16 statsCurrentFocus = STATISTICS_TOP_MENU_FOCUS;

void HSSH_dataInit(MetaData *metaData) {
  // Common statistic border position
  metaData->hintOptionData.statisticData.borderPosition = (Vec2){1, 5};
  // Common statistic border size
  metaData->hintOptionData.statisticData.borderSize = (SizeBox){38, 22};
  // Statistic focus box position
  metaData->hintOptionData.statisticData.focusBoxPosition = (Vec2){2, 8};
  // Statistic focus box size
  metaData->hintOptionData.statisticData.focusBoxSize = (SizeBox){36, 17};
  // HintOption statistic title name
  metaData->hintOptionData.statisticData.textTitlePosition = (Vec2){4, 2};
  // HintOption statistic tiles
  memcpy(metaData->hintOptionData.statisticData.textTitle, STATISTIC_TEXT,
         sizeof(STATISTIC_TEXT));
  // Player avatar data Border
  metaData->hintOptionData.statisticData.avatar.borderPosition = (Vec2){2, 8};
  metaData->hintOptionData.statisticData.avatar.borderSize = (SizeBox){10, 10};
  // Player avatar data Position
  metaData->hintOptionData.statisticData.avatar.position = (Vec2){3, 9};
  // Player stats data Border
  metaData->hintOptionData.statisticData.stats.borderPosition = (Vec2){13, 8};
  metaData->hintOptionData.statisticData.stats.borderSize = (SizeBox){15, 5};
  // Player stats data name
  memcpy(metaData->hintOptionData.statisticData.stats.nameTitle, STATS_NAME_TITLE,
         sizeof(STATS_NAME_TITLE));
  metaData->hintOptionData.statisticData.stats.nameTitilePosition = (Vec2){14, 9};
  metaData->hintOptionData.statisticData.stats.nameValuePosition = (Vec2){19, 9};
  memcpy(metaData->hintOptionData.statisticData.stats.nameValue,
         STATS_NAME_DEFAULT, sizeof(STATS_NAME_DEFAULT));
  // Player stats data health
  memcpy(metaData->hintOptionData.statisticData.stats.healthTitle,
         STATS_HEALTH_TITLE, sizeof(STATS_HEALTH_TITLE));
  metaData->hintOptionData.statisticData.stats.healthTitlePosition =
      (Vec2){14, 10};
  metaData->hintOptionData.statisticData.stats.healthValue =
      metaData->playerNode->stats.health;
  metaData->hintOptionData.statisticData.stats.healthValuePosition =
      (Vec2){19, 10};
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
}

void HSSH_drawStatisticsOption(MetaData *metaData) {
  // Draw border avatar
  drawBorder(metaData->hintOptionData.statisticData.avatar.borderPosition,
             metaData->hintOptionData.statisticData.avatar.borderSize,
             metaData->borderTilesData);
  // Draw avatar
  HSSH_drawPlayerAvatar(metaData->hintOptionData.statisticData.avatar.position);
  // Draw border stats
  drawBorder(metaData->hintOptionData.statisticData.stats.borderPosition,
             metaData->hintOptionData.statisticData.stats.borderSize,
             metaData->borderTilesData);
  // Draw name text title stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.stats.nameTitilePosition,
      metaData->hintOptionData.statisticData.stats.nameTitle,
      ARRAY_LEN(metaData->hintOptionData.statisticData.stats.nameTitle));
  // Draw name stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.stats.nameValuePosition,
      metaData->hintOptionData.statisticData.stats.nameValue,
      ARRAY_LEN(metaData->hintOptionData.statisticData.stats.nameValue));
  // Draw health text title stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.stats.healthTitlePosition,
      metaData->hintOptionData.statisticData.stats.healthTitle,
      ARRAY_LEN(metaData->hintOptionData.statisticData.stats.healthTitle));
  // Draw health stats
  CFH_SplitDigits u16ToSplitDigits =
      CFH_splitDigits(metaData->hintOptionData.statisticData.stats.healthValue);
  SceneTransformDigits splitDigitsToHex =
      sceneTransformDigitsToHex(u16ToSplitDigits);
  drawTextTiles(
      metaData->hintOptionData.statisticData.stats.healthValuePosition,
      splitDigitsToHex.hexDigits, splitDigitsToHex.count);
}

void HSSH_drawTopMenuOptions(MetaData *metaData) {
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
  HSSH_drawSelector(metaData);
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

void HSSH_drawPlayerAvatar(Vec2 avatarPosition) {
  PAL_setPalette(PAL1, hideoutStatisticPalette.data, DMA);
  VDP_drawImageEx(BG_A, &playerAvatar, TILE_ATTR_FULL(PAL1, 0, 0, 0, 0x7A),
                  avatarPosition.x, avatarPosition.y, 0, CPU);
}

void HSSH_reRenderSelector(MetaData *metaData) {
  for (u16 i = 0; i < 4; i++) {
    Vec2 selectorPosition = STATS_TOP_MENU_SELECTOR_POSITIONS[i];
    // Clear selector
    drawTile(selectorPosition, metaData->borderTilesData.fill);
    // Clear hint button selector
    drawTile((Vec2){selectorPosition.x - 1, selectorPosition.y},
             metaData->borderTilesData.fill);
  }
  HSSH_drawSelector(metaData);
}

void HSSH_drawSelector(MetaData *metaData) {
  drawTile(metaData->hintOptionData.statisticData.topMenuData.selectorData
               .hintButtonPosition,
           metaData->hintOptionData.statisticData.topMenuData.selectorData
               .hintButtonTile);
  drawTile(metaData->hintOptionData.statisticData.topMenuData.selectorData
               .selectorPosition,
           metaData->hintOptionData.statisticData.topMenuData.selectorData
               .selectorTile);
}

void HSSH_clearFocusBox(MetaData *metaData) {
  drawFillBox(metaData->hintOptionData.statisticData.focusBoxPosition,
              metaData->hintOptionData.statisticData.focusBoxSize,
              metaData->borderTilesData.fill);
}

void HSSH_selectorStatsHandle(MetaData *metaData, u16 typeButton) {
  if (typeButton == PRESS_Y_BUTTON) {
    metaData->currentFocus = HINT_MENU_OPTION_FOCUS;
    metaData->reRenderTrigger = true;
  } else if (typeButton == MOVE_SELECTOR_RIGHT) {
    if (statsCurrentFocus == STATISTICS_TOP_MENU_FOCUS) {
      if (metaData->hintOptionData.statisticData.topMenuData.selectorData
              .selectorIndex < 3) {
        metaData->hintOptionData.statisticData.topMenuData.selectorData
            .selectorIndex++;
        metaData->hintOptionData.statisticData.topMenuData.selectorData
            .selectorPosition =
            STATS_TOP_MENU_SELECTOR_POSITIONS[metaData->hintOptionData
                                                  .statisticData.topMenuData
                                                  .selectorData.selectorIndex];
        Vec2 selectorPosition = metaData->hintOptionData.statisticData
                                    .topMenuData.selectorData.selectorPosition;
        metaData->hintOptionData.statisticData.topMenuData.selectorData
            .hintButtonPosition =
            (Vec2){selectorPosition.x - 1, selectorPosition.y};
        HSSH_reRenderSelector(metaData);
      }
    }
  } else if (typeButton == MOVE_SELECTOR_LEFT) {
    if (statsCurrentFocus == STATISTICS_TOP_MENU_FOCUS) {
      if (metaData->hintOptionData.statisticData.topMenuData.selectorData
              .selectorIndex > 0) {
        metaData->hintOptionData.statisticData.topMenuData.selectorData
            .selectorIndex--;
        metaData->hintOptionData.statisticData.topMenuData.selectorData
            .selectorPosition =
            STATS_TOP_MENU_SELECTOR_POSITIONS[metaData->hintOptionData
                                                  .statisticData.topMenuData
                                                  .selectorData.selectorIndex];
        Vec2 selectorPosition = metaData->hintOptionData.statisticData
                                    .topMenuData.selectorData.selectorPosition;
        metaData->hintOptionData.statisticData.topMenuData.selectorData
            .hintButtonPosition =
            (Vec2){selectorPosition.x - 1, selectorPosition.y};
        HSSH_reRenderSelector(metaData);
      }
    }
  } else if (typeButton == PRESS_X_BUTTON) {
    if (statsCurrentFocus == STATISTICS_TOP_MENU_FOCUS) {
      if (metaData->hintOptionData.statisticData.topMenuData.selectorData
              .selectorIndex == TMS_STATS) {
        HSSH_drawStatisticsOption(metaData);
	statsCurrentFocus = STATISTICS_STATS_FOCUS;
      }
    } else if (statsCurrentFocus == STATISTICS_STATS_FOCUS) {
      HSSH_clearFocusBox(metaData);
      statsCurrentFocus = STATISTICS_TOP_MENU_FOCUS;
    }
  }
}
