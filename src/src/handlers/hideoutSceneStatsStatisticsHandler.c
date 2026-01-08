#include "../../headers/handlers/hideoutSceneStatsStatisticsHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/scenes/scene.h"
#include "../res/resources.h"
#include <genesis.h>

static const u16 STATS_NAME_TITLE[4] = {0x2E, 0x3D, 0x58, 0x5C};
static const u16 STATS_HEALTH_TITLE[4] = {0x27, 0x2A, 0x46, 0x5E};
static const u16 STATS_NAME_DEFAULT[8] = {
    0x1C, 0x33, 0x46, 0x66, BORDER_FILL, BORDER_FILL, BORDER_FILL, BORDER_FILL};
static const u16 START_AVATAR_IMAGE_REGISTER = 0x81;
static const u16 STATS_ATTACK_TITLE[4] = {0x19, 0x43, 0x31, 0x5E};
static const u16 STATS_DEFENSE_TITLE[4] = {0x27, 0x4B, 0x43, 0x5E};
static const u16 STATS_CRIT_TITLE[4] = {0x31, 0x41, 0x43, 0x5E};
static const u16 STATS_EVASION_TITLE[4] = {0x44, 0x4B, 0x37, 0x5E};

void HSSSH_dataInit(MetaData *metaData) {
  // Player stats data Border
  metaData->hintOptionData.statisticData.statisticsData.borderPosition =
      (Vec2){13, 8};
  metaData->hintOptionData.statisticData.statisticsData.borderSize =
      (SizeBox){15, 8};
  // Player avatar data Border
  metaData->hintOptionData.statisticData.statisticsData.avatar.borderPosition =
      (Vec2){2, 8};
  metaData->hintOptionData.statisticData.statisticsData.avatar.borderSize =
      (SizeBox){10, 10};
  // Player avatar data Position
  metaData->hintOptionData.statisticData.statisticsData.avatar.position =
      (Vec2){3, 9};
  // Player stats data name
  memcpy(metaData->hintOptionData.statisticData.statisticsData.nameTitle,
         STATS_NAME_TITLE, sizeof(STATS_NAME_TITLE));
  metaData->hintOptionData.statisticData.statisticsData.nameTitilePosition =
      (Vec2){14, 9};
  metaData->hintOptionData.statisticData.statisticsData.nameValuePosition =
      (Vec2){19, 9};
  memcpy(metaData->hintOptionData.statisticData.statisticsData.nameValue,
         STATS_NAME_DEFAULT, sizeof(STATS_NAME_DEFAULT));
  // Player stats data health
  memcpy(metaData->hintOptionData.statisticData.statisticsData.healthTitle,
         STATS_HEALTH_TITLE, sizeof(STATS_HEALTH_TITLE));
  metaData->hintOptionData.statisticData.statisticsData.healthTitlePosition =
      (Vec2){14, 10};
  metaData->hintOptionData.statisticData.statisticsData.healthValue =
      &metaData->playerNode->stats.healthPoint;
  metaData->hintOptionData.statisticData.statisticsData.healthValuePosition =
      (Vec2){19, 10};
  // Player stats data attack
  memcpy(metaData->hintOptionData.statisticData.statisticsData.attackTitle,
         STATS_ATTACK_TITLE, sizeof(STATS_ATTACK_TITLE));
  metaData->hintOptionData.statisticData.statisticsData.attackTitlePosition =
      (Vec2){14, 11};
  metaData->hintOptionData.statisticData.statisticsData.attackValue =
      &metaData->playerNode->stats.attak;
  metaData->hintOptionData.statisticData.statisticsData.attackValuePosition =
      (Vec2){19, 11};
  // Player stats data defense
  memcpy(metaData->hintOptionData.statisticData.statisticsData.defenseTitle,
         STATS_DEFENSE_TITLE, sizeof(STATS_DEFENSE_TITLE));
  metaData->hintOptionData.statisticData.statisticsData.defenseTitlePosition =
      (Vec2){14, 12};
  metaData->hintOptionData.statisticData.statisticsData.defenseValue =
      &metaData->playerNode->stats.defense;
  metaData->hintOptionData.statisticData.statisticsData.defenseValuePosition =
      (Vec2){19, 12};
  // Player stats data crit
  memcpy(metaData->hintOptionData.statisticData.statisticsData.critTitle,
         STATS_CRIT_TITLE, sizeof(STATS_CRIT_TITLE));
  metaData->hintOptionData.statisticData.statisticsData.critTitlePosition =
      (Vec2){14, 13};
  metaData->hintOptionData.statisticData.statisticsData.critValue =
      &metaData->playerNode->stats.crit;
  metaData->hintOptionData.statisticData.statisticsData.critValuePosition =
      (Vec2){19, 13};
  // Player stats data evasion
  memcpy(metaData->hintOptionData.statisticData.statisticsData.evasionTitle,
         STATS_EVASION_TITLE, sizeof(STATS_EVASION_TITLE));
  metaData->hintOptionData.statisticData.statisticsData.evasionTitlePosition =
      (Vec2){14, 14};
  metaData->hintOptionData.statisticData.statisticsData.evasionValue =
      &metaData->playerNode->stats.evasion;
  metaData->hintOptionData.statisticData.statisticsData.evasionValuePosition =
      (Vec2){19, 14};
}

