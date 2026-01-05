#ifndef HIDEOUT_SCENE_STATS_HANDLER_H
#define HIDEOUT_SCENE_STATS_HANDLER_H

#include "commonHideoutStructHandler.h"

void HSSH_dataInit(MetaData *metaData);
void HSSH_drawStatisticsOption(MetaData *metaData);
void HSSH_selectorStatsHandle(MetaData *metaData, u16 typeButton);
void HSSH_drawTopMenuOptions(MetaData *metaData);
void HSSH_reRenderSelector(MetaData *metaData);
void HSSH_clearFocusBox(MetaData *metaData);
void HSSH_drawOffensiveOption(MetaData *metaData);
bool HSSH_skillPointsAvailable(MetaData *metaData);
void HSSH_skillSelectorRender(MetaData *metaData, u16 selectorType);
void HSSH_skillConfirmHandler(MetaData *metaData, u16 skillTypeTree,
                              u16 skillId);
void HSSH_currentSkillsRender(MetaData *metaData, u16 skillTreeType);
void HSSH_nextSkillsRender(MetaData *metaData, u16 skillTreeType);

#endif
