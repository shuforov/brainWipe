#ifndef SCENE_H
#define SCENE_H

#include <genesis.h>

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

void sceneManagerInit();
SceneManager getSceneManager();
Scene createScene(char name[], u16 entityCount, SceneId idTag);
bool isScenePresent(char name[]);
void setScene(SceneId sceneTagId);
Scene getSceneByName(char name[]);
void sceneUpdate();
void sceneInputHandle();

#endif
