#ifndef HIDEOUT_SCENE_STATS_UTILITY_HANDLER_H
#define HIDEOUT_SCENE_STATS_UTILITY_HANDLER_H

#include "commonHideoutStructHandler.h"

void HSSUH_dataInit(MetaData *metaData);
void HSSUH_nextSkillsRender(MetaData *metaData);
void HSSUH_acceptSkillHandelr(MetaData *metaData, u16 skillId);
void HSSUH_currentSkillsRender(MetaData *metaData);
void HSSUH_setSkillStatsHandler(MetaData *metaData, u16 skillId);

#endif
