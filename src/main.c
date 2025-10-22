#include <genesis.h>
#include "gameEngine.h"

int main() {
  init();
  while (1) {
    update();

    SYS_doVBlankProcess();
  }
  return(0);  
}  
