#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "lib/SceneManager.h"
#include "lib/UI.h"
#include "lib/Utils.h"
#include "global.h"

static const char *buttonText[] = { "Start", "Option", "About", "Exit" };
static int fontSize = 40;

static int states[4] = { NONE };
static int keyboardState = 0;
static bool checkState = true;

static int radius = 0;
static Vector2 positionForCircle;
static Color startColor;

SI_FUNC void MenuEventHandler()
{
	if (states[0] == CLICKED)
		SetSceneByName(&sceneManager, "Game");
	
	if (states[3] == CLICKED)
		IsWindowAlive = false;

	for (int i = 0; i < sizeof(states) / sizeof(states[0]); ++i)
	{
		if (IsKeyDown(KEY_DOWN) && checkState)
			keyboardState = (keyboardState + 1) % (sizeof(states) / sizeof(states[0])),
			checkState = false;

		if (IsKeyDown(KEY_UP) && checkState)
			keyboardState = keyboardState <= 0 ? (sizeof(states) / sizeof(states[0]) - 1) : keyboardState - 1,
			checkState = false;

		if (IsKeyUp(KEY_DOWN) && IsKeyUp(KEY_UP))
			checkState = true;

		states[i] = DrawFixedBoundRoundedButton(
				(Rectangle){ 320, (float)400 + (i * 150), 150, 50},
				fontSize, .3f, 
				buttonText[i], 
				states[i] == FOCUSED ? RED : states[i] == CLICKED ? YELLOW : startColor, BLACK
		);

		if (keyboardState >= 0)
			DrawFixedBoundRoundedButton(
					(Rectangle){ 320, (float)400 + (keyboardState * 150), 150, 50},
					fontSize, .3f, 
					buttonText[keyboardState], 
					RED, BLACK
			);

		if (IsKeyDown(KEY_ENTER) && keyboardState >= 0)
			states[keyboardState] = CLICKED;

		if (states[i] != NONE)
			keyboardState = -1;
	}
}

SI_FUNC void BackgroundAnimation()
{
	if (radius > 0)
	{
		DrawCircle(
				positionForCircle.x, 
				positionForCircle.y, 
				radius, 
				(Color){ 120, 120, 120, (unsigned char)radius }
		);

		radius--;
	}

	if (radius == 0)
	{
		positionForCircle.x = GetRandomValue(0, 800);
		positionForCircle.y = GetRandomValue(0, 600);
		radius = GetRandomValue(0, 255);
	}
}

SI_FUNC void InitMenu()
{
	for (int i = 0; i < sizeof(states) / sizeof(states[0]); ++i)
		states[i] = NONE;

	startColor = BLACK;

	printf("init menu\n");
}

SI_FUNC void TerminateMenu()
{
	printf("terminate\n");
}

SI_FUNC void UpdateMenu(float dt)
{
	ClearBackground((Color) { 23, 23, 23 });
	startColor = LerpColor(startColor, LIGHTGRAY, dt);

	BeginDrawing();
	{
		BackgroundAnimation();
		MenuEventHandler();
	}
	EndDrawing();
}

#endif
