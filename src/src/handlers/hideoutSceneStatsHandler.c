#include "../../headers/handlers/hideoutSceneStatsHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/hideoutSceneStatsDefensiveHandler.h"
#include "../../headers/handlers/hideoutSceneStatsOffensiveHandler.h"
#include "../../headers/handlers/hideoutSceneStatsStatisticsHandler.h"
#include "../../headers/handlers/hideoutSceneStatsTopPanelHandler.h"
#include "../../headers/handlers/hideoutSceneStatsUtility.h"
#include "../../headers/scenes/scene.h"
#include <genesis.h>

typedef enum {
  TMS_STATS,
  TMS_OFFENSIVE,
  TMS_DEFENSIVE,
  TMS_UTILITY
} TopMenuStates;
typedef enum { SST_LEFT, SST_RIGHT } StatsSelectorTypes;
typedef enum { OFFENSIVE, DEFENSIVE, UTILITY } SkillTypeTree;

void HSSH_dataInit(MetaData *metaData) {
  // Common statistic border position
  metaData->hintOptionData.statisticData.borderPosition = (Vec2){1, 5};
  // Common statistic border size
  metaData->hintOptionData.statisticData.borderSize = (SizeBox){38, 22};
  // Statistic focus box position
  metaData->hintOptionData.statisticData.focusBoxPosition = (Vec2){2, 7};
  // Statistic focus box size
  metaData->hintOptionData.statisticData.focusBoxSize = (SizeBox){36, 19};
  HSSSH_dataInit(metaData);
  HSSTPH_dataInit(metaData);
  HSSOH_dataInit(metaData);
  HSSDH_dataInit(metaData);
  HSSUH_dataInit(metaData);
}

void HSSH_drawStatisticsOption(MetaData *metaData) {
  HSSSH_statisticsRender(metaData);
}

void HSSH_drawTopMenuOptions(MetaData *metaData) {
  HSSTPH_drawTopMenuOptions(metaData);
}

void HSSH_reRenderSelector(MetaData *metaData) {
  HSSTPH_drawSelector(metaData);
}

void HSSH_clearFocusBox(MetaData *metaData) {
  drawFillBox(metaData->hintOptionData.statisticData.focusBoxPosition,
              metaData->hintOptionData.statisticData.focusBoxSize,
              metaData->borderTilesData.fill);
}

void HSSH_drawOffensiveOption(MetaData *metaData) {
  // Draw next skills block
  HSSH_nextSkillsRender(metaData, OFFENSIVE);
  // Draw current skill block
  HSSH_currentSkillsRender(metaData, OFFENSIVE);
}

void HSSH_drawDefensiveOption(MetaData *metaData) {
  // Draw next skills block
  HSSH_nextSkillsRender(metaData, DEFENSIVE);
  // Draw current skill block
  HSSH_currentSkillsRender(metaData, DEFENSIVE);
}

void HSSH_drawUtilityOption(MetaData *metaData) {
  // Draw next skills block
  HSSH_nextSkillsRender(metaData, UTILITY);
  // Draw current skill block
  HSSH_currentSkillsRender(metaData, UTILITY);
}

void HSSH_nextSkillsRender(MetaData *metaData, u16 skillTypeTree) {
  bool skillSelectorRender = false;
  if (skillTypeTree == OFFENSIVE) {
    HSSOH_nextSkillsRender(metaData);
    // Set Selector of next skill rendering state
    if (HSSH_skillPointsAvailable(metaData) &&
        metaData->hintOptionData.statisticData.offensiveData.currentSkills
                .skillsSize < 5) {
      skillSelectorRender = true;
    }

  } else if (skillTypeTree == DEFENSIVE) {
    HSSDH_nextSkillsRender(metaData);
    // Set Selector of next skill rendering state
    if (HSSH_skillPointsAvailable(metaData) &&
        metaData->hintOptionData.statisticData.defensiveData.currentSkills
                .skillsSize < 5) {
      skillSelectorRender = true;
    }
  } else if (skillTypeTree == UTILITY) {
    HSSUH_nextSkillsRender(metaData);
    // Set Selector of next skill rendering state
    if (HSSH_skillPointsAvailable(metaData) &&
        metaData->hintOptionData.statisticData.utilityData.currentSkills
                .skillsSize < 5) {
      skillSelectorRender = true;
    }
  }
  if (skillSelectorRender) {
    HSSH_skillSelectorRender(metaData, SST_LEFT);
  }
  // Skill points
  drawTextTilesWHLimits(
      metaData->hintOptionData.statisticData.skillPointsData.positionTiles,
      metaData->hintOptionData.statisticData.skillPointsData.textTiles,
      ARRAY_LEN(
          metaData->hintOptionData.statisticData.skillPointsData.textTiles),
      (Vec2){22, 11});
  drawTile(metaData->hintOptionData.statisticData.skillPointsData.positionValue,
           NUMBERS_HEX[metaData->hintOptionData.statisticData.skillPointsData
                           .value]);
}

