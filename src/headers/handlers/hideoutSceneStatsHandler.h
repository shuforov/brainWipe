#ifndef HIDEOUT_SCENE_STATS_HANDLER_H
#define HIDEOUT_SCENE_STATS_HANDLER_H

#include "commonStructHandler.h"
#include "commonHideoutStructHandler.h"

void HSSH_dataInit(MetaData *metaData);
void HSSH_drawStatisticsOption(MetaData *metaData);
void HSSH_drawPlayerAvatar(Vec2 avatarPosition);
void HSSH_selectorStatsHandle(MetaData *metaData, u16 typeButton);
void HSSH_drawTopMenuOptions(MetaData *metaData);
void HSSH_reRenderSelector(MetaData *metaData);
void HSSH_drawSelector(MetaData *metaData);
void HSSH_clearFocusBox(MetaData *metaData);

#endif
