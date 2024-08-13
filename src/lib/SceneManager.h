#ifndef __SCENE_MANAGER_h__
#define __SCENE_MANAGER_h__

#include "Constant.h"

#define AddSceneAuto(CALLER, NAME) AddScene(&sceneManager, InitScene(CALLER, Init##NAME, Terminate##NAME, Update##NAME))

typedef struct {
	char *sceneName;
	void (*SceneInit)();
	void (*SceneTerminate)();
	void (*SceneUpdate)(float dt);
} Scene;

Scene InitScene(const char *sceneName, void (*SIf)(void), void (*STf)(void), void (*SUf)(float dt));

typedef struct {
	Scene scenes[MAX_SCENE];
	unsigned int state;
	int currentState;
} SceneManager;

SceneManager InitSceneManager();
int AddScene(SceneManager *sceneManager, Scene scene);
void SetScene(SceneManager *sceneManager, unsigned int newState);
void SetSceneByName(SceneManager *sceneManager, const char *sceneName);
Scene *GetScene(SceneManager *sceneManager);

#endif
