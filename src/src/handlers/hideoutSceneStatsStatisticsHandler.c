#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/hideoutSceneStatsStatisticsHandler.h"
#include "../../headers/scenes/scene.h"

static const u16 STATS_NAME_TITLE[4] = {0x2E, 0x3D, 0x58, 0x5C};
static const u16 STATS_HEALTH_TITLE[4] = {0x27, 0x2A, 0x46, 0x5E};
static const u16 STATS_NAME_DEFAULT[8] = {
    0x1C, 0x33, 0x46, 0x66, BORDER_FILL, BORDER_FILL, BORDER_FILL, BORDER_FILL};
static const u16 START_AVATAR_IMAGE_REGISTER = 0x81;

void HSSSH_dataInit(MetaData *metaData) {
  // Player avatar data Border
  metaData->hintOptionData.statisticData.avatar.borderPosition = (Vec2){2, 8};
  metaData->hintOptionData.statisticData.avatar.borderSize = (SizeBox){10, 10};
  // Player avatar data Position
  metaData->hintOptionData.statisticData.avatar.position = (Vec2){3, 9};
  // Player stats data Border
  metaData->hintOptionData.statisticData.stats.borderPosition = (Vec2){13, 8};
  metaData->hintOptionData.statisticData.stats.borderSize = (SizeBox){15, 5};
  // Player stats data name
  memcpy(metaData->hintOptionData.statisticData.stats.nameTitle,
         STATS_NAME_TITLE, sizeof(STATS_NAME_TITLE));
  metaData->hintOptionData.statisticData.stats.nameTitilePosition =
      (Vec2){14, 9};
  metaData->hintOptionData.statisticData.stats.nameValuePosition =
      (Vec2){19, 9};
  memcpy(metaData->hintOptionData.statisticData.stats.nameValue,
         STATS_NAME_DEFAULT, sizeof(STATS_NAME_DEFAULT));
  // Player stats data health
  memcpy(metaData->hintOptionData.statisticData.stats.healthTitle,
         STATS_HEALTH_TITLE, sizeof(STATS_HEALTH_TITLE));
  metaData->hintOptionData.statisticData.stats.healthTitlePosition =
      (Vec2){14, 10};
  metaData->hintOptionData.statisticData.stats.healthValue =
      metaData->playerNode->stats.healthPoint;
  metaData->hintOptionData.statisticData.stats.healthValuePosition =
      (Vec2){19, 10};
}

void HSSSH_drawPlayerAvatar(Vec2 avatarPosition) {
  PAL_setPalette(PAL1, hideoutStatisticPalette.data, DMA);
  VDP_drawImageEx(BG_A, &playerAvatar,
                  TILE_ATTR_FULL(PAL1, 0, 0, 0, START_AVATAR_IMAGE_REGISTER),
                  avatarPosition.x, avatarPosition.y, 0, CPU);
}

void HSSSH_statisticsRender(MetaData *metaData) {
  // Draw border avatar
  drawBorder(metaData->hintOptionData.statisticData.avatar.borderPosition,
             metaData->hintOptionData.statisticData.avatar.borderSize,
             metaData->borderTilesData);
  // Draw avatar
  HSSSH_drawPlayerAvatar(
      metaData->hintOptionData.statisticData.avatar.position);
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
