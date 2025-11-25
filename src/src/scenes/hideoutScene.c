#include <genesis.h>
#include "../res/resources.h"
#include "../../headers/scenes/hideoutScene.h"
#include "../../headers/handlers/debugHandler.h"
#include "../../headers/handlers/inputHandler.h"
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/commonFunctionsHandler.h"
#include "../../headers/handlers/hideoutSceneStatsHandler.h"
#include "../../headers/handlers/hideoutSceneTopPanelHandler.h"
#include "../../headers/handlers/hideoutSceneInventoryHandler.h"
#include "../../headers/handlers/hideoutSceneMapHandler.h"
#include "../../headers/handlers/hideoutSceneMenuHandler.h"

static MetaData metaData;

Scene hideoutSceneInit() {
  hideoutSceneLoadTiles();
  PAL_setPalette(PAL1, mainScenesPalette.data, DMA);

  // Init player data
  metaData.playerNode = EMH_getPlayerNode();
  // Init all options data
  HSIH_dataInit(&metaData);
  HSMH_dataInit(&metaData);
  HSMEH_dataInit(&metaData);
  HSTPH_dataInit(&metaData);
  HSSH_dataInit(&metaData);
  // Draw top panel
  HSTPH_drawTopPanel(&metaData);
  return createScene("hideout", 0, SCENE_HIDEOUT);
}

void hideoutSceneLoadTiles() {
  u16 ind = TILE_USER_INDEX;

  VDP_loadTileSet(scenesBorder.tileset, ind, DMA);
  ind += scenesBorder.tileset->numTile;

  VDP_loadTileSet(scenesAlphabetUa.tileset, ind, DMA);
  ind += scenesAlphabetUa.tileset->numTile;

  VDP_loadTileSet(scenesSelectorButtons.tileset, ind, DMA);
  ind += scenesSelectorButtons.tileset->numTile;

  VDP_loadTileSet(playerAvatar.tileset, ind, DMA);
  ind += playerAvatar.tileset->numTile;
}

void hideoutSceneSelectorHandle(u16 typeFocus, u16 typeButton) {
  if (typeFocus == TOP_PANEL_FOCUS) {
    HSTPH_selectorTopPanelHandle(&metaData, typeButton);
  } else if (typeFocus == STATISTICS_FOCUS) {
    HSSH_selectorStatsHandle(&metaData, typeButton);
  } else if (typeFocus == INVENTORY_FOCUS) {
    HSIH_selectorInventoryHandle(&metaData, typeButton);
  } else if (typeFocus == MAP_FOCUS) {
    HSMH_selectorInventoryHandle(&metaData, typeButton);
  } else if (typeFocus == MENU_FOCUS) {
    HSMEH_selectorInventoryHandle(&metaData, typeButton);
  }
}

void hideoutSceneUpdate() {
  printInt(0, 0, getTick()); // print current frame from start of rom
}

void hideoutSceneInputHandler() {
  if (getJoyStates().leftButton) {
    if (metaData.currentFocus == TOP_PANEL_FOCUS) {
      hideoutSceneSelectorHandle(TOP_PANEL_FOCUS, MOVE_SELECTOR_LEFT);
    }
  }
  if (getJoyStates().rightButton) {
    if (metaData.currentFocus == TOP_PANEL_FOCUS) {
      hideoutSceneSelectorHandle(TOP_PANEL_FOCUS, MOVE_SELECTOR_RIGHT);
    }
  }
  if (getJoyStates().cButton) {
    if (metaData.currentFocus == TOP_PANEL_FOCUS) {
      hideoutSceneSelectorHandle(TOP_PANEL_FOCUS, PRESS_C_BUTTON);
    } else if (metaData.currentFocus == STATISTICS_FOCUS) {
      hideoutSceneSelectorHandle(STATISTICS_FOCUS, PRESS_C_BUTTON);
    } else if (metaData.currentFocus == INVENTORY_FOCUS) {
      hideoutSceneSelectorHandle(INVENTORY_FOCUS, PRESS_C_BUTTON);
    } else if (metaData.currentFocus == MAP_FOCUS) {
      hideoutSceneSelectorHandle(MAP_FOCUS, PRESS_C_BUTTON);
    } else if (metaData.currentFocus == MENU_FOCUS) {
      hideoutSceneSelectorHandle(MENU_FOCUS, PRESS_C_BUTTON);
    }
  }
}
