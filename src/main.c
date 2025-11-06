#include <genesis.h>
#include "headers/gameEngine.h"

int main() {
  gameEngineInit();
  while (1) {
    gameEngineUpdate();

    SYS_doVBlankProcess();
  }
  return (0);
}
