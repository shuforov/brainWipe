#ifndef SCENE_H
#define SCENE_H

#include <genesis.h>

#define MAX_ENTITIES 256
#define MAX_SCENES 10
#define MAX_SCENE_NAME 23

typedef struct {
  u16 entityCount;
  u16 idTag;
  char name[MAX_SCENE_NAME];
} Scene;

typedef struct {
  Scene *currentScene;
  u16 sceneCount;
  Scene scenes[MAX_SCENES];
} SceneManager;

void initSceneManager();
SceneManager getSceneManager();
u16 createScene(char name[]);
Scene getSceneByName(char name[]);

#endif
