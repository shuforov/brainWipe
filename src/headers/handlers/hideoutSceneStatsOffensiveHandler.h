#ifndef HIDEOUT_SCENE_STATS_OFFENSIVE_HANDLER_H
#define HIDEOUT_SCENE_STATS_OFFENSIVE_HANDLER_H

#include "commonHideoutStructHandler.h"

void HSSOH_dataInit(MetaData *metaData);
void HSSOH_nextSkillsRender(MetaData *metaData);
void HSSOH_acceptSkillHandelr(MetaData *metaData, u16 skillId);
void HSSOH_currentSkillsRender(MetaData *metaData);

#endif
