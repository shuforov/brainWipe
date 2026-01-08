#include "../../headers/handlers/hideoutSceneStatsUtilityHandler.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/scenes/hideoutConstants.h"
#include "../../headers/scenes/scene.h"
#include "types.h"
#include <genesis.h>

typedef enum {
  KEY_FINDER,
  MEDIC_KNOWLEDGE,
  INITIATIVE,
  WEAK_SPOT_SCAN,
  GRANADIER,
  CHEM_EXPERT,
  BETTER_SALVAGE,
  ECONOMIST,
  SECOND_WIND,
  LUCKY_BREAK
} HSSDHSkillTypes;

static const Skill HSSUH_UTILITY_DATA[10] = {
    // Key finder: +10% key drop chance
    (Skill){{0x4E, 0x49, 0x36, 0x1E, 0x52, 0x16, 0x36, 0x3C, 0x5B, 0x52, 0x33,
             0x20},
            {0x6E, 0x60, 0x5F, 0x70, 0x16, 0x53, 0x1E, 0x3E, 0x47,
             0x16, 0x20, 0x32, 0x40, 0x1E, 0x2A, 0x33, 0x3E, 0x3E,
             0x5C, 0x16, 0x36, 0x3C, 0x5B, 0x52, 0x33, 0x20},
            12,
            26},
    // Medic knowledge: medkits heal +10 more HP
    (Skill){{0x38, 0x28, 0x2A, 0x32, 0x52, 0x3E, 0x1E, 0x16, 0x3D, 0x1E,
             0x35, 0x47, 0x48, 0x28, 0x46, 0x3E, 0x33, 0x47, 0x48, 0x5A},
            {0x1E, 0x40, 0x48, 0x28, 0x52, 0x36, 0x32, 0x16, 0x3C, 0x33, 0x36,
             0x49, 0x5B, 0x48, 0x5A, 0x16, 0x3E, 0x1E, 0x16, 0x60, 0x5F, 0x16,
             0x27, 0x23, 0x41, 0x16, 0x1F, 0x33, 0x3C, 0x5A, 0x53, 0x28},
            20,
            32},
    // Initiative: +10% chance to act first
    (Skill){{0x2E, 0x3E, 0x33, 0x51, 0x33, 0x1E, 0x48, 0x32, 0x20, 0x1E},
            {0x6E, 0x60, 0x5F, 0x70, 0x16, 0x53, 0x1E, 0x3E, 0x47, 0x16,
             0x40, 0x28, 0x46, 0x53, 0x3F, 0x34, 0x16, 0x2A, 0x33, 0x34},
            10,
            20},
    // Weak spot scan: reveals enemy DEF & HP before fight
    (Skill){{0x42, 0x36, 0x1E, 0x3E, 0x49, 0x20, 0x1E, 0x3E, 0x3E,
             0x5C, 0x16, 0x20, 0x46, 0x1E, 0x2C, 0x3C, 0x32, 0x20,
             0x32, 0x50, 0x16, 0x3D, 0x33, 0x47, 0x51, 0x5A},
            {0x40, 0x3F, 0x36, 0x1E, 0x2C, 0x49, 0x29, 0x16, 0x27,
             0x4B, 0x43, 0x16, 0x33, 0x16, 0x27, 0x23, 0x41, 0x16,
             0x20, 0x3F, 0x46, 0x3F, 0x21, 0x1E, 0x16, 0x40, 0x28,
             0x46, 0x28, 0x2A, 0x16, 0x1F, 0x3F, 0x29, 0x3D},
            26,
            35},
    // Granadier: throwables deal +10 damage
    (Skill){{0x1C, 0x46, 0x1E, 0x3E, 0x1E, 0x48, 0x3F, 0x3D, 0x28, 0x48, 0x3E,
             0x32, 0x36},
            {0x3D, 0x28, 0x48, 0x1E, 0x3C, 0x5A, 0x3E, 0x33, 0x16,
             0x47, 0x3E, 0x1E, 0x46, 0x5C, 0x2A, 0x32, 0x16, 0x3E,
             0x1E, 0x3E, 0x3F, 0x47, 0x5C, 0x48, 0x5A, 0x16, 0x6E,
             0x60, 0x5F, 0x16, 0x53, 0x36, 0x3F, 0x2A, 0x32},
            13,
            35},
    // Chem expert: last status effects 1 extra turn
    (Skill){{0x4B, 0x33, 0x3D, 0x33, 0x36, 0x6F, 0x28, 0x36, 0x47, 0x40, 0x28,
             0x46, 0x48},
            {0x28, 0x4A, 0x28, 0x36, 0x48, 0x32, 0x16, 0x47, 0x48,
             0x1E, 0x3E, 0x49, 0x16, 0x48, 0x46, 0x32, 0x20, 0x1E,
             0x5B, 0x48, 0x5A, 0x16, 0x3E, 0x1E, 0x16, 0x60, 0x16,
             0x50, 0x33, 0x2A, 0x16, 0x2A, 0x3F, 0x20, 0x53, 0x28},
            13,
            36},
    // Better salvage: +20% more credits from kills
    (Skill){{0x31, 0x46, 0x1E, 0x54, 0x32, 0x35, 0x16, 0x46, 0x3F, 0x2C, 0x1F,
             0x33, 0x46},
            {0x6E, 0x61, 0x5F, 0x70, 0x16, 0x1F, 0x33, 0x3C, 0x5A, 0x53, 0x28,
             0x16, 0x36, 0x46, 0x28, 0x2A, 0x32, 0x48, 0x33, 0x20, 0x16, 0x2C,
             0x1E, 0x16, 0x20, 0x1F, 0x32, 0x20, 0x47, 0x48, 0x20, 0x1E},
            13,
            32},
    // Economist: store items cost -10%
    (Skill){{0x24, 0x36, 0x3F, 0x3E, 0x3F, 0x3D, 0x33, 0x47, 0x48},
            {0x20, 0x1E, 0x46, 0x48, 0x33, 0x47, 0x48, 0x5A, 0x16, 0x48, 0x3F,
             0x20, 0x1E, 0x46, 0x33, 0x20, 0x16, 0x49, 0x16, 0x3D, 0x1E, 0x21,
             0x1E, 0x2C, 0x32, 0x3E, 0x33, 0x16, 0x2C, 0x3E, 0x32, 0x2B, 0x28,
             0x3E, 0x1E, 0x16, 0x3E, 0x1E, 0x16, 0x60, 0x5F, 0x70},
            9,
            42},
    // Second wind: 1 free heal at 0HP (only once per battle)
    (Skill){{0x23, 0x46, 0x49, 0x21, 0x32, 0x35, 0x16, 0x40, 0x3F, 0x2A, 0x32,
             0x50},
            {0x60, 0x16, 0x1F, 0x28, 0x2C, 0x36, 0x3F, 0x53, 0x48, 0x3F,
             0x20, 0x3E, 0x28, 0x16, 0x3C, 0x33, 0x36, 0x49, 0x20, 0x1E,
             0x3E, 0x3E, 0x5C, 0x16, 0x40, 0x46, 0x32, 0x16, 0x5F, 0x16,
             0x27, 0x23, 0x41, 0x16, 0x48, 0x33, 0x3C, 0x5A, 0x36, 0x32,
             0x16, 0x3F, 0x2A, 0x32, 0x3E, 0x16, 0x46, 0x1E, 0x2C, 0x16,
             0x2C, 0x1E, 0x16, 0x1F, 0x33, 0x35},
            12,
            56},
    // Lucky break: +10% drop chance for all items
    (Skill){{0x4F, 0x1E, 0x47, 0x3C, 0x32, 0x20, 0x32, 0x35, 0x16, 0x20, 0x32,
             0x40, 0x1E, 0x2A, 0x3F, 0x36},
            {0x6E, 0x60, 0x5F, 0x70, 0x16, 0x53, 0x1E, 0x3E, 0x47,
             0x16, 0x20, 0x32, 0x40, 0x1E, 0x2A, 0x33, 0x3E, 0x3E,
             0x5C, 0x16, 0x20, 0x47, 0x33, 0x50, 0x16, 0x40, 0x46,
             0x28, 0x2A, 0x3D, 0x28, 0x48, 0x33, 0x20},
            16,
            34}};

