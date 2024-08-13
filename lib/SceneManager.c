#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SceneManager.h"

Scene InitScene(const char *sceneName, void (*SIf)(void), void (*STf)(void), void (*SUf)(float dt))
{
	Scene scene = {
		strdup(sceneName),
		SIf,
		STf,
		SUf
	};

	return scene;
}

SceneManager InitSceneManager()
{
	SceneManager sceneManager;
	sceneManager.state = 0;
	sceneManager.currentState = -1;

	return sceneManager;
}

int AddScene(SceneManager *sceneManager, Scene scene)
{
	if (sceneManager->state + 1 >= MAX_SCENE)
		return -1;

	sceneManager->scenes[sceneManager->state] = scene;
	sceneManager->state++;

	scene.SceneInit();
	
	return sceneManager->state - 1;
}

void SetScene(SceneManager *sceneManager, unsigned int newState)
{
	if (newState >= sceneManager->state)
		return;

	sceneManager->currentState = newState;
	sceneManager->scenes[sceneManager->currentState].SceneInit();
}

void SetSceneByName(SceneManager *sceneManager, const char *sceneName)
{
	for (unsigned int i = 0; i < sceneManager->state; ++i)
	{
		if (!strcmp(sceneName, sceneManager->scenes[i].sceneName))
		{
			sceneManager->currentState = i;
			sceneManager->scenes[sceneManager->currentState].SceneInit();
			return;
		}
	}

	printf("Scene :: Cannot find `%s` scene in the Scene Manager.\n", sceneName);
	exit(EXIT_FAILURE);
}

Scene *GetScene(SceneManager *sceneManager)
{
	if (sceneManager->currentState < 0)
		printf("Scene :: No scene is selected.\n"), exit(EXIT_FAILURE);

	return &sceneManager->scenes[sceneManager->currentState];
}
