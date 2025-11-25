#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/hideoutSceneStatsHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"

static const u16 STATISTIC_TEXT[5] = {0x42, 0x48, 0x1E, 0x48, 0x5E};
static const u16 STATS_NAME_TITLE[4] = {0x2E, 0x3D, 0x58, 0x5C};
static const u16 STATS_NAME_DEFAULT[8] = {
    0x1C, 0x33, 0x46, 0x66, BORDER_FILL, BORDER_FILL, BORDER_FILL, BORDER_FILL};
static const u16 STATS_HEALTH_TITLE[4] = {0x27, 0x2A, 0x46, 0x5E};

void HSSH_dataInit(MetaData *metaData) {
  // TopPanel statistic title name
  metaData->topPanelData.statisticData.textTitlePosition = (Vec2){4, 2};
  // TopPanel statistic tiles
  memcpy(metaData->topPanelData.statisticData.textTitle, STATISTIC_TEXT,
         sizeof(STATISTIC_TEXT));
  // Player avatar data Border
  metaData->topPanelData.statisticData.avatar.borderPosition = (Vec2){1, 5};
  metaData->topPanelData.statisticData.avatar.borderSize = (SizeBox){10, 10};
  // Player avatar data Position
  metaData->topPanelData.statisticData.avatar.position = (Vec2){2, 6};
  // Player stats data Border
  metaData->topPanelData.statisticData.stats.borderPosition = (Vec2){12, 5};
  metaData->topPanelData.statisticData.stats.borderSize = (SizeBox){15, 5};
  // Player stats data name
  memcpy(metaData->topPanelData.statisticData.stats.nameTitle, STATS_NAME_TITLE,
         sizeof(STATS_NAME_TITLE));
  metaData->topPanelData.statisticData.stats.nameTitilePosition = (Vec2){13, 6};
  metaData->topPanelData.statisticData.stats.nameValuePosition = (Vec2){18, 6};
  memcpy(metaData->topPanelData.statisticData.stats.nameValue,
         STATS_NAME_DEFAULT, sizeof(STATS_NAME_DEFAULT));
  // Player stats data health
  memcpy(metaData->topPanelData.statisticData.stats.healthTitle,
         STATS_HEALTH_TITLE, sizeof(STATS_HEALTH_TITLE));
  metaData->topPanelData.statisticData.stats.healthTitlePosition =
      (Vec2){13, 7};
  metaData->topPanelData.statisticData.stats.healthValue =
      metaData->playerNode->stats.health;
  metaData->topPanelData.statisticData.stats.healthValuePosition =
      (Vec2){18, 7};
}

void HSSH_drawStatisticsOption(MetaData *metaData) {
  // Draw border avatar
  drawBorder(metaData->topPanelData.statisticData.avatar.borderPosition,
             metaData->topPanelData.statisticData.avatar.borderSize,
             metaData->borderTilesData);
  // Draw avatar
  HSSH_drawPlayerAvatar(metaData->topPanelData.statisticData.avatar.position);
  // Draw border stats
  drawBorder(metaData->topPanelData.statisticData.stats.borderPosition,
             metaData->topPanelData.statisticData.stats.borderSize,
             metaData->borderTilesData);
  // Draw name text title stats
  drawTextTiles(
      metaData->topPanelData.statisticData.stats.nameTitilePosition,
      metaData->topPanelData.statisticData.stats.nameTitle,
      ARRAY_LEN(metaData->topPanelData.statisticData.stats.nameTitle));
  // Draw name stats
  drawTextTiles(
      metaData->topPanelData.statisticData.stats.nameValuePosition,
      metaData->topPanelData.statisticData.stats.nameValue,
      ARRAY_LEN(metaData->topPanelData.statisticData.stats.nameValue));
  // Draw health text title stats
  drawTextTiles(
      metaData->topPanelData.statisticData.stats.healthTitlePosition,
      metaData->topPanelData.statisticData.stats.healthTitle,
      ARRAY_LEN(metaData->topPanelData.statisticData.stats.healthTitle));
  // Draw health stats
  CFH_SplitDigits u16ToSplitDigits =
      CFH_splitDigits(metaData->topPanelData.statisticData.stats.healthValue);
  SceneTransformDigits splitDigitsToHex =
      sceneTransformDigitsToHex(u16ToSplitDigits);
  drawTextTiles(metaData->topPanelData.statisticData.stats.healthValuePosition,
                splitDigitsToHex.hexDigits, splitDigitsToHex.count);
}

void HSSH_drawPlayerAvatar(Vec2 avatarPosition) {
  PAL_setPalette(PAL1, hideoutStatisticPalette.data, DMA);
  VDP_drawImageEx(BG_A, &playerAvatar, TILE_ATTR_FULL(PAL1, 0, 0, 0, 0x7A),
                  avatarPosition.x, avatarPosition.y, 0, CPU);
}

void HSSH_selectorStatsHandle(MetaData *metaData, u16 typeButton) {
  if (typeButton == PRESS_C_BUTTON) {
    metaData->currentFocus = TOP_PANEL_FOCUS;
  }
}