static const u16 HSSUH_KEY_FINDER = {10};
static const u16 HSSUH_MEDIC_KNOWLEDGE = {10};
static const u16 HSSUH_INITIATIVE = {10};
static const bool HSSUH_WEAK_SPOT_SCAN = {true};
static const u16 HSSUH_GRANADIER = {10};
static const u16 HSSUH_CHEM_EXPERT = {1};
static const u16 HSSUH_BETTER_SALVAGE = {20};
static const u16 HSSUH_ECONOMIST = {10};
static const bool HSSUH_SECOND_WIND = {true};
static const u16 HSSUH_LUCKY_BREAK = {10};

void HSSUH_dataInit(MetaData *metaData) {
  // Next Skill init data
  metaData->hintOptionData.statisticData.utilityData.nextSkills.borderPosition =
      (Vec2){2, 7};
  metaData->hintOptionData.statisticData.utilityData.nextSkills.borderSize =
      (SizeBox){36, 10};
  metaData->hintOptionData.statisticData.utilityData.nextSkills.skills[0] = 0;
  metaData->hintOptionData.statisticData.utilityData.nextSkills.skills[1] = 1;
  metaData->hintOptionData.statisticData.utilityData.nextSkills.rightSkill
      .namePosition = (Vec2){25, 8};
  metaData->hintOptionData.statisticData.utilityData.nextSkills.rightSkill
      .descriptionPosition = (Vec2){25, 10};
  metaData->hintOptionData.statisticData.utilityData.nextSkills.leftSkill
      .namePosition = (Vec2){3, 8};
  metaData->hintOptionData.statisticData.utilityData.nextSkills.leftSkill
      .descriptionPosition = (Vec2){3, 10};
  // Current skills init data
  metaData->hintOptionData.statisticData.utilityData.currentSkills
      .borderPosition = (Vec2){2, 17};
  metaData->hintOptionData.statisticData.utilityData.currentSkills.borderSize =
      (SizeBox){36, 9};
  metaData->hintOptionData.statisticData.utilityData.currentSkills.skillsSize =
      &metaData->playerNode->skillsData.utilitySize;
  metaData->hintOptionData.statisticData.utilityData.currentSkills.skills =
      &metaData->playerNode->skillsData.utility;
  memcpy(metaData->hintOptionData.statisticData.utilityData.currentSkills
             .titleTiles,
         CURRENT_SKILL_TITLE_NAME, sizeof(CURRENT_SKILL_TITLE_NAME));
  metaData->hintOptionData.statisticData.utilityData.currentSkills
      .titleTilesPosition = (Vec2){10, 18};
  metaData->hintOptionData.statisticData.utilityData.currentSkills
      .firstSkillPosition = (Vec2){3, 19};
  metaData->hintOptionData.statisticData.utilityData.currentSkills
      .focusBoxPosition = (Vec2){3, 19};
  metaData->hintOptionData.statisticData.utilityData.currentSkills
      .focusBoxSize = (SizeBox){34, 6};
}
void HSSUH_nextSkillsRender(MetaData *metaData) {
  // Clear border
  Vec2 startClearPosition =
      (Vec2){metaData->hintOptionData.statisticData.utilityData.nextSkills
                     .borderPosition.x +
                 1,
             metaData->hintOptionData.statisticData.utilityData.nextSkills
                     .borderPosition.y +
                 1};
  SizeBox boxClear = (SizeBox){metaData->hintOptionData.statisticData
                                       .utilityData.nextSkills.borderSize.w -
                                   1,
                               metaData->hintOptionData.statisticData
                                       .utilityData.nextSkills.borderSize.h -
                                   1};
  drawFillBox(startClearPosition, boxClear, metaData->borderTilesData.fill);
  // Draw next skill border
  drawBorder(
      metaData->hintOptionData.statisticData.utilityData.nextSkills
          .borderPosition,
      metaData->hintOptionData.statisticData.utilityData.nextSkills.borderSize,
      metaData->borderTilesData);
  if (*metaData->hintOptionData.statisticData.utilityData.currentSkills
           .skillsSize < 5) {
    // Draw next skill data
    Skill leftUtilityData =
        HSSUH_UTILITY_DATA[metaData->hintOptionData.statisticData.utilityData
                               .nextSkills.skills[0]];
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.utilityData
                              .nextSkills.leftSkill.namePosition,
                          leftUtilityData.name, leftUtilityData.nameSize,
                          (Vec2){11, 9});

    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.utilityData
                              .nextSkills.leftSkill.descriptionPosition,
                          leftUtilityData.description,
                          leftUtilityData.descriptionSize, (Vec2){11, 16});
    Skill rightUtilityData =
        HSSUH_UTILITY_DATA[metaData->hintOptionData.statisticData.utilityData
                               .nextSkills.skills[1]];
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.utilityData
                              .nextSkills.rightSkill.namePosition,
                          rightUtilityData.name, rightUtilityData.nameSize,
                          (Vec2){36, 9});
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.utilityData
                              .nextSkills.rightSkill.descriptionPosition,
                          rightUtilityData.description,
                          rightUtilityData.descriptionSize, (Vec2){36, 16});
  }
}
void HSSUH_acceptSkillHandelr(MetaData *metaData, u16 skillId) {
  (*metaData->hintOptionData.statisticData.utilityData.currentSkills
        .skills)[*metaData->hintOptionData.statisticData.utilityData
                      .currentSkills.skillsSize] = skillId;
  (*metaData->hintOptionData.statisticData.utilityData.currentSkills
        .skillsSize)++;
  u16 secondSkillId =
      metaData->hintOptionData.statisticData.utilityData.nextSkills.skills[1];
  if (secondSkillId < 9) {
    metaData->hintOptionData.statisticData.utilityData.nextSkills.skills[0] =
        secondSkillId + 1;
    metaData->hintOptionData.statisticData.utilityData.nextSkills.skills[1] =
        secondSkillId + 2;
  }
}
void HSSUH_currentSkillsRender(MetaData *metaData) {
  // Clear current skill box
  drawFillBox(metaData->hintOptionData.statisticData.utilityData.currentSkills
                  .focusBoxPosition,
              metaData->hintOptionData.statisticData.utilityData.currentSkills
                  .focusBoxSize,
              metaData->borderTilesData.fill);
  // Draw border
  drawBorder(metaData->hintOptionData.statisticData.utilityData.currentSkills
                 .borderPosition,
             metaData->hintOptionData.statisticData.utilityData.currentSkills
                 .borderSize,
             metaData->borderTilesData);
  drawTextTiles(metaData->hintOptionData.statisticData.utilityData.currentSkills
                    .titleTilesPosition,
                metaData->hintOptionData.statisticData.utilityData.currentSkills
                    .titleTiles,
                ARRAY_LEN(metaData->hintOptionData.statisticData.utilityData
                              .currentSkills.titleTiles));
  // render each available skill
  for (u16 i = 0; i < *metaData->hintOptionData.statisticData.utilityData
                           .currentSkills.skillsSize;
       i++) {
    Skill skillMetaData =
        HSSUH_UTILITY_DATA[(*metaData->hintOptionData.statisticData.utilityData
                                 .currentSkills.skills)[i]];
    Vec2 namePosition =
        (Vec2){metaData->hintOptionData.statisticData.utilityData.currentSkills
                   .firstSkillPosition.x,
               metaData->hintOptionData.statisticData.utilityData.currentSkills
                       .firstSkillPosition.y +
                   i};
    Vec2 descriptionPosition =
        (Vec2){metaData->hintOptionData.statisticData.utilityData.currentSkills
                       .firstSkillPosition.x +
                   skillMetaData.nameSize + 1,
               metaData->hintOptionData.statisticData.utilityData.currentSkills
                       .firstSkillPosition.y +
                   i};
    Vec2 descriptionLimitPosition = (Vec2){36, descriptionPosition.y};

    drawTextTiles(namePosition, skillMetaData.name, skillMetaData.nameSize);
    drawTextTilesWHLimits(descriptionPosition, skillMetaData.description,
                          skillMetaData.descriptionSize,
                          descriptionLimitPosition);
  }
}

