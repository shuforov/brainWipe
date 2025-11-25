#include "../../headers/handlers/hideoutSceneCommonFunctions.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include <genesis.h>

void HSCF_clearOptionSpace(MetaData *metaData) {
  drawFillBox(metaData->optionSpacePosition, metaData->optionSpaceSize, 0x00);
}
