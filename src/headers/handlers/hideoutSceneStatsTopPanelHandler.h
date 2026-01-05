#ifndef HIDEOUT_SCENE_STATS_TOP_PANEL_HANDLER_H
#define HIDEOUT_SCENE_STATS_TOP_PANEL_HANDLER_H

#include "commonHideoutStructHandler.h"

void HSSTPH_dataInit(MetaData *metaData);
void HSSTPH_drawSelector(MetaData *metaData);
void HSSTPH_drawTopMenuOptions(MetaData *metaData);
void HSSTPH_selectorMovementHandler(MetaData *metaData, u16 typeButton);

#endif
