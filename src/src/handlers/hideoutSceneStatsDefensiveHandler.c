#include <genesis.h>
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/drawButtonHandler.h"
#include "../../headers/handlers/hideoutSceneStatsDefensiveHandler.h"
#include "../../headers/scenes/hideoutConstants.h"

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
      .skillsSize = 0;
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
  if (metaData->hintOptionData.statisticData.defensiveData.currentSkills
          .skillsSize < 5) {
    // Draw next skill data
    Skill leftDefensiveData =
        CCH_DEFENSIVE_DATA[metaData->hintOptionData.statisticData.defensiveData
                               .nextSkills.skills[0]];
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.defensiveData
                              .nextSkills.leftSkill.namePosition,
                          leftDefensiveData.name, leftDefensiveData.nameSize,
                          (Vec2){11, 9});

    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.defensiveData
                              .nextSkills.leftSkill.descriptionPosition,
                          leftDefensiveData.description,
                          leftDefensiveData.descriptionSize, (Vec2){11, 16});
    Skill rightDefensiveData =
        CCH_DEFENSIVE_DATA[metaData->hintOptionData.statisticData.defensiveData
                               .nextSkills.skills[1]];
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
  metaData->hintOptionData.statisticData.defensiveData.currentSkills
      .skills[metaData->hintOptionData.statisticData.defensiveData.currentSkills
                  .skillsSize] = skillId;
  metaData->hintOptionData.statisticData.defensiveData.currentSkills
      .skillsSize++;
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
  for (u16 i = 0; i < metaData->hintOptionData.statisticData.defensiveData
                          .currentSkills.skillsSize;
       i++) {
    Skill skillMetaData =
        CCH_DEFENSIVE_DATA[metaData->hintOptionData.statisticData.defensiveData
                               .currentSkills.skills[i]];
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
