#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <stdio.h>
#include <raylib.h>
#include "lib/SceneManager.h"
#include "lib/Animation.h"
#include "global.h"

inline Rectangle x;

SI_FUNC void InitGame()
{
	x = (Rectangle){ 100, 100, 50, 50 };

	printf("init\n");
}

SI_FUNC void TerminateGame()
{
	printf("terminate\n");
}

SI_FUNC void UpdateGame(float dt)
{
	ClearBackground((Color) { 23, 23, 23 });

	if (IsKeyPressed(KEY_ESCAPE))
		SetSceneByName(&sceneManager, "Menu");

	AnimateLinearMotion(&x, (Vector2) { 200, 200 }, 1.0f * dt);

	BeginDrawing();
	{
		DrawFPS(20, 20);

		DrawRectangleRec(x, RED);
	}
	EndDrawing();
}

#endif
