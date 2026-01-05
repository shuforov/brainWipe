#include <genesis.h>
#include "../../headers/scenes/scene.h"
#include "../../headers/handlers/hideoutSceneStatsOffensiveHandler.h"
#include "../../headers/scenes/hideoutConstants.h"
#include "../../headers/handlers/drawButtonHandler.h"

void HSSOH_dataInit(MetaData *metaData) {
  // Current skills init data
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .borderPosition = (Vec2){2, 17};
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .borderSize = (SizeBox){36, 9};
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .skillsSize = 0;
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
  if (metaData->hintOptionData.statisticData.offensiveData.currentSkills
          .skillsSize < 5) {
    // Draw next skill data
    Skill leftOffensiveData =
        CCH_OFFENSIVE_DATA[metaData->hintOptionData.statisticData.offensiveData
                               .nextSkills.skills[0]];
    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.offensiveData
                              .nextSkills.leftSkill.namePosition,
                          leftOffensiveData.name, leftOffensiveData.nameSize,
                          (Vec2){11, 9});

    drawTextTilesWHLimits(metaData->hintOptionData.statisticData.offensiveData
                              .nextSkills.leftSkill.descriptionPosition,
                          leftOffensiveData.description,
                          leftOffensiveData.descriptionSize, (Vec2){11, 16});
    Skill rightOffensiveData =
        CCH_OFFENSIVE_DATA[metaData->hintOptionData.statisticData.offensiveData
                               .nextSkills.skills[1]];
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
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .skills[metaData->hintOptionData.statisticData.offensiveData.currentSkills
                  .skillsSize] = skillId;
  metaData->hintOptionData.statisticData.offensiveData.currentSkills
      .skillsSize++;
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
  for (u16 i = 0; i < metaData->hintOptionData.statisticData.offensiveData
                          .currentSkills.skillsSize;
       i++) {
    Skill skillMetaData =
        CCH_OFFENSIVE_DATA[metaData->hintOptionData.statisticData.offensiveData
                               .currentSkills.skills[i]];
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
