#include "../../headers/handlers/hideoutSceneTopPanelHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/scenes/scene.h"
#include <genesis.h>
#include <string.h>

static const u16 LEVEL_TITLE[6] = {0x41, 0x33, 0x20, 0x28, 0x3E, 0x5A};
static const u16 EXPERIENCE_TITLE[6] = {0x23, 0x3F, 0x47, 0x20, 0x33, 0x2A};
static const u16 EXPERIENCE_SPLITER_TITLE = {0x74};
static const u16 CREDITS_TITLE = {0x42};

void HSTPH_dataInit(MetaData *metaData) {
  // Main border init data
  metaData->topPanelData.borderPosition = (Vec2){6, 1};
  metaData->topPanelData.borderSize = (SizeBox){33, 3};
  metaData->borderTilesData =
      (BorderTiles){BORDER_TOP_RIGHT,   BORDER_TOP_LEFT,    BORDER_BOTTOM_RIGHT,
                    BORDER_BOTTOM_LEFT, BORDER_TOP_SIDE,    BORDER_LEFT_SIDE,
                    BORDER_RIGHT_SIDE,  BORDER_BOTTOM_SIDE, BORDER_FILL};
  metaData->cursorTilesData =
      (CursorTiles){LEFT_CURSOR,       RIGHT_CURSOR,      UP_CURSOR,
                    DOWN_CURSOR,       A_SELECTOR_BUTTON, B_SELECTOR_BUTTON,
                    C_SELECTOR_BUTTON, X_SELECTOR_BUTTON, Y_SELECTOR_BUTTON,
                    Z_SELECTOR_BUTTON, DROP_DOWN_ICON};
  // Level init data
  memcpy(metaData->topPanelData.levelTitle, LEVEL_TITLE, sizeof(LEVEL_TITLE));
  metaData->topPanelData.levelTitlePosition = (Vec2){7, 2};
  metaData->topPanelData.levelValuePosition = (Vec2){14, 2};
  metaData->topPanelData.levelValue = &metaData->playerNode->levelData.level;
  // Experience init data
  memcpy(metaData->topPanelData.experienceTitle, EXPERIENCE_TITLE,
         sizeof(EXPERIENCE_TITLE));
  metaData->topPanelData.experienceTitlePosition = (Vec2){17, 2};
  metaData->topPanelData.currentExperience =
      &metaData->playerNode->levelData.currentExperience;
  metaData->topPanelData.currentExperiencePosition = (Vec2){24, 2};
  metaData->topPanelData.experienceNeededNext =
      &metaData->playerNode->levelData.experienceNeededNext;
  metaData->topPanelData.experienceNeededNextPosition = (Vec2){28, 2};
  // Experience spliter init data
  metaData->topPanelData.experienceSpliterTile = EXPERIENCE_SPLITER_TITLE;
  metaData->topPanelData.experienceSpliterTilePosition = (Vec2){27, 2};
  // Credit init data
  metaData->topPanelData.creditTitle = CREDITS_TITLE;
  metaData->topPanelData.creditTitlePosition = (Vec2){32, 2};
  metaData->topPanelData.creditSpliterTilePosition = (Vec2){33, 2};
  metaData->topPanelData.creditValue = &metaData->playerNode->creditValue;
  metaData->topPanelData.creditValuePosition = (Vec2){34, 2};
  metaData->topPanelData.creditSpliterTile = EXPERIENCE_SPLITER_TITLE;
}

void HSTPH_drawTopPanel(MetaData *metaData) {
  // Draw border
  drawBorder(metaData->topPanelData.borderPosition,
             metaData->topPanelData.borderSize, metaData->borderTilesData);
  HSTPH_renderLevelData(metaData);
  HSTPH_renderExperienceData(metaData);
  HSTPH_renderCreditsData(metaData);
}

void HSTPH_renderLevelData(MetaData *metaData) {
  // Draw level title
  drawTextTiles(metaData->topPanelData.levelTitlePosition,
                metaData->topPanelData.levelTitle,
                ARRAY_LEN(metaData->topPanelData.levelTitle));
  // Draw level value
  CFH_SplitDigits LV_u16ToSplitDigits =
      CFH_splitDigits(*metaData->topPanelData.levelValue);
  SceneTransformDigits LV_splitDigitsToHex =
      sceneTransformDigitsToHex(LV_u16ToSplitDigits);
  drawTextTiles(metaData->topPanelData.levelValuePosition,
                LV_splitDigitsToHex.hexDigits, LV_splitDigitsToHex.count);
}

void HSTPH_renderExperienceData(MetaData *metaData) {
  // Draw experience title
  drawTextTiles(metaData->topPanelData.experienceTitlePosition,
                metaData->topPanelData.experienceTitle,
                ARRAY_LEN(metaData->topPanelData.experienceTitle));
  // Draw current experience value
  CFH_SplitDigits ECV_u16ToSplitDigits =
      CFH_splitDigits(*metaData->topPanelData.currentExperience);
  SceneTransformDigits ECV_splitDigitsToHex =
      sceneTransformDigitsToHex(ECV_u16ToSplitDigits);
  drawTextTiles(metaData->topPanelData.currentExperiencePosition,
                ECV_splitDigitsToHex.hexDigits, ECV_splitDigitsToHex.count);
  // Draw experience split tile
  drawTile(metaData->topPanelData.experienceSpliterTilePosition,
           metaData->topPanelData.experienceSpliterTile);
  // Draw experience needed value
  CFH_SplitDigits ENV_u16ToSplitDigits =
      CFH_splitDigits(*metaData->topPanelData.experienceNeededNext);
  SceneTransformDigits ENV_splitDigitsToHex =
      sceneTransformDigitsToHex(ENV_u16ToSplitDigits);
  drawTextTiles(metaData->topPanelData.experienceNeededNextPosition,
                ENV_splitDigitsToHex.hexDigits, ENV_splitDigitsToHex.count);
}

void HSTPH_renderCreditsData(MetaData *metaData) {
  // Draw credit title
  drawTile(metaData->topPanelData.creditTitlePosition,
           metaData->topPanelData.creditTitle);
  // Draw credit split tile
  drawTile(metaData->topPanelData.creditSpliterTilePosition,
           metaData->topPanelData.creditSpliterTile);
  // Draw credit value
  CFH_SplitDigits CV_u16ToSplitDigits =
      CFH_splitDigits(*metaData->topPanelData.creditValue);
  SceneTransformDigits CV_splitDigitsToHex =
      sceneTransformDigitsToHex(CV_u16ToSplitDigits);
  drawTextTiles(metaData->topPanelData.creditValuePosition,
                CV_splitDigitsToHex.hexDigits, CV_splitDigitsToHex.count);
}
