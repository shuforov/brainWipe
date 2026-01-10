#ifndef COMMON_HIDEOUT_STRUCT_HANDLER_H
#define COMMON_HIDEOUT_STRUCT_HANDLER_H

#include "commonStructHandler.h"
#include "entityManagerHandler.h"

typedef enum {
  MOVE_SELECTOR_UP,
  MOVE_SELECTOR_DOWN,
  MOVE_SELECTOR_RIGHT,
  MOVE_SELECTOR_LEFT,
  PRESS_X_BUTTON,
  PRESS_Y_BUTTON,
  PRESS_Z_BUTTON,
  PRESS_A_BUTTON,
  PRESS_B_BUTTON,
  PRESS_C_BUTTON
} CursorButtons;

typedef enum {
  HINT_MENU_OPTION_FOCUS,
  STATISTICS_TOP_MENU_FOCUS,
  STATISTICS_STATS_FOCUS,
  STATISTICS_OFFENSIVE_FOCUS,
  STATISTICS_DEFENSIVE_FOCUS,
  STATISTICS_UTILITY_FOCUS,
  STATISTICS_FOCUS,
  INVENTORY_FOCUS,
  MAP_FOCUS,
  MENU_FOCUS
} InteractFocusTypes;

typedef enum {
  STATISTICS_OPTION,
  INVENTORY_OPTION,
  MAP_OPTION,
  MENU_OPTION
} HintMenuOptionTypes;

typedef struct {
  u16 indexLevel;
  u16 infoText[145];
  u16 enemiesCount;
  bool available;
} BildingLevelData;

typedef struct {
  char name[10];
  u16 infoText[145];
  u16 indexImage;
  bool available;
} BuildingData;

typedef struct {
  char name[10];
  u16 buildingCount;
  BuildingData buildings[9];
  u16 infoText[145];
  u16 indexImage;
  bool available;
} CityData;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  u16 titleTiles[11];
  Vec2 titlePosition;
  u16 selectorIndex;
  Vec2 selectorPosition;
  Vec2 aButtonPosition;
  VerticalScrollTransform verticalScroll;
  Vec2 cursorRightPosition;
} CitiesBorderData;

typedef struct {
  CityData cities[9];
  u16 textTitle[5];
  Vec2 textTitlePosition;
} MapData;

typedef struct {
  u16 textTitle[8];
  Vec2 textTitlePosition;
} InventoryData;

typedef struct {
  u16 textTitle[4];
  Vec2 textTitlePosition;
} MenuData;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  Vec2 position;
} PlayerStatisticAvatarData;

typedef struct {
  Vec2 hintButtonPosition;
  Vec2 selectorPosition;
  u16 hintButtonTile;
  u16 selectorTile;
  u16 selectorIndex;
} StatisticTopSelector;

typedef struct {
  Vec2 statPositiona;
  u16 statTextTitles[5];
  Vec2 offensivePosition;
  u16 offensiveTextTitles[5];
  Vec2 defensivePosition;
  u16 defensiveTextTitles[6];
  Vec2 utilityPosition;
  u16 utilityTextTitles[9];
} StatisticTopOptions;

typedef struct {
  StatisticTopSelector selectorData;
  StatisticTopOptions optionsData;
  Vec2 leftHintPosition;
  Vec2 rightHintPosition;
  u16 currentFocus;
} StatisticTopMenuData;

typedef struct {
  Vec2 namePosition;
  Vec2 descriptionPosition;
} SD_leftSkill;

typedef struct {
  Vec2 namePosition;
  Vec2 descriptionPosition;
} SD_rightSkill;

typedef struct {
  Vec2 positionTiles;
  u16 textTiles[11];
  Vec2 positionValue;
  u16 value;
} SD_skillPoinstData;

typedef struct {
  Vec2 leftSelectorPosition;
  u16 leftSelectorTile;
  Vec2 rightSelectorPosition;
  u16 rightSelectorTile;
  Vec2 hintSelectorPosition;
  u16 hintSelectorTile;
  u16 index;
} SD_selectorData;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  SD_leftSkill leftSkill;
  SD_rightSkill rightSkill;
  u16 skills[2];
} SD_NextSkills;

