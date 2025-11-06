#include <genesis.h>
#include "../../headers/scenes/scene.h"
#include "../../headers/scenes/mainMenuScene.h"

SceneManager currentSceneManager;

void sceneManagerInit() { currentSceneManager.sceneCount = 0; }

SceneManager getSceneManager() { return currentSceneManager; }

Scene createScene(char name[], u16 entityCount, SceneId idTag) {
  if (isScenePresent(name)) {
    return getSceneByName(name);
  }
  Scene sceneEntity;
  sceneEntity.entityCount = 0;
  sceneEntity.idTag = SCENE_MAIN_MENU;
  strncpy(sceneEntity.name, name, sizeof(sceneEntity.name) - 1);
  currentSceneManager.scenes[currentSceneManager.sceneCount++] = sceneEntity;
  return sceneEntity;
}

void setScene(SceneId sceneTagId) {
  if (sceneTagId == SCENE_MAIN_MENU) {
    Scene resultInit = mainMenuSceneInit();
    if (!isScenePresent(currentSceneManager.currentScene->name)) {
      currentSceneManager.scenes[currentSceneManager.sceneCount] = resultInit;
    }
  }
}

bool isScenePresent(char name[]) {
  for (u16 i = 0; i <= MAX_SCENES; i++) {
    if (currentSceneManager.scenes[i].name == name) {
      return true;
    }
  }
  return false;
}

Scene getSceneByName(char name[]) {
  Scene result = {0};
  for (u16 i = 0; i <= MAX_SCENES; i++) {
    if (currentSceneManager.scenes[i].name == name) {
      return currentSceneManager.scenes[i];
    }
  }
  return result;
}

void sceneUpdate() {
  SceneId idTagScene = currentSceneManager.currentScene->idTag;
  if (idTagScene == SCENE_MAIN_MENU) {
    mainMenuSceneUpdate();
  }
}
