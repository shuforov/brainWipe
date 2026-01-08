#ifndef HIDEOUT_SCENE_STATS_DEFENSIVE_HANDLER_H
#define HIDEOUT_SCENE_STATS_DEFENSIVE_HANDLER_H

#include "commonHideoutStructHandler.h"

void HSSDH_dataInit(MetaData *metaData);
void HSSDH_nextSkillsRender(MetaData *metaData);
void HSSDH_currentSkillsRender(MetaData *metaData);
void HSSDH_acceptSkillHandelr(MetaData *metaData, u16 skillId);
void HSSDH_setSkillStatsHandler(MetaData *metaData, u16 skillId);

#endif
