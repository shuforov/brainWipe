#include "../../headers/handlers/hideoutSceneStatsDefensiveHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/scenes/hideoutConstants.h"
#include "../../headers/scenes/scene.h"
#include <genesis.h>

typedef enum {
  HP_BOOST,
  ARMOR_PLATING,
  TOUGH_SKIN,
  PAIN_RESISTANCE,
  COUNTER_GUARD,
  SOLID_STANCE,
  ADRENAL_RECOVERY,
  LAST_STAND,
  IRON_SHELL,
  TITAN_CORE
} HSSDHSkillTypes;

static const Skill HSSDH_DEFENSIVE_DATA[10] = {
    // HP Boost +20 max HP
    (Skill){{0x3B, 0x33, 0x3C, 0x20, 0x32, 0x54, 0x28, 0x3E, 0x3E, 0x5C, 0x16,
             0x27, 0x23, 0x41},
            {0x6E, 0x61, 0x5F, 0x16, 0x3D, 0x1E, 0x36, 0x47, 0x5E, 0x16, 0x27,
             0x23, 0x41},
            14,
            13},
    // Armor Plating +2 DEF
    (Skill){{0x1A, 0x46, 0x3F, 0x3E, 0x28, 0x40, 0x3C, 0x1E, 0x47, 0x48, 0x32,
             0x3E, 0x32},
            {0x6E, 0x61, 0x16, 0x27, 0x4B, 0x43},
            13,
            6},
    // Tough skin -10% damage taken
    (Skill){{0x38, 0x33, 0x51, 0x3E, 0x1E, 0x16, 0x53, 0x36, 0x33, 0x46, 0x1E},
            {0x6F, 0x60, 0x5F, 0x70, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x32},
            11,
            10},
    // Pain resistance -20% chance enemy crits you
    (Skill){{0x42, 0x48, 0x33, 0x35, 0x36, 0x33, 0x47, 0x48, 0x5A, 0x16, 0x2A,
             0x3F, 0x16, 0x1F, 0x3F, 0x3C, 0x5B},
            {0x53, 0x1E, 0x3E, 0x47, 0x16, 0x36, 0x46, 0x32, 0x48, 0x5E, 0x16,
             0x49, 0x2A, 0x1E, 0x46, 0x49, 0x16, 0x20, 0x3F, 0x46, 0x3F, 0x21,
             0x1E, 0x16, 0x40, 0x3F, 0x16, 0x21, 0x46, 0x1E, 0x20, 0x51, 0x5B},
            17,
            33},
    // Counter guard: when you defend, 20% chance to counter attack
    (Skill){{0x31, 0x3F, 0x3E, 0x48, 0x46, 0x6F, 0x47, 0x48, 0x33, 0x35, 0x36,
             0x1E},
            {0x40, 0x46, 0x32, 0x16, 0x2C, 0x1E, 0x50, 0x32, 0x47,
             0x48, 0x33, 0x16, 0x61, 0x5F, 0x70, 0x16, 0x53, 0x1E,
             0x3E, 0x47, 0x16, 0x36, 0x3F, 0x3E, 0x48, 0x46, 0x1E,
             0x48, 0x1E, 0x36, 0x49, 0x20, 0x1E, 0x48, 0x32},
            12,
            35},
    // Solid stance: defend reduces 60% damage (insted of 50%)
    (Skill){{0x43, 0x20, 0x28, 0x46, 0x2A, 0x1E, 0x16, 0x47, 0x48, 0x33, 0x35,
             0x36, 0x1E},
            {0x2C, 0x1E, 0x50, 0x32, 0x47, 0x48, 0x16, 0x2C, 0x3D, 0x28,
             0x3E, 0x53, 0x49, 0x29, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x49,
             0x16, 0x3E, 0x1E, 0x16, 0x65, 0x5F, 0x70, 0x16, 0x2C, 0x1E,
             0x3D, 0x33, 0x47, 0x48, 0x5A, 0x16, 0x64, 0x5F, 0x70},
            13,
            39},
    // Adrenal recovery: heal +10% more
    (Skill){{0x1B, 0x33, 0x2A, 0x3E, 0x3F, 0x20, 0x3C, 0x28, 0x3E, 0x3E, 0x5C,
             0x16, 0x1E, 0x2A, 0x46, 0x28, 0x3E, 0x1E, 0x3C, 0x33, 0x3E, 0x49},
            {0x3C, 0x33, 0x36, 0x49, 0x20, 0x1E, 0x3E, 0x3E,
             0x5C, 0x16, 0x3E, 0x1E, 0x16, 0x6E, 0x60, 0x5F,
             0x70, 0x16, 0x1F, 0x33, 0x3C, 0x5A, 0x53, 0x28},
            22,
            24},
    // Last stand: +20% damage when HP <20%
    (Skill){{0x3A, 0x47, 0x48, 0x1E, 0x3E, 0x3E, 0x33, 0x35, 0x16, 0x1F, 0x33,
             0x35},
            {0x6E, 0x61, 0x5F, 0x70, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x32, 0x16,
             0x40, 0x46, 0x32, 0x16, 0x16, 0x72, 0x16, 0x61, 0x5F, 0x70},
            12,
            21},
    // Iron shell: -25% damage taken permanently
    (Skill){{0x27, 0x1E, 0x3C, 0x33, 0x2C, 0x3E, 0x1E, 0x16, 0x3F, 0x1F, 0x3F,
             0x3C, 0x3F, 0x3E, 0x36, 0x1E},
            {0x6F, 0x61, 0x64, 0x70, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x32, 0x16,
             0x3E, 0x1E, 0x2C, 0x1E, 0x20, 0x2B, 0x2A, 0x32},
            16,
            19},
    // Titan core: +50 max HP
    (Skill){{0x57, 0x2A, 0x46, 0x3F, 0x16, 0x43, 0x32, 0x48, 0x1E, 0x3E, 0x1E},
            {0x6E, 0x64, 0x5F, 0x16, 0x3D, 0x1E, 0x36, 0x47, 0x5E, 0x16, 0x27,
             0x23, 0x41},
            11,
            13}};

