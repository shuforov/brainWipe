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
  u16 name[21];
  u16 description[48];
  u16 nameSize;
  u16 descriptionSize;
  u16 value;
  u16 valueAdditional;
} Skill;

typedef struct {
  Skill offensive[5];
  u16 offensiveSize;
  Skill defensive[5];
  u16 defensiveSize;
  Skill utility[5];
  u16 utilitySize;
  u16 skillPoints;
} SkillsData;

#endif
