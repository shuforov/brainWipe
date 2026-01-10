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
  playerNode->stats.healthPoint = 30;
  playerNode->stats.attak = 3;
  playerNode->stats.defense = 0;
  playerNode->stats.crit = 2;
  playerNode->stats.evasion = 2;
  playerNode->skillsData.skillPoints = 6;
  playerNode->skillsData.offensiveSize = 0;
  playerNode->skillsData.defensiveSize = 0;
  playerNode->skillsData.utilitySize = 0;
  playerNode->levelData.level = 1;
  playerNode->levelData.currentExperience = 0;
  playerNode->levelData.experienceNeededNext = 100;
  playerNode->creditValue = 111;
}

Player *EMH_getPlayerNode() { return playerNode; }
