#include <genesis.h>
#include "../../headers/scenes/scene.h"

SceneManager currentSceneManager;

void initSceneManager() {
  currentSceneManager.sceneCount = 0;
  KLog_U1("Set sceneCount: ", currentSceneManager.sceneCount);
}

SceneManager getSceneManager() { return currentSceneManager; }

u16 createScene(char name[]) {
  Scene sceneEntity;
  strncpy(sceneEntity.name, name, sizeof(sceneEntity.name) - 1);
  currentSceneManager.scenes[currentSceneManager.sceneCount++] = sceneEntity;
  return currentSceneManager.sceneCount;
}

Scene getSceneByName(char name[]) {
  Scene result;
  for (u16 i = 0; i <= MAX_SCENES; i++) {
    if (currentSceneManager.scenes[i].name == name) {
      return currentSceneManager.scenes[i];
    }
  }
  return result;
}
