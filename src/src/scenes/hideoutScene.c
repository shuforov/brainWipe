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
#include "../../headers/handlers/hideoutSceneHintOptionHandler.h"

static MetaData metaData;

Scene hideoutSceneInit() {
  hideoutSceneLoadTiles();
  PAL_setPalette(PAL1, mainScenesPalette.data, DMA);

  // Init player data
  metaData.playerNode = EMH_getPlayerNode();
  // Set reRenderTrigger
  metaData.reRenderTrigger = false;
  // Set default focus state
  metaData.currentFocus = STATISTICS_FOCUS;
  // Init top panel data
  HSTPH_dataInit(&metaData);
  // Init hint menu of options data
  HSHOH_dataInit(&metaData);
  // Init all options data
  HSSH_dataInit(&metaData);
  /* HSIH_dataInit(&metaData) */
  /* HSMH_dataInit(&metaData); */
  /* HSMEH_dataInit(&metaData); */
  // First init render
  HS_reRenderHideout();

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
  if (typeFocus == HINT_MENU_OPTION_FOCUS) {
    HSHO_selectorStatsHandle(&metaData, typeButton);
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
  if (metaData.reRenderTrigger) {
    HS_reRenderHideout();
    metaData.reRenderTrigger = false;
  }
}

void hideoutSceneInputHandler() {
  if (getJoyStates().upButton) {
    if (metaData.currentFocus == HINT_MENU_OPTION_FOCUS) {
      hideoutSceneSelectorHandle(HINT_MENU_OPTION_FOCUS, MOVE_SELECTOR_UP);
    }
  }
  if (getJoyStates().downButton) {
    if (metaData.currentFocus == HINT_MENU_OPTION_FOCUS) {
      hideoutSceneSelectorHandle(HINT_MENU_OPTION_FOCUS, MOVE_SELECTOR_DOWN);
    }
  }
  if (getJoyStates().yButton) {
    if (metaData.currentFocus != HINT_MENU_OPTION_FOCUS) {
      hideoutSceneSelectorHandle(HINT_MENU_OPTION_FOCUS, PRESS_Y_BUTTON);
    }
  }
  if (getJoyStates().rightButton) {
    if (metaData.currentFocus == STATISTICS_FOCUS) {
      hideoutSceneSelectorHandle(STATISTICS_FOCUS, MOVE_SELECTOR_RIGHT);
    }
  }
  if (getJoyStates().leftButton) {
    if (metaData.currentFocus == STATISTICS_FOCUS) {
      hideoutSceneSelectorHandle(STATISTICS_FOCUS, MOVE_SELECTOR_LEFT);
    }
  }
  if (getJoyStates().xButton) {
    if (metaData.currentFocus == STATISTICS_FOCUS) {
      hideoutSceneSelectorHandle(STATISTICS_FOCUS, PRESS_X_BUTTON);
    }
  }
  if (getJoyStates().aButton) {
    if (metaData.currentFocus == HINT_MENU_OPTION_FOCUS) {
      hideoutSceneSelectorHandle(HINT_MENU_OPTION_FOCUS, PRESS_A_BUTTON);
    }
  }
}

void HS_reRenderHideout() {
  // Clear screen
  HS_clearScreen();
  // Render hint menu
  HSHOH_drawHintMenu(&metaData);
  // Render top panel
  HSTPH_drawTopPanel(&metaData);
  // Render currentfocus option
  if (metaData.currentFocus == STATISTICS_FOCUS) {
    HSSH_drawTopMenuOptions(&metaData);
  } else if (metaData.currentFocus == HINT_MENU_OPTION_FOCUS) {
    HSHOH_drawHintMenu(&metaData);
  }
}

void HS_clearScreen() {
  VDP_clearPlane(BG_A, TRUE);
  VDP_clearPlane(BG_B, TRUE);
  VDP_clearPlane(WINDOW, TRUE);
}
