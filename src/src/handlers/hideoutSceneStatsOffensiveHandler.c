#include "../../headers/handlers/hideoutSceneStatsOffensiveHandler.h"
#include "../../headers/handlers/commonStructHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/scenes/hideoutConstants.h"
#include "../../headers/scenes/scene.h"
#include <genesis.h>

typedef enum {
  POWER_STRIKES,
  PRECISION_TRAINING,
  DURABILITY_EXPERT,
  SHARP_INSTINCTS,
  COMBO_BOOST,
  BLOODY_EDGE,
  CRITICAL_SURGE,
  DUAL_FOCUS,
  OVERPOWER,
  EXECUTIONER
} HSSOHSkillTypes;

static const Skill HSSOH_OFFENSIVE_DATA[10] = {
    // Power strikes +10% damage
    (Skill){{0x3B, 0x3F, 0x48, 0x49, 0x2B, 0x3E, 0x32, 0x35, 0x16, 0x49, 0x2A,
             0x1E, 0x46},
            {0x6E, 0x60, 0x5F, 0x70, 0x16, 0x2A, 0x3F, 0x16, 0x53, 0x36, 0x3F,
             0x2A, 0x32},
            13,
            13},
    // Precision Training +5% crit chance
    (Skill){{
                0x43, 0x46, 0x28, 0x3E, 0x49, 0x20, 0x1E, 0x3E, 0x3E, 0x5C,
                0x16, 0x48, 0x3F, 0x52, 0x3E, 0x3F, 0x47, 0x48, 0x33,
            },
            {0x6E, 0x64, 0x70, 0x16, 0x53, 0x1E, 0x3E, 0x47, 0x16,
             0x36, 0x46, 0x32, 0x48, 0x32, 0x52, 0x3E, 0x3F, 0x21,
             0x3F, 0x16, 0x49, 0x2A, 0x1E, 0x46, 0x49},
            19,
            25},
    // Durability Expert -20% durability loss
    (Skill){{0x24, 0x36, 0x47, 0x40, 0x28, 0x46, 0x48, 0x16, 0x3D, 0x33, 0x51,
             0x3E, 0x3F, 0x47, 0x48, 0x33},
            {0x6F, 0x61, 0x5F, 0x70, 0x16, 0x20, 0x48, 0x46, 0x1E, 0x48,
             0x32, 0x16, 0x3D, 0x33, 0x51, 0x3E, 0x3F, 0x47, 0x48, 0x33},
            16,
            20},
    // Sharp Instincts +10% hit chance
    (Skill){{0x1C, 0x3F, 0x47, 0x48, 0x46, 0x33, 0x16, 0x33, 0x3E, 0x47, 0x48,
             0x32, 0x3E, 0x36, 0x48, 0x32},
            {0x6E, 0x60, 0x5F, 0x70, 0x16, 0x53, 0x1E, 0x3E, 0x47, 0x16, 0x20,
             0x3C, 0x49, 0x52, 0x1E, 0x3E, 0x3E, 0x5C},
            16,
            18},
    // Combo boost +2 damage when HP > 50%
    (Skill){{0x31, 0x3F, 0x3D, 0x1F, 0x3F, 0x6F, 0x1F, 0x3F, 0x3E, 0x49, 0x47},
            {0x6E, 0x61, 0x16, 0x2A, 0x3F, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x32,
             0x6D, 0x16, 0x36, 0x3F, 0x3C, 0x32, 0x16, 0x27, 0x23, 0x41, 0x16,
             0x1F, 0x33, 0x3C, 0x5A, 0x53, 0x28, 0x16, 0x64, 0x5F, 0x70},
            11,
            32},
    // Bloody Edge +4 damage when HP < 40%
    (Skill){{0x31, 0x46, 0x32, 0x20, 0x1E, 0x20, 0x32, 0x35, 0x16, 0x36, 0x46,
             0x1E, 0x35},
            {0x6E, 0x63, 0x16, 0x2A, 0x3F, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x32,
             0x6D, 0x16, 0x36, 0x3F, 0x3C, 0x32, 0x16, 0x27, 0x23, 0x41, 0x16,
             0x3D, 0x28, 0x3E, 0x53, 0x28, 0x16, 0x63, 0x5F, 0x70},
            13,
            31},
    // Critical Surge crits deal * 2 damage
    (Skill){{0x31, 0x46, 0x32, 0x48, 0x32, 0x52, 0x3E, 0x32, 0x35, 0x16, 0x47,
             0x40, 0x3C, 0x28, 0x47, 0x36},
            {0x36, 0x46, 0x32, 0x48, 0x32, 0x52, 0x3E, 0x33, 0x16,
             0x49, 0x2A, 0x1E, 0x46, 0x32, 0x16, 0x2C, 0x1E, 0x20,
             0x2A, 0x1E, 0x5B, 0x48, 0x5A, 0x16, 0x49, 0x16, 0x61,
             0x16, 0x46, 0x1E, 0x2C, 0x32, 0x16, 0x1F, 0x33, 0x3C,
             0x5A, 0x53, 0x28, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x32},
            16,
            45},
    // Dual focus +5% crit and +5% hit
    (Skill){{0x3B, 0x3F, 0x2A, 0x20, 0x33, 0x35, 0x3E, 0x1E, 0x16, 0x36, 0x3F,
             0x3E, 0x51, 0x28, 0x3E, 0x48, 0x46, 0x1E, 0x51, 0x33, 0x5C},
            {0x6E, 0x64, 0x70, 0x16, 0x53, 0x1E, 0x3E, 0x47, 0x16, 0x36,
             0x46, 0x32, 0x48, 0x32, 0x52, 0x3E, 0x3F, 0x21, 0x3F, 0x16,
             0x49, 0x2A, 0x1E, 0x46, 0x49, 0x16, 0x48, 0x1E, 0x16, 0x6E,
             0x64, 0x70, 0x16, 0x53, 0x1E, 0x3E, 0x47, 0x16, 0x20, 0x3C,
             0x49, 0x52, 0x1E, 0x3E, 0x3E, 0x5C},
            21,
            46},
    // Overpower +10 flat damage
    (Skill){{0x3B, 0x28, 0x46, 0x28, 0x20, 0x28, 0x46, 0x53, 0x28, 0x3E, 0x3E,
             0x5C},
            {0x6E, 0x60, 0x5F, 0x16, 0x4A, 0x33, 0x36, 0x47, 0x3F, 0x20,
             0x1E, 0x3E, 0x3F, 0x34, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x32},
            12,
            20},
    // Executioner +20% damage vs enemies below 30% HP
    (Skill){{0x31, 0x1E, 0x48},
            {0x61, 0x5F, 0x70, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x32, 0x16,
             0x40, 0x3F, 0x16, 0x20, 0x3F, 0x46, 0x3F, 0x21, 0x1E, 0x50,
             0x16, 0x2C, 0x16, 0x3D, 0x28, 0x3E, 0x53, 0x28, 0x16, 0x3E,
             0x33, 0x2B, 0x16, 0x62, 0x5F, 0x70, 0x16, 0x27, 0x23, 0x41},
            3,
            40}};

