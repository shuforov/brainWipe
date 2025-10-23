#include <genesis.h>
#include "../../headers/handlers/debugHandler.h"

void printInt(u16 x, u16 y, u16 printNumber) {
  char currentFrameChar[6];

  sprintf(currentFrameChar, "%d", printNumber);
  VDP_clearTextArea(x, y, 5, 1);
  VDP_drawText(currentFrameChar, x, y);
}
