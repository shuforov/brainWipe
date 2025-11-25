#include <genesis.h>
#include "../../headers/handlers/hideoutSceneInventoryHandler.h"

static const u16 INVENTORY_TEXT[8] = {0x2E, 0x3E, 0x20, 0x28,
                                      0x3E, 0x48, 0x1E, 0x46};

void HSIH_dataInit(MetaData *metaData) {
  metaData->topPanelData.inventoryData.textTitlePosition = (Vec2){12, 2};
  memcpy(metaData->topPanelData.inventoryData.textTitle, INVENTORY_TEXT,
         sizeof(INVENTORY_TEXT));
}

void HSIH_selectorInventoryHandle(MetaData *metaData, u16 typeButton) {
  if (typeButton == PRESS_C_BUTTON) {
    metaData->currentFocus = TOP_PANEL_FOCUS;
  }
}