static const u16 HSSOH_POWER_STRIKES = {10};
static const u16 HSSOH_PRECISION_TRAINING = {5};
static const u16 HSSOH_DURABILITY_EXPERT = {20};
static const u16 HSSOH_SHARP_INSTINCTS = {10};
static const u16 HSSOH_COMBO_BOOST = {2};
static const u16 HSSOH_BLOODY_EDGE = {4};
static const u16 HSSOH_CRITICAL_SURGE = {2};
static const u16 HSSOH_DUAL_FOCUS[2] = {5, 5};
static const u16 HSSOH_OVERPOWER = {10};
static const u16 HSSOH_EXECUTIONER = {20};

void HSSOH_dataInit(MetaData *metaData) {
  // Current skills init data
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .borderPosition = (Vec2){2, 17};
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .borderSize = (SizeBox){36, 9};
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .skillsSize = &metaData->playerNode->skillsData.offensiveSize;
  metaData->hintOptionData.statisticData.offensiveData.currentSkills.skills =
      &metaData->playerNode->skillsData.offensive;
  memcpy(metaData->hintOptionData.statisticData.offensiveData.currentSkills
             .titleTiles,
         CURRENT_SKILL_TITLE_NAME, sizeof(CURRENT_SKILL_TITLE_NAME));
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .titleTilesPosition = (Vec2){10, 18};
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .firstSkillPosition = (Vec2){3, 19};
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .focusBoxPosition = (Vec2){3, 19};
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .focusBoxSize = (SizeBox){34, 6};
  // Skill selector init data
  metaData->hintOptionData.statisticData.selectorData.leftSelectorPosition =
      (Vec2){17, 12};
  metaData->hintOptionData.statisticData.selectorData.hintSelectorPosition =
      (Vec2){18, 12};
  metaData->hintOptionData.statisticData.selectorData.rightSelectorPosition =
      (Vec2){19, 12};
  metaData->hintOptionData.statisticData.selectorData.hintSelectorTile =
      A_SELECTOR_BUTTON;
  metaData->hintOptionData.statisticData.selectorData.leftSelectorTile =
      LEFT_CURSOR;
  metaData->hintOptionData.statisticData.selectorData.rightSelectorTile =
      RIGHT_CURSOR;
  metaData->hintOptionData.statisticData.selectorData.index = 0;
  // Skill init data
  metaData->hintOptionData.statisticData.offensiveData.nextSkills
      .borderPosition = (Vec2){2, 7};
  metaData->hintOptionData.statisticData.offensiveData.nextSkills.borderSize =
      (SizeBox){36, 10};
  metaData->hintOptionData.statisticData.offensiveData.nextSkills.skills[0] = 0;
  metaData->hintOptionData.statisticData.offensiveData.nextSkills.skills[1] = 1;
  metaData->hintOptionData.statisticData.offensiveData.nextSkills.rightSkill
      .namePosition = (Vec2){25, 8};
  metaData->hintOptionData.statisticData.offensiveData.nextSkills.rightSkill
      .descriptionPosition = (Vec2){25, 10};
  metaData->hintOptionData.statisticData.offensiveData.nextSkills.leftSkill
      .namePosition = (Vec2){3, 8};
  metaData->hintOptionData.statisticData.offensiveData.nextSkills.leftSkill
      .descriptionPosition = (Vec2){3, 10};
  // Skill points init
  memcpy(metaData->hintOptionData.statisticData.skillPointsData.textTiles,
         SKILL_POINTS_TEXT, sizeof(SKILL_POINTS_TEXT));
  metaData->hintOptionData.statisticData.skillPointsData.positionTiles =
      (Vec2){14, 8};
  metaData->hintOptionData.statisticData.skillPointsData.positionValue =
      (Vec2){18, 10};
  metaData->hintOptionData.statisticData.skillPointsData.value =
      metaData->playerNode->skillsData.skillPoints;
}

