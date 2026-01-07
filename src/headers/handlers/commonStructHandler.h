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
  u16 offensive[5]; // ids of offensive accepted skills
  u16 offensiveSize;
  OffensiveSkillStats offensiveSkillStats;
  u16 defensive[5]; // ids of defensive accepted skills
  u16 defensiveSize;
  u16 utility[5]; // ids of utility accepted skills
  u16 utilitySize;
  u16 skillPoints;
} SkillsData;

#endif
