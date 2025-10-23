#ifndef COMMON_MINI_GAME_HANDLER_H
#define COMMON_MINI_GAME_HANDLER_H

#include <genesis.h>

struct buttonMetadata {
  u16 x;
  u16 y;
  u16 idTag;
};

struct buttonMetadata* getButtonsInPopUp();

#endif
