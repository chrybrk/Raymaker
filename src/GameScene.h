#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <stdio.h>
#include <raylib.h>
#include "lib/SceneManager.h"
#include "global.h"

SI_FUNC void InitGame()
{
	printf("init\n");
}

SI_FUNC void TerminateGame()
{
	printf("terminate\n");
}

SI_FUNC void UpdateGame(float dt)
{
	ClearBackground(RAYWHITE);

	if (IsKeyPressed(KEY_ESCAPE))
		SetSceneByName(&sceneManager, "Main");

	BeginDrawing();
	{
		DrawFPS(20, 20);
	}
	EndDrawing();
}

#endif