void HSSH_skillSelectorRender(MetaData *metaData, u16 selectorType) {
  // Clear selectors
  drawTile(
      metaData->hintOptionData.statisticData.selectorData.leftSelectorPosition,
      metaData->borderTilesData.fill);
  drawTile(
      metaData->hintOptionData.statisticData.selectorData.rightSelectorPosition,
      metaData->borderTilesData.fill);
  drawTile(
      metaData->hintOptionData.statisticData.selectorData.hintSelectorPosition,
      metaData->borderTilesData.fill);
  // Draw selector and hint button
  if (selectorType == SST_LEFT || selectorType == SST_RIGHT) {
    if (selectorType == SST_LEFT) {
      drawTile(
          metaData->hintOptionData.statisticData.selectorData
              .leftSelectorPosition,
          metaData->hintOptionData.statisticData.selectorData.leftSelectorTile);
      metaData->hintOptionData.statisticData.selectorData.index = 0;
    } else if (selectorType == SST_RIGHT) {
      drawTile(metaData->hintOptionData.statisticData.selectorData
                   .rightSelectorPosition,
               metaData->hintOptionData.statisticData.selectorData
                   .rightSelectorTile);
      metaData->hintOptionData.statisticData.selectorData.index = 1;
    }
    drawTile(
        metaData->hintOptionData.statisticData.selectorData
            .hintSelectorPosition,
        metaData->hintOptionData.statisticData.selectorData.hintSelectorTile);
  }
}

bool HSSH_skillPointsAvailable(MetaData *metaData) {
  if (metaData->hintOptionData.statisticData.skillPointsData.value > 0) {
    return true;
  }
  return false;
}

void HSSH_skillConfirmHandler(MetaData *metaData, u16 skillTypeTree,
                              u16 skillId) {
  // skillTypeTree -> Offensive Defensive Utility types
  // decrement of skill points
  metaData->hintOptionData.statisticData.skillPointsData.value--;
  metaData->playerNode->skillsData.skillPoints--;
  // push skillid to currentSkills array by skill type
  // update next skill ids
  if (skillTypeTree == OFFENSIVE) {
    HSSOH_acceptSkillHandelr(metaData, skillId);
    HSSH_nextSkillsRender(metaData, OFFENSIVE);
  } else if (skillTypeTree == DEFENSIVE) {
    HSSDH_acceptSkillHandelr(metaData, skillId);
    HSSH_nextSkillsRender(metaData, DEFENSIVE);
  } else if (skillTypeTree == UTILITY) {
    HSSUH_acceptSkillHandelr(metaData, skillId);
    HSSH_nextSkillsRender(metaData, UTILITY);
  }
}

void HSSH_currentSkillsRender(MetaData *metaData, u16 skillTreeType) {
  if (skillTreeType == OFFENSIVE) {
    HSSOH_currentSkillsRender(metaData);
  } else if (skillTreeType == DEFENSIVE) {
    HSSDH_currentSkillsRender(metaData);
  } else if (skillTreeType == UTILITY) {
    HSSUH_currentSkillsRender(metaData);
  }
}

