#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <genesis.h>

void init();
void loadTiles();
void update();
void myJoyHandler(u16 joy, u16 changed, u16 state);

#endif // GAME_ENGINE_H