void HSSOH_nextSkillsRender(MetaData *metaData) {
  // Clear border
  Vec2 startClearPosition =
      (Vec2){metaData->hintOptionData.statisticData.offensiveData.nextSkills
                     .borderPosition.x +
                 1,
             metaData->hintOptionData.statisticData.offensiveData.nextSkills
                     .borderPosition.y +
                 1};
  SizeBox boxClear = (SizeBox){metaData->hintOptionData.statisticData
                                       .offensiveData.nextSkills.borderSize.w -
                                   1,
                               metaData->hintOptionData.statisticData
                                       .offensiveData.nextSkills.borderSize.h -
                                   1};
  drawFillBox(startClearPosition, boxClear, metaData->borderTilesData.fill);

  // Draw next skill border
  drawBorder(metaData->hintOptionData.statisticData.offensiveData.nextSkills
                 .borderPosition,
             metaData->hintOptionData.statisticData.offensiveData.nextSkills
                 .borderSize,
             metaData->borderTilesData);
  if (*metaData->hintOptionData.statisticData.offensiveData.currentSkills
           .skillsSize < 5) {
    // Draw next skill data
    Skill leftOffensiveData =
        HSSOH_OFFENSIVE_DATA[metaData->hintOptionData.statisticData
                                 .offensiveData.nextSkills.skills[0]];
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.offensiveData
                              .nextSkills.leftSkill.namePosition,
                          leftOffensiveData.name, leftOffensiveData.nameSize,
                          (Vec2){11, 9});

    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.offensiveData
                              .nextSkills.leftSkill.descriptionPosition,
                          leftOffensiveData.description,
                          leftOffensiveData.descriptionSize, (Vec2){11, 16});
    Skill rightOffensiveData =
        HSSOH_OFFENSIVE_DATA[metaData->hintOptionData.statisticData
                                 .offensiveData.nextSkills.skills[1]];
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.offensiveData
                              .nextSkills.rightSkill.namePosition,
                          rightOffensiveData.name, rightOffensiveData.nameSize,
                          (Vec2){36, 9});
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.offensiveData
                              .nextSkills.rightSkill.descriptionPosition,
                          rightOffensiveData.description,
                          rightOffensiveData.descriptionSize, (Vec2){36, 16});
  }
}

void HSSOH_acceptSkillHandelr(MetaData *metaData, u16 skillId) {
  (*metaData->hintOptionData.statisticData.offensiveData.currentSkills
        .skills)[(*metaData->hintOptionData.statisticData.offensiveData
                       .currentSkills.skillsSize)] = skillId;
  (*metaData->hintOptionData.statisticData.offensiveData.currentSkills
        .skillsSize)++;
  HSSOH_setSkillStatsHandler(metaData, skillId);
  u16 secondSkillId =
      metaData->hintOptionData.statisticData.offensiveData.nextSkills.skills[1];
  if (secondSkillId < 9) {
    metaData->hintOptionData.statisticData.offensiveData.nextSkills.skills[0] =
        secondSkillId + 1;
    metaData->hintOptionData.statisticData.offensiveData.nextSkills.skills[1] =
        secondSkillId + 2;
  }
}

