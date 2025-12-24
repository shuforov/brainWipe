#include <genesis.h>
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/hideoutSceneHintOptionHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/hideoutSceneCommonFunctions.h"

void HSHOH_dataInit(MetaData *metaData) {
  metaData->hintOptionData.borderPosition = (Vec2){1, 1};
  metaData->hintOptionData.borderSize = (SizeBox){4, 3};
  metaData->hintOptionData.hintButtonPosition = (Vec2){2, 2};
  metaData->hintOptionData.hintIconPosition = (Vec2){3, 2};
  metaData->hintOptionData.menuData.selectorIndex = STATISTICS_OPTION;
  metaData->hintOptionData.menuData.borderPosition = (Vec2){1, 1};
  metaData->hintOptionData.menuData.borderSize = (SizeBox){6, 6};
}

void HSHOH_drawHintMenu(MetaData *metaData) {
  // Draw border
  drawBorder(metaData->hintOptionData.borderPosition,
             metaData->hintOptionData.borderSize, metaData->borderTilesData);
  // Draw hint button
  drawTile(metaData->hintOptionData.hintButtonPosition, metaData->cursorTilesData.yButton);
  // Draw hint drop down icon
  drawTile(metaData->hintOptionData.hintIconPosition, metaData->cursorTilesData.dropDownIcon);
}

void HSHO_selectorStatsHandle(MetaData *metaData, u16 typeButton) {
  if (typeButton == MOVE_SELECTOR_UP) {
    if (metaData->hintOptionData.menuData.selectorIndex > 1) {
      metaData->hintOptionData.menuData.selectorIndex--;
    }
  } else if (typeButton == MOVE_SELECTOR_DOWN) {
    if (metaData->hintOptionData.menuData.selectorIndex < 3) {
      metaData->hintOptionData.menuData.selectorIndex++;
    }
  } else if (typeButton == PRESS_Y_BUTTON) {
    if (metaData->currentFocus != HINT_MENU_OPTION_FOCUS) {
      // Render hint popup menu
      drawBorder(metaData->hintOptionData.menuData.borderPosition,
                 metaData->hintOptionData.menuData.borderSize,
                 metaData->borderTilesData);
      // Change current focus
      metaData->currentFocus = HINT_MENU_OPTION_FOCUS;
    }
  } else if (typeButton == PRESS_A_BUTTON) {
    if (metaData->currentFocus == HINT_MENU_OPTION_FOCUS) {
      metaData->reRenderTrigger = true;
      // change focus to selected menu option
      metaData->currentFocus = metaData->hintOptionData.menuData.selectorIndex;
    }
  }
}
