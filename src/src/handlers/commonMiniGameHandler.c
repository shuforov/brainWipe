#include <genesis.h>
#include "../../headers/handlers/commonMiniGameHandler.h"

struct buttonMetadata buttonsInPopUp[] = {
    {11, 9, 0},  // count down timer
    {13, 9, 0},  // end status of minigame
    {15, 9, 11}, // rounds count of minigames
    {11, 11, 4}, // X button
    {13, 11, 5}, // Y button
    {15, 11, 6}, // Z button
    {11, 13, 1}, // A button
    {13, 13, 2}, // B buutton
    {15, 13, 3}, // C button
};

struct buttonMetadata* getButtonsInPopUp() {
  return buttonsInPopUp;
}
