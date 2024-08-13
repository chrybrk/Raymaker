#ifdef GAME_SCENE

#include <stdio.h>
#include <raylib.h>
#include "lib/SceneManager.h"
#include "lib/Animation.h"
#include "global.h"

Rectangle x, y;
AnimationTask id;

void InitGame()
{
	x = (Rectangle){ 100, 100, 50, 50 };
	y = (Rectangle){ 100, 300, 50, 50 };

	id = Animation(2.0f, RecMove, {
			rec->x += 100.0f * dt;
			/*
			Vector2 pos = Vector2Lerp(
					(Vector2){ rec->x, rec->y },
					(Vector2){ 200, 200 },
					duration * .05f
			);

			rec->x = pos.x;
			rec->y = pos.y;
			*/
	});
}

void TerminateGame()
{
}

void UpdateGame(float dt)
{
	ClearBackground((Color) { 23, 23, 23 });

	if (IsKeyPressed(KEY_ESCAPE))
		SetSceneByName(&sceneManager, "Menu");

	BeginDrawing();
	{
		DrawFPS(20, 20);

		DrawRectangleRec(x, RED);
		DrawRectangleRec(y, YELLOW);
	}
	EndDrawing();
}

#endif