void HSSSH_drawPlayerAvatar(Vec2 avatarPosition) {
  PAL_setPalette(PAL1, hideoutStatisticPalette.data, DMA);
  VDP_drawImageEx(BG_A, &playerAvatar,
                  TILE_ATTR_FULL(PAL1, 0, 0, 0, START_AVATAR_IMAGE_REGISTER),
                  avatarPosition.x, avatarPosition.y, 0, CPU);
}

void HSSSH_statisticsRender(MetaData *metaData) {
  // Draw border avatar
  drawBorder(
      metaData->hintOptionData.statisticData.statisticsData.avatar
          .borderPosition,
      metaData->hintOptionData.statisticData.statisticsData.avatar.borderSize,
      metaData->borderTilesData);
  // Draw avatar
  HSSSH_drawPlayerAvatar(
      metaData->hintOptionData.statisticData.statisticsData.avatar.position);
  // Draw border stats
  drawBorder(
      metaData->hintOptionData.statisticData.statisticsData.borderPosition,
      metaData->hintOptionData.statisticData.statisticsData.borderSize,
      metaData->borderTilesData);
  // Draw name text title stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData.nameTitilePosition,
      metaData->hintOptionData.statisticData.statisticsData.nameTitle,
      ARRAY_LEN(
          metaData->hintOptionData.statisticData.statisticsData.nameTitle));
  // Draw name stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData.nameValuePosition,
      metaData->hintOptionData.statisticData.statisticsData.nameValue,
      ARRAY_LEN(
          metaData->hintOptionData.statisticData.statisticsData.nameValue));
  // Draw health text title stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData.healthTitlePosition,
      metaData->hintOptionData.statisticData.statisticsData.healthTitle,
      ARRAY_LEN(
          metaData->hintOptionData.statisticData.statisticsData.healthTitle));
  // Draw health stats
  CFH_SplitDigits HS_u16ToSplitDigits = CFH_splitDigits(
      *metaData->hintOptionData.statisticData.statisticsData.healthValue);
  SceneTransformDigits HS_splitDigitsToHex =
      sceneTransformDigitsToHex(HS_u16ToSplitDigits);
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData.healthValuePosition,
      HS_splitDigitsToHex.hexDigits, HS_splitDigitsToHex.count);
  // Draw attack stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData.attackTitlePosition,
      metaData->hintOptionData.statisticData.statisticsData.attackTitle,
      ARRAY_LEN(
          metaData->hintOptionData.statisticData.statisticsData.attackTitle));
  CFH_SplitDigits AS_u16ToSplitDigits = CFH_splitDigits(
      *metaData->hintOptionData.statisticData.statisticsData.attackValue);
  SceneTransformDigits AS_splitDigitsToHex =
      sceneTransformDigitsToHex(AS_u16ToSplitDigits);
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData.attackValuePosition,
      AS_splitDigitsToHex.hexDigits, AS_splitDigitsToHex.count);
  // Draw defense stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData
          .defenseTitlePosition,
      metaData->hintOptionData.statisticData.statisticsData.defenseTitle,
      ARRAY_LEN(
          metaData->hintOptionData.statisticData.statisticsData.defenseTitle));
  CFH_SplitDigits DS_u16ToSplitDigits = CFH_splitDigits(
      *metaData->hintOptionData.statisticData.statisticsData.defenseValue);
  SceneTransformDigits DS_splitDigitsToHex =
      sceneTransformDigitsToHex(DS_u16ToSplitDigits);
  drawTextTiles(metaData->hintOptionData.statisticData.statisticsData
                    .defenseValuePosition,
                DS_splitDigitsToHex.hexDigits, DS_splitDigitsToHex.count);
  // Draw crit stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData.critTitlePosition,
      metaData->hintOptionData.statisticData.statisticsData.critTitle,
      ARRAY_LEN(
          metaData->hintOptionData.statisticData.statisticsData.critTitle));
  CFH_SplitDigits CS_u16ToSplitDigits = CFH_splitDigits(
      *metaData->hintOptionData.statisticData.statisticsData.critValue);
  SceneTransformDigits CS_splitDigitsToHex =
      sceneTransformDigitsToHex(CS_u16ToSplitDigits);
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData.critValuePosition,
      CS_splitDigitsToHex.hexDigits, CS_splitDigitsToHex.count);
  // Draw evasion stats
  drawTextTiles(
      metaData->hintOptionData.statisticData.statisticsData
          .evasionTitlePosition,
      metaData->hintOptionData.statisticData.statisticsData.evasionTitle,
      ARRAY_LEN(
          metaData->hintOptionData.statisticData.statisticsData.evasionTitle));
  CFH_SplitDigits ES_u16ToSplitDigits = CFH_splitDigits(
      *metaData->hintOptionData.statisticData.statisticsData.evasionValue);
  SceneTransformDigits ES_splitDigitsToHex =
      sceneTransformDigitsToHex(ES_u16ToSplitDigits);
  drawTextTiles(metaData->hintOptionData.statisticData.statisticsData
                    .evasionValuePosition,
                ES_splitDigitsToHex.hexDigits, ES_splitDigitsToHex.count);
}