static const u16 HSSDH_HP_BOOST = {20};
static const u16 HSSDH_ARMOR_PLATING = {2};
static const u16 HSSDH_TOUGH_SKIN = {10};
static const u16 HSSDH_PAIN_RESISTANCE = {20};
static const u16 HSSDH_COUNTER_GUARD = {20};
static const u16 HSSDH_SOLID_STANCE = {60};
static const u16 HSSDH_ADRENAL_RECOVERY = {10};
static const u16 HSSDH_LAST_STAND = {20};
static const u16 HSSDH_IRON_SHELL = {25};
static const u16 HSSDH_TITAN_CORE = {50};

void HSSDH_dataInit(MetaData *metaData) {
  // Next Skill init data
  metaData->hintOptionData.statisticData.defensiveData.nextSkills
      .borderPosition = (Vec2){2, 7};
  metaData->hintOptionData.statisticData.defensiveData.nextSkills.borderSize =
      (SizeBox){36, 10};
  metaData->hintOptionData.statisticData.defensiveData.nextSkills.skills[0] = 0;
  metaData->hintOptionData.statisticData.defensiveData.nextSkills.skills[1] = 1;
  metaData->hintOptionData.statisticData.defensiveData.nextSkills.rightSkill
      .namePosition = (Vec2){25, 8};
  metaData->hintOptionData.statisticData.defensiveData.nextSkills.rightSkill
      .descriptionPosition = (Vec2){25, 10};
  metaData->hintOptionData.statisticData.defensiveData.nextSkills.leftSkill
      .namePosition = (Vec2){3, 8};
  metaData->hintOptionData.statisticData.defensiveData.nextSkills.leftSkill
      .descriptionPosition = (Vec2){3, 10};
  // Current skills init data
  metaData->hintOptionData.statisticData.defensiveData.currentSkills
      .borderPosition = (Vec2){2, 17};
  metaData->hintOptionData.statisticData.defensiveData.currentSkills
      .borderSize = (SizeBox){36, 9};
  metaData->hintOptionData.statisticData.defensiveData.currentSkills
      .skillsSize = &metaData->playerNode->skillsData.defensiveSize;
  metaData->hintOptionData.statisticData.defensiveData.currentSkills.skills =
      &metaData->playerNode->skillsData.defensive;
  memcpy(metaData->hintOptionData.statisticData.defensiveData.currentSkills
             .titleTiles,
         CURRENT_SKILL_TITLE_NAME, sizeof(CURRENT_SKILL_TITLE_NAME));
  metaData->hintOptionData.statisticData.defensiveData.currentSkills
      .titleTilesPosition = (Vec2){10, 18};
  metaData->hintOptionData.statisticData.defensiveData.currentSkills
      .firstSkillPosition = (Vec2){3, 19};
  metaData->hintOptionData.statisticData.defensiveData.currentSkills
      .focusBoxPosition = (Vec2){3, 19};
  metaData->hintOptionData.statisticData.defensiveData.currentSkills
      .focusBoxSize = (SizeBox){34, 6};
}