void HSSUH_setSkillStatsHandler(MetaData *metaData, u16 skillId) {
  if (KEY_FINDER) {
    metaData->playerNode->skillsData.utilitySkillStats.keyDropChance +=
        HSSUH_KEY_FINDER;
  } else if (MEDIC_KNOWLEDGE) {
    metaData->playerNode->skillsData.utilitySkillStats.medkitsHeal +=
        HSSUH_MEDIC_KNOWLEDGE;
  } else if (INITIATIVE) {
    metaData->playerNode->skillsData.utilitySkillStats.chanceAF +=
        HSSUH_INITIATIVE;
  } else if (WEAK_SPOT_SCAN) {
    metaData->playerNode->skillsData.utilitySkillStats.rEDHBF =
        HSSUH_WEAK_SPOT_SCAN;
  } else if (GRANADIER) {
    metaData->playerNode->skillsData.utilitySkillStats.damageT +=
        HSSUH_GRANADIER;
  } else if (CHEM_EXPERT) {
    metaData->playerNode->skillsData.utilitySkillStats.lastSEET +=
        HSSUH_CHEM_EXPERT;
  } else if (BETTER_SALVAGE) {
    metaData->playerNode->skillsData.utilitySkillStats.creditsFK +=
        HSSUH_BETTER_SALVAGE;
  } else if (ECONOMIST) {
    metaData->playerNode->skillsData.utilitySkillStats.storeItemsCost +=
        HSSUH_ECONOMIST;
  } else if (SECOND_WIND) {
    metaData->playerNode->skillsData.utilitySkillStats.freeHeal =
        HSSUH_SECOND_WIND;
  } else if (LUCKY_BREAK) {
    metaData->playerNode->skillsData.utilitySkillStats.dropChanceFAI +=
        HSSUH_LUCKY_BREAK;
  }
}
