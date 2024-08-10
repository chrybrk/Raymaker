#include <raylib.h>
#include "lib/SceneManager.h"
#include "global.h"
#include "MenuScene.h"
#include "GameScene.h"

SceneManager sceneManager;
bool IsWindowAlive;

int main(void)
{
	sceneManager = InitSceneManager();

	AddSceneAuto("Menu", Menu);
	AddSceneAuto("Game", Game);

	SetSceneByName(&sceneManager, "Menu");

	InitWindow(800, 600, "game");
	SetTargetFPS(60);
	SetExitKey(0);
	IsWindowAlive = true;

	while (!WindowShouldClose() && IsWindowAlive)
	{
		float dt = GetFrameTime();

		Scene *scene = GetScene(&sceneManager);
		scene->SceneUpdate(dt);
	}

	CloseWindow();

	for (unsigned int i = 0; i < sceneManager.state; ++i)
		sceneManager.scenes[i].SceneTerminate();

	return 0;
}
