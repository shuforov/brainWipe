#include <genesis.h>
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/hideoutSceneStatsUtility.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/scenes/hideoutConstants.h"

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
      0;
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
  if (metaData->hintOptionData.statisticData.utilityData.currentSkills
          .skillsSize < 5) {
    // Draw next skill data
    Skill leftUtilityData =
        CCH_UTILITY_DATA[metaData->hintOptionData.statisticData.utilityData
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
        CCH_UTILITY_DATA[metaData->hintOptionData.statisticData.utilityData
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
  metaData->hintOptionData.statisticData.utilityData.currentSkills
      .skills[metaData->hintOptionData.statisticData.utilityData.currentSkills
                  .skillsSize] = skillId;
  metaData->hintOptionData.statisticData.utilityData.currentSkills.skillsSize++;
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
  for (u16 i = 0; i < metaData->hintOptionData.statisticData.utilityData
                          .currentSkills.skillsSize;
       i++) {
    Skill skillMetaData =
        CCH_UTILITY_DATA[metaData->hintOptionData.statisticData.utilityData
                             .currentSkills.skills[i]];
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
