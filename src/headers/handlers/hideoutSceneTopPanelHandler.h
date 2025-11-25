#ifndef HIDEOUT_SCENE_TOP_PANEL_HANDLER_H
#define HIDEOUT_SCENE_TOP_PANEL_HANDLER_H

#include "commonStructHandler.h"
#include "commonHideoutStructHandler.h"

void HSTPH_drawTopPanelCursor(MetaData *metaData);
void HSTPH_dataInit(MetaData *metaData);
void HSTPH_drawTopPanel(MetaData *metaData);
void HSTPH_selectorTopPanelHandle(MetaData *metaData, u16 typeButton);

#endif