void HSSOH_currentSkillsRender(MetaData *metaData) {
  // Clear current skill box
  drawFillBox(metaData->hintOptionData.statisticData.offensiveData.currentSkills
                  .focusBoxPosition,
              metaData->hintOptionData.statisticData.offensiveData.currentSkills
                  .focusBoxSize,
              metaData->borderTilesData.fill);
  // Draw border
  drawBorder(metaData->hintOptionData.statisticData.offensiveData.currentSkills
                 .borderPosition,
             metaData->hintOptionData.statisticData.offensiveData.currentSkills
                 .borderSize,
             metaData->borderTilesData);
  drawTextTiles(metaData->hintOptionData.statisticData.offensiveData
                    .currentSkills.titleTilesPosition,
                metaData->hintOptionData.statisticData.offensiveData
                    .currentSkills.titleTiles,
                ARRAY_LEN(metaData->hintOptionData.statisticData.offensiveData
                              .currentSkills.titleTiles));
  // render each available skill
  for (u16 i = 0; i < *metaData->hintOptionData.statisticData.offensiveData
                           .currentSkills.skillsSize;
       i++) {
    Skill skillMetaData =
        HSSOH_OFFENSIVE_DATA[(*metaData->hintOptionData.statisticData
                                   .offensiveData.currentSkills.skills)[i]];
    Vec2 namePosition =
        (Vec2){metaData->hintOptionData.statisticData.offensiveData
                   .currentSkills.firstSkillPosition.x,
               metaData->hintOptionData.statisticData.offensiveData
                       .currentSkills.firstSkillPosition.y +
                   i};
    Vec2 descriptionPosition =
        (Vec2){metaData->hintOptionData.statisticData.offensiveData
                       .currentSkills.firstSkillPosition.x +
                   skillMetaData.nameSize + 1,
               metaData->hintOptionData.statisticData.offensiveData
                       .currentSkills.firstSkillPosition.y +
                   i};
    Vec2 descriptionLimitPosition = (Vec2){36, descriptionPosition.y};

    drawTextTiles(namePosition, skillMetaData.name, skillMetaData.nameSize);
    drawTextTilesWHLimits(descriptionPosition, skillMetaData.description,
                          skillMetaData.descriptionSize,
                          descriptionLimitPosition);
  }
}

void HSSOH_setSkillStatsHandler(MetaData *metaData, u16 skillId) {
  if (skillId == POWER_STRIKES) {
    metaData->playerNode->skillsData.offensiveSkillStats.damage +=
        HSSOH_POWER_STRIKES;
  } else if (skillId == PRECISION_TRAINING) {
    metaData->playerNode->skillsData.offensiveSkillStats.critChance +=
        HSSOH_PRECISION_TRAINING;
  } else if (skillId == DURABILITY_EXPERT) {
    metaData->playerNode->skillsData.offensiveSkillStats.durabilityLoss -=
        HSSOH_DURABILITY_EXPERT;
  } else if (skillId == SHARP_INSTINCTS) {
    metaData->playerNode->skillsData.offensiveSkillStats.hitChance +=
        HSSOH_SHARP_INSTINCTS;
  } else if (skillId == COMBO_BOOST) {
    metaData->playerNode->skillsData.offensiveSkillStats.damageWHPH50P +=
        HSSOH_COMBO_BOOST;
  } else if (skillId == BLOODY_EDGE) {
    metaData->playerNode->skillsData.offensiveSkillStats.damageWHPL40P +=
        HSSOH_BLOODY_EDGE;
  } else if (skillId == CRITICAL_SURGE) {
    metaData->playerNode->skillsData.offensiveSkillStats.critsDealXD +=
        HSSOH_CRITICAL_SURGE;
  } else if (skillId == DUAL_FOCUS) {
    metaData->playerNode->skillsData.offensiveSkillStats.critChance +=
        HSSOH_DUAL_FOCUS[0];
    metaData->playerNode->skillsData.offensiveSkillStats.hitChance +=
        HSSOH_DUAL_FOCUS[1];
  } else if (skillId == OVERPOWER) {
    metaData->playerNode->skillsData.offensiveSkillStats.damage +=
        HSSOH_OVERPOWER;
  } else if (skillId == EXECUTIONER) {
    metaData->playerNode->skillsData.offensiveSkillStats.damageNPEnemyHPL30P +=
        HSSOH_EXECUTIONER;
  }
}