void HSSDH_nextSkillsRender(MetaData *metaData) {
  // Clear border
  Vec2 startClearPosition =
      (Vec2){metaData->hintOptionData.statisticData.defensiveData.nextSkills
                     .borderPosition.x +
                 1,
             metaData->hintOptionData.statisticData.defensiveData.nextSkills
                     .borderPosition.y +
                 1};
  SizeBox boxClear = (SizeBox){metaData->hintOptionData.statisticData
                                       .defensiveData.nextSkills.borderSize.w -
                                   1,
                               metaData->hintOptionData.statisticData
                                       .defensiveData.nextSkills.borderSize.h -
                                   1};
  drawFillBox(startClearPosition, boxClear, metaData->borderTilesData.fill);
  // Draw next skill border
  drawBorder(metaData->hintOptionData.statisticData.defensiveData.nextSkills
                 .borderPosition,
             metaData->hintOptionData.statisticData.defensiveData.nextSkills
                 .borderSize,
             metaData->borderTilesData);
  if (*metaData->hintOptionData.statisticData.defensiveData.currentSkills
           .skillsSize < 5) {
    // Draw next skill data
    Skill leftDefensiveData =
        HSSDH_DEFENSIVE_DATA[metaData->hintOptionData.statisticData
                                 .defensiveData.nextSkills.skills[0]];
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.defensiveData
                              .nextSkills.leftSkill.namePosition,
                          leftDefensiveData.name, leftDefensiveData.nameSize,
                          (Vec2){11, 9});

    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.defensiveData
                              .nextSkills.leftSkill.descriptionPosition,
                          leftDefensiveData.description,
                          leftDefensiveData.descriptionSize, (Vec2){11, 16});
    Skill rightDefensiveData =
        HSSDH_DEFENSIVE_DATA[metaData->hintOptionData.statisticData
                                 .defensiveData.nextSkills.skills[1]];
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.defensiveData
                              .nextSkills.rightSkill.namePosition,
                          rightDefensiveData.name, rightDefensiveData.nameSize,
                          (Vec2){36, 9});
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.defensiveData
                              .nextSkills.rightSkill.descriptionPosition,
                          rightDefensiveData.description,
                          rightDefensiveData.descriptionSize, (Vec2){36, 16});
  }
}

void HSSDH_acceptSkillHandelr(MetaData *metaData, u16 skillId) {
  (*metaData->hintOptionData.statisticData.defensiveData.currentSkills
        .skills)[(*metaData->hintOptionData.statisticData.defensiveData
                       .currentSkills.skillsSize)] = skillId;
  (*metaData->hintOptionData.statisticData.defensiveData.currentSkills
        .skillsSize)++;
  u16 secondSkillId =
      metaData->hintOptionData.statisticData.defensiveData.nextSkills.skills[1];
  if (secondSkillId < 9) {
    metaData->hintOptionData.statisticData.defensiveData.nextSkills.skills[0] =
        secondSkillId + 1;
    metaData->hintOptionData.statisticData.defensiveData.nextSkills.skills[1] =
        secondSkillId + 2;
  }
}

