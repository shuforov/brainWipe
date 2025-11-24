#include <genesis.h>
#include "../../headers/handlers/entityManagerHandler.h"

u16 enemyCount = 0;
u16 citiesCount = 0;
static Player playerInstance;
Player *playerNode;
Enemy enemies[224];
City Cities[10];

static const u16 BASIC_PLAYER_NAME[3] = {0x41, 0x3A, 0x1A};

void EMH_createNewPlayer() {
  playerNode = &playerInstance;
  memcpy(playerNode->name, BASIC_PLAYER_NAME, sizeof(BASIC_PLAYER_NAME));
  playerNode->stats.health = 100;
}

Player *EMH_getPlayerNode() { return playerNode; }
