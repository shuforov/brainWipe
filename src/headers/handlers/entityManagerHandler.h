#ifndef ENTITY_MANAGER_HANDLER_H
#define ENTITY_MANAGER_HANDLER_H

#include <genesis.h>
#include "../commonConstants.h"

typedef enum {
  SMALL_BATTERY
} HealingItemTypes;

typedef struct {
  u16 health;
} CharacterStats;

typedef struct {
  char name[32];
  u16 damage;
} Weapon;

typedef struct {
  char name[32];
  u16 heal; // how many health restore per use
  u16 count;
  HealingItemTypes type;
} HealingItem;

typedef struct {
  Weapon weapons[5];
  u16 weaponCount;
  HealingItem healingItems[5];
  u16 healingItemCount;
} BackPack;

typedef struct {
  u16 name[20];
  Weapon weapon; // currect geared weapon
  BackPack backPack;
  CharacterStats stats;
  SkillsData skillsData;
} Player;

typedef struct {
  char name[32];
  Weapon weapon; // currect geared weapon
  CharacterStats stats;
} Enemy;

typedef struct {
  char name[10];
  u16 enemyCount;
  bool isOpen;
} BuildingLevel;

typedef struct {
  char name[10];
  BuildingLevel levels;
  bool isOpen;
} Building;

typedef struct {
  char name[10];
  Building buildings;
  bool isOpen;
} City;

void EMH_createNewPlayer();
Player *EMH_getPlayerNode();

#endif
