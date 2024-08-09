#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "lib/SceneManager.h"
#include "lib/UI.h"
#include "global.h"

static int states[4] = { NONE };

SI_FUNC void InitMenu()
{
	for (int i = 0; i < sizeof(states) / sizeof(states[0]); ++i)
		states[i] = NONE;

	printf("init menu\n");
}

SI_FUNC void TerminateMenu()
{
	printf("terminate\n");
}

SI_FUNC void UpdateMenu(float dt)
{
	ClearBackground(RAYWHITE);

	const char *buttonText[] = { "Start", "Option", "About", "Exit" };
	int fontSize = 40;

	if (states[0] == CLICKED)
		SetSceneByName(&sceneManager, "Game");
	
	if (states[3] == CLICKED)
		IsWindowAlive = false;

	BeginDrawing();
	{
		for (int i = 0; i < 4; ++i)
		{
			states[i] = DrawRoundedButton(
					(Vector2){ 400, (float)400 + (i * 150)},
					fontSize, .3f, 
					buttonText[i], 
					states[i] == FOCUSED ? RED : states[i] == CLICKED ? YELLOW : LIGHTGRAY, BLACK
			);
		}
	}
	EndDrawing();
}

#endif
