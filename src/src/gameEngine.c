#include <genesis.h>
#include <../res/resources.h>
#include "../headers/gameEngine.h"
#include "../headers/miniGame.h"
#include "../headers/handlers/debugHandler.h"
#include "../headers/handlers/buttonAnimationHandler.h"
#include "../headers/handlers/inputHandler.h"
#include "../headers/scenes/scene.h"
#include "../headers/scenes/mainMenuScene.h"

void gameEngineInit() {
  // init SceneManager
  sceneManagerInit();
  // create Scene
  createScene("main menu", 0, SCENE_MAIN_MENU);
  // set Scene
  setScene(SCENE_MAIN_MENU);
  // init inputs
  JOY_init();
  JOY_setEventHandler(&myJoyHandler);
}

void gameEngineUpdate() {
  sceneUpdate();
}

void myJoyHandler(u16 joy, u16 changed, u16 state) {
  joyUpdate(joy, changed, state);
}