typedef struct {
  Vec2 titleTilesPosition;
  u16 titleTiles[15];
  Vec2 borderPosition;
  SizeBox borderSize;
  Vec2 firstSkillPosition;
  u16 (*skills)[5]; // offensive defensive utility pointer of player SkillsData
                    // struct
  u16 *skillsSize;
  Vec2 focusBoxPosition;
  SizeBox focusBoxSize;
} SD_CurrentSkills;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  PlayerStatisticAvatarData avatar;
  u16 nameTitle[4];
  Vec2 nameTitilePosition;
  u16 nameValue[8];
  Vec2 nameValuePosition;
  u16 healthTitle[4];
  Vec2 healthTitlePosition;
  u16 *healthValue;
  Vec2 healthValuePosition;
  u16 attackTitle[4];
  Vec2 attackTitlePosition;
  u16 *attackValue;
  Vec2 attackValuePosition;
  u16 defenseTitle[4];
  Vec2 defenseTitlePosition;
  u16 *defenseValue;
  Vec2 defenseValuePosition;
  u16 critTitle[4];
  Vec2 critTitlePosition;
  u16 *critValue;
  Vec2 critValuePosition;
  u16 evasionTitle[4];
  Vec2 evasionTitlePosition;
  u16 *evasionValue;
  Vec2 evasionValuePosition;
} StatisticStatsStatisticsData;

typedef struct {
  SD_NextSkills nextSkills;
  SD_CurrentSkills currentSkills;
} StatisticOffensiveData;

typedef struct {
  SD_NextSkills nextSkills;
  SD_CurrentSkills currentSkills;
} StatisticDefensiveData;

typedef struct {
  SD_NextSkills nextSkills;
  SD_CurrentSkills currentSkills;
} StatisticUtilityData;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  Vec2 focusBoxPosition;
  SizeBox focusBoxSize;
  StatisticTopMenuData topMenuData;
  StatisticStatsStatisticsData statisticsData;
  StatisticOffensiveData offensiveData;
  StatisticDefensiveData defensiveData;
  StatisticUtilityData utilityData;
  SD_skillPoinstData skillPointsData;
  SD_selectorData selectorData;
} StatisticData;

typedef struct {
  MenuData menuData;
  InventoryData inventoryData;
  MapData mapData;
  Vec2 borderPosition;
  SizeBox borderSize;
  u16 levelTitle[6];
  Vec2 levelTitlePosition;
  u16 *levelValue;
  Vec2 levelValuePosition;
  u16 experienceTitle[6];
  Vec2 experienceTitlePosition;
  u16 experienceSpliterTile;
  Vec2 experienceSpliterTilePosition;
  u16 *currentExperience;
  Vec2 currentExperiencePosition;
  u16 *experienceNeededNext;
  Vec2 experienceNeededNextPosition;
  u16 creditTitle;
  Vec2 creditTitlePosition;
  u16 creditSpliterTile;
  Vec2 creditSpliterTilePosition;
  u16 *creditValue;
  Vec2 creditValuePosition;

} TopPanelData;

typedef struct {
  Vec2 hintButtonPosition;
  Vec2 selectorPosition;
  u16 hintButtonTile;
  u16 selectorTile;
  u16 selectorIndex;
} HintOptionMenuSelector;

typedef struct {
  Vec2 statsPosition;
  u16 statsTiles[5];
  Vec2 inventoryPosition;
  u16 inventoryTiles[8];
  Vec2 mapPosition;
  u16 mapTiles[4];
  Vec2 menuPosition;
  u16 menuTiles[4];
} HintOptionMenuOptionsData;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  HintOptionMenuSelector selectorData;
  HintOptionMenuOptionsData optionsData;
} HintOptionMenuData;

typedef struct {
  Vec2 borderPosition;
  SizeBox borderSize;
  Vec2 hintButtonPosition;
  Vec2 hintIconPosition;
  HintOptionMenuData menuData;
  StatisticData statisticData;
} HintOptionData;

typedef struct {
  HintOptionData hintOptionData;
  TopPanelData topPanelData;
  BorderTiles borderTilesData;
  CursorTiles cursorTilesData;
  u16 currentFocus;
  Vec2 optionSpacePosition; // Position of rendering data of selected option
                            // from top panel
  SizeBox optionSpaceSize;  // Size of option box for clearing this space
  Player *playerNode;
  bool reRenderTrigger;
} MetaData;

#endif