void HSSH_selectorStatsHandle(MetaData *metaData, u16 typeButton) {
  if (typeButton == PRESS_Y_BUTTON) {
    metaData->currentFocus = HINT_MENU_OPTION_FOCUS;
    metaData->reRenderTrigger = true;
    metaData->hintOptionData.statisticData.topMenuData.currentFocus =
        STATISTICS_STATS_FOCUS;
  } else if (typeButton == MOVE_SELECTOR_RIGHT) {
    if (metaData->hintOptionData.statisticData.topMenuData.currentFocus ==
        STATISTICS_TOP_MENU_FOCUS) {
      HSSTPH_selectorMovementHandler(metaData, typeButton);
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_OFFENSIVE_FOCUS) {
      if (HSSH_skillPointsAvailable(metaData) &&
          metaData->hintOptionData.statisticData.offensiveData.currentSkills
                  .skillsSize < 5) {
        HSSH_skillSelectorRender(metaData, SST_RIGHT);
      }
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_DEFENSIVE_FOCUS) {
      if (HSSH_skillPointsAvailable(metaData) &&
          metaData->hintOptionData.statisticData.defensiveData.currentSkills
                  .skillsSize < 5) {
        HSSH_skillSelectorRender(metaData, SST_RIGHT);
      }
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_UTILITY_FOCUS) {
      if (HSSH_skillPointsAvailable(metaData) &&
          metaData->hintOptionData.statisticData.utilityData.currentSkills
                  .skillsSize < 5) {
        HSSH_skillSelectorRender(metaData, SST_RIGHT);
      }
    }
  } else if (typeButton == MOVE_SELECTOR_LEFT) {
    if (metaData->hintOptionData.statisticData.topMenuData.currentFocus ==
        STATISTICS_TOP_MENU_FOCUS) {
      HSSTPH_selectorMovementHandler(metaData, typeButton);
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_OFFENSIVE_FOCUS) {
      if (HSSH_skillPointsAvailable(metaData) &&
          metaData->hintOptionData.statisticData.offensiveData.currentSkills
                  .skillsSize < 5) {
        HSSH_skillSelectorRender(metaData, SST_LEFT);
      }
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_DEFENSIVE_FOCUS) {
      if (HSSH_skillPointsAvailable(metaData) &&
          metaData->hintOptionData.statisticData.defensiveData.currentSkills
                  .skillsSize < 5) {
        HSSH_skillSelectorRender(metaData, SST_LEFT);
      }
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_UTILITY_FOCUS) {
      if (HSSH_skillPointsAvailable(metaData) &&
          metaData->hintOptionData.statisticData.utilityData.currentSkills
                  .skillsSize < 5) {
        HSSH_skillSelectorRender(metaData, SST_LEFT);
      }
    }
  } else if (typeButton == PRESS_X_BUTTON) {
    if (metaData->hintOptionData.statisticData.topMenuData.currentFocus ==
        STATISTICS_TOP_MENU_FOCUS) {
      if (metaData->hintOptionData.statisticData.topMenuData.selectorData
              .selectorIndex == TMS_STATS) {
        HSSH_drawStatisticsOption(metaData);
        metaData->hintOptionData.statisticData.topMenuData.currentFocus =
            STATISTICS_STATS_FOCUS;
      } else if (metaData->hintOptionData.statisticData.topMenuData.selectorData
                     .selectorIndex == TMS_OFFENSIVE) {
        HSSH_drawOffensiveOption(metaData);
        metaData->hintOptionData.statisticData.topMenuData.currentFocus =
            STATISTICS_OFFENSIVE_FOCUS;
      } else if (metaData->hintOptionData.statisticData.topMenuData.selectorData
                     .selectorIndex == TMS_DEFENSIVE) {
        HSSH_drawDefensiveOption(metaData);
        metaData->hintOptionData.statisticData.topMenuData.currentFocus =
            STATISTICS_DEFENSIVE_FOCUS;
      } else if (metaData->hintOptionData.statisticData.topMenuData.selectorData
                     .selectorIndex == TMS_UTILITY) {
        HSSH_drawUtilityOption(metaData);
        metaData->hintOptionData.statisticData.topMenuData.currentFocus =
            STATISTICS_UTILITY_FOCUS;
      }
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_STATS_FOCUS) {
      HSSH_clearFocusBox(metaData);
      metaData->hintOptionData.statisticData.topMenuData.currentFocus =
          STATISTICS_TOP_MENU_FOCUS;
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_OFFENSIVE_FOCUS) {
      HSSH_clearFocusBox(metaData);
      metaData->hintOptionData.statisticData.topMenuData.currentFocus =
          STATISTICS_TOP_MENU_FOCUS;
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_DEFENSIVE_FOCUS) {
      HSSH_clearFocusBox(metaData);
      metaData->hintOptionData.statisticData.topMenuData.currentFocus =
          STATISTICS_TOP_MENU_FOCUS;
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_UTILITY_FOCUS) {
      HSSH_clearFocusBox(metaData);
      metaData->hintOptionData.statisticData.topMenuData.currentFocus =
          STATISTICS_TOP_MENU_FOCUS;
    }
  } else if (typeButton == PRESS_A_BUTTON) {
    if (metaData->hintOptionData.statisticData.topMenuData.currentFocus ==
        STATISTICS_OFFENSIVE_FOCUS) {
      if (HSSH_skillPointsAvailable(metaData) &&
          metaData->hintOptionData.statisticData.offensiveData.currentSkills
                  .skillsSize < 5) {
        // Accept selected skill
        u16 skillId =
            metaData->hintOptionData.statisticData.offensiveData.nextSkills
                .skills[metaData->hintOptionData.statisticData.selectorData
                            .index];
        HSSH_skillConfirmHandler(metaData, OFFENSIVE, skillId);
        HSSH_currentSkillsRender(metaData, OFFENSIVE);
      }
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_DEFENSIVE_FOCUS) {
      if (HSSH_skillPointsAvailable(metaData) &&
          metaData->hintOptionData.statisticData.defensiveData.currentSkills
                  .skillsSize < 5) {
        // Accept selected skill
        u16 skillId =
            metaData->hintOptionData.statisticData.defensiveData.nextSkills
                .skills[metaData->hintOptionData.statisticData.selectorData
                            .index];
        HSSH_skillConfirmHandler(metaData, DEFENSIVE, skillId);
        HSSH_currentSkillsRender(metaData, DEFENSIVE);
      }
    } else if (metaData->hintOptionData.statisticData.topMenuData
                   .currentFocus == STATISTICS_UTILITY_FOCUS) {
      if (HSSH_skillPointsAvailable(metaData) &&
          metaData->hintOptionData.statisticData.utilityData.currentSkills
                  .skillsSize < 5) {
        // Accept selected skill
        u16 skillId =
            metaData->hintOptionData.statisticData.utilityData.nextSkills.skills
                [metaData->hintOptionData.statisticData.selectorData.index];
        HSSH_skillConfirmHandler(metaData, UTILITY, skillId);
        HSSH_currentSkillsRender(metaData, UTILITY);
      }
    }
  }
}
