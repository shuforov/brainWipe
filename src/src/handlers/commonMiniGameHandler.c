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

u16 mgna[M_G_N_A_MAX_SIZE];
u16 mgnaCounter = 0; // how many numbers are currently in mgna array

void generateMgna(u16 min, u16 max, u16 howMany) {
  // prevent overflow
  if (howMany > M_G_N_A_MAX_SIZE) { howMany = M_G_N_A_MAX_SIZE; }
  // clear array before generating new numbers
  mgnaCounter = 0;

  for (u16 i = 0; i < howMany; i++) {
    mgna[mgnaCounter++] = (random() % (max - min + 1)) + min;
  }
}

u16 *getMgna() { return mgna; }

void printMgna() {
  for (u16 i = 0; i < mgnaCounter; i++) {
    u16 num = mgna[i];
    char numS[3];
    sprintf(numS, "%d", num);
    KLog(numS);
  }
}

u16 getMgnaCounter() {
  return mgnaCounter;
}