void HSSDH_currentSkillsRender(MetaData *metaData) {
  // Clear current skill box
  drawFillBox(metaData->hintOptionData.statisticData.defensiveData.currentSkills
                  .focusBoxPosition,
              metaData->hintOptionData.statisticData.defensiveData.currentSkills
                  .focusBoxSize,
              metaData->borderTilesData.fill);
  // Draw border
  drawBorder(metaData->hintOptionData.statisticData.defensiveData.currentSkills
                 .borderPosition,
             metaData->hintOptionData.statisticData.defensiveData.currentSkills
                 .borderSize,
             metaData->borderTilesData);
  drawTextTiles(metaData->hintOptionData.statisticData.defensiveData
                    .currentSkills.titleTilesPosition,
                metaData->hintOptionData.statisticData.defensiveData
                    .currentSkills.titleTiles,
                ARRAY_LEN(metaData->hintOptionData.statisticData.defensiveData
                              .currentSkills.titleTiles));
  // render each available skill
  for (u16 i = 0; i < *metaData->hintOptionData.statisticData.defensiveData
                           .currentSkills.skillsSize;
       i++) {
    Skill skillMetaData =
        HSSDH_DEFENSIVE_DATA[(*metaData->hintOptionData.statisticData
                                   .defensiveData.currentSkills.skills)[i]];
    Vec2 namePosition =
        (Vec2){metaData->hintOptionData.statisticData.defensiveData
                   .currentSkills.firstSkillPosition.x,
               metaData->hintOptionData.statisticData.defensiveData
                       .currentSkills.firstSkillPosition.y +
                   i};
    Vec2 descriptionPosition =
        (Vec2){metaData->hintOptionData.statisticData.defensiveData
                       .currentSkills.firstSkillPosition.x +
                   skillMetaData.nameSize + 1,
               metaData->hintOptionData.statisticData.defensiveData
                       .currentSkills.firstSkillPosition.y +
                   i};
    Vec2 descriptionLimitPosition = (Vec2){36, descriptionPosition.y};

    drawTextTiles(namePosition, skillMetaData.name, skillMetaData.nameSize);
    drawTextTilesWHLimits(descriptionPosition, skillMetaData.description,
                          skillMetaData.descriptionSize,
                          descriptionLimitPosition);
  }
}

void HSSDH_setSkillStatsHandler(MetaData *metaData, u16 skillId) {
  if (skillId == HP_BOOST) {
      metaData->playerNode->skillsData.defensiveSkillStats.maxHP += HSSDH_HP_BOOST;
  } else if (skillId == ARMOR_PLATING) {
      metaData->playerNode->skillsData.defensiveSkillStats.defense += HSSDH_ARMOR_PLATING;
  } else if (skillId == TOUGH_SKIN) {
      metaData->playerNode->skillsData.defensiveSkillStats.damageTaken -= HSSDH_TOUGH_SKIN;
  } else if (skillId == PAIN_RESISTANCE) {
      metaData->playerNode->skillsData.defensiveSkillStats.chanceECY -= HSSDH_PAIN_RESISTANCE;
  } else if (skillId == COUNTER_GUARD) {
      metaData->playerNode->skillsData.defensiveSkillStats.chanceCA += HSSDH_COUNTER_GUARD;
  } else if (skillId == SOLID_STANCE) {
      metaData->playerNode->skillsData.defensiveSkillStats.defendR60D = HSSDH_SOLID_STANCE;
  } else if (skillId == ADRENAL_RECOVERY) {
      metaData->playerNode->skillsData.defensiveSkillStats.healNPM += HSSDH_ADRENAL_RECOVERY;
  } else if (skillId == LAST_STAND) {
      metaData->playerNode->skillsData.defensiveSkillStats.damageWHPL20P += HSSDH_LAST_STAND;
  } else if (skillId == IRON_SHELL) {
      metaData->playerNode->skillsData.defensiveSkillStats.damageTaken -= HSSDH_IRON_SHELL;
  } else if (skillId == TITAN_CORE) {
      metaData->playerNode->skillsData.defensiveSkillStats.maxHP += HSSDH_TITAN_CORE;
  }
}
