#include <genesis.h>
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/hideoutSceneTopPanelHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"

void HSTPH_dataInit(MetaData *metaData) {
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
}

void HSTPH_drawTopPanel(MetaData *metaData) {
  // Draw border
  drawBorder(metaData->topPanelData.borderPosition,
             metaData->topPanelData.borderSize, metaData->borderTilesData);
}
