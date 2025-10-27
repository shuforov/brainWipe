#include <genesis.h>
#include "headers/gameEngine.h"

int main() {
  init();
  while (1) {
    updateGameEngine();

    SYS_doVBlankProcess();
  }
  return (0);
}
