#ifndef COMMON_STRUCT_HANDLER_H
#define COMMON_STRUCT_HANDLER_H

#include <genesis.h>

typedef struct {
  u16 x;
  u16 y;
} Vec2;

typedef struct {
  u16 w;
  u16 h;
} SizeBox;

typedef struct {
  u16 topRight;
  u16 topLeft;
  u16 bottomRight;
  u16 bottomLeft;
  u16 topSide;
  u16 leftSide;
  u16 rightSide;
  u16 bottomSide;
  u16 fill;
} BorderTiles;

typedef struct {
  u16 left;
  u16 right;
  u16 up;
  u16 down;
  u16 aButton;
  u16 bButton;
  u16 cButton;
  u16 xButton;
  u16 yButton;
  u16 zButton;
  u16 dropDownIcon;
} CursorTiles;

typedef struct {
  Vec2 upPosition;
  Vec2 downPosition;
} VerticalScrollTransform;

typedef struct {
  Vec2 leftPosition;
  Vec2 rightPosition;
} HorizontalScrolTransform;

typedef struct {
  u16 nameHex[13];
} SaveData;

typedef struct {
  u16 name[26];
  u16 description[56];
  u16 nameSize;
  u16 descriptionSize;
} Skill;

typedef struct {
  u16 damage;
  u16 critChance;
  u16 durabilityLoss;
  u16 hitChance;
  u16 damageWHPH50P; // damage when HP > 50%
  u16 damageWHPL40P; // damage when HP < 40%
  u16 critsDealXD; // crits deal * X damage
  u16 damageNPEnemyHPL30P; // damage n% enemy HP < 30%
} OffensiveSkillStats;

typedef struct {
  u16 maxHP;
  u16 defense;
  u16 damageTaken;
  u16 chanceECY;     // chance enemy crits you
  u16 chanceCA;      // chance to counter attack
  u16 healNPM;       // heal N% more
  u16 damageWHPL20P; // damage when HP < 20%
  u16 defendR60D;    // defend reduces 60% damage (insted of 50%)
} DefensiveSkillStats;

typedef struct {
  u16 keyDropChance;
  u16 medkitsHeal;
  u16 chanceAF; // chance to act first
  bool rEDHBF; // reveals enemy Def & HP before fight
  u16 damageT; // throwables deal +N damage
  u16 lastSEET; // last status effects N extra turn
  u16 creditsFK; // +N% more credits from kills
  u16 storeItemsCost; // store items cost -N%
  bool freeHeal; // N free heal at 0HP (only once per battle)
  u16 dropChanceFAI; // +N% drop chance for all items
} UtilitySkillStats ;

typedef struct {
  u16 offensive[5]; // ids of offensive accepted skills
  u16 offensiveSize;
  OffensiveSkillStats offensiveSkillStats;
  DefensiveSkillStats defensiveSkillStats;
  UtilitySkillStats utilitySkillStats;
  u16 defensive[5]; // ids of defensive accepted skills
  u16 defensiveSize;
  u16 utility[5]; // ids of utility accepted skills
  u16 utilitySize;
  u16 skillPoints;
} SkillsData;

#endif
