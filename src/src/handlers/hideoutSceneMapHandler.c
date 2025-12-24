#include <genesis.h>
#include "../../headers/handlers/hideoutSceneMapHandler.h"

static const u16 MAP_TEXT[5] = {0x31, 0x1E, 0x46, 0x48, 0x1E};

void HSMH_dataInit(MetaData *metaData) {
  memcpy(metaData->topPanelData.mapData.textTitle, MAP_TEXT, sizeof(MAP_TEXT));
  metaData->topPanelData.mapData.textTitlePosition = (Vec2){23, 2};
}

void HSMH_selectorInventoryHandle(MetaData *metaData, u16 typeButton) {}
