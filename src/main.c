#include <stdio.h>
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

	int menuSceneID = AddScene(&sceneManager, InitScene("Main", InitMenu, TerminateMenu, UpdateMenu));
	int gameSceneID = AddScene(&sceneManager, InitScene("Game", InitGame, TerminateGame, UpdateGame));

	SetSceneByName(&sceneManager, "Main");

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

	for (int i = 0; i < sceneManager.state; ++i)
		sceneManager.scenes[i].SceneTerminate();

	return 0;
}
