#ifndef SCENE_H
#define SCENE_H

#include <genesis.h>
#include "../handlers/commonFunctionsHandler.h"

// border tiles
#define BORDER_TOP_RIGHT 0x10
#define BORDER_TOP_LEFT 0x18
#define BORDER_BOTTOM_RIGHT 0x11
#define BORDER_BOTTOM_LEFT 0x12
#define BORDER_RIGHT_SIDE 0x13
#define BORDER_TOP_SIDE 0x14
#define BORDER_LEFT_SIDE 0x15
#define BORDER_FILL 0x16
#define BORDER_BOTTOM_SIDE 0x17

// cursor selector buttons tiles
#define LEFT_CURSOR 0x75
#define RIGHT_CURSOR 0x76
#define DOWN_CURSOR 0x79
#define UP_CURSOR 0x7A
#define A_SELECTOR_BUTTON 0x78
#define B_SELECTOR_BUTTON 0x77
#define C_SELECTOR_BUTTON 0x7B
#define X_SELECTOR_BUTTON 0x7D
#define Y_SELECTOR_BUTTON 0x7E
#define Z_SELECTOR_BUTTON 0x7F
#define DROP_DOWN_ICON 0x7C

#define MAX_ENTITIES 256
#define MAX_SCENES 10
#define MAX_SCENE_NAME 23
#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
  u16 entityCount;
  u16 idTag;
  char name[MAX_SCENE_NAME];
} Scene;

typedef struct {
  Scene currentScene;
  u16 sceneCount;
  Scene scenes[MAX_SCENES];
} SceneManager;

typedef enum { SCENE_MAIN_MENU, SCENE_HIDEOUT } SceneId;

typedef struct {
  u16 hexDigits[3];
  u16 count;
} SceneTransformDigits;

extern const u16 NUMBERS_HEX[10];

void sceneManagerInit();
SceneManager getSceneManager();
Scene createScene(char name[], u16 entityCount, SceneId idTag);
bool isScenePresent(char name[]);
void setScene(SceneId sceneTagId);
Scene getSceneByName(char name[]);
void sceneUpdate();
void sceneInputHandle();
SceneTransformDigits sceneTransformDigitsToHex(CFH_SplitDigits splitDigits);

#endif
