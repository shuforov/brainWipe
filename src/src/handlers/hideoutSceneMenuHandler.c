#include <genesis.h>
#include "../../headers/handlers/hideoutSceneMenuHandler.h"

static const u16 MENU_TEXT[4] = {0x38, 0x28, 0x3E, 0x5B};

void HSMEH_dataInit(MetaData *metaData) {
  memcpy(metaData->topPanelData.menuData.textTitle, MENU_TEXT,
         sizeof(MENU_TEXT));
  metaData->topPanelData.menuData.textTitlePosition = (Vec2){32, 2};
}

void HSMEH_selectorInventoryHandle(MetaData *metaData, u16 typeButton) {
  if (typeButton == PRESS_C_BUTTON) {
    metaData->currentFocus = TOP_PANEL_FOCUS;
  }
}
