#ifndef __UI_H__
#define __UI_H__

#include <raylib.h>
#include "raymath.h"

typedef enum {
	NONE = 0,
	FOCUSED,
	CLICKED,
	TOUCHED
} GUI_STATE;

bool IsRectTouched(Rectangle rec);
bool IsRectHovered(Rectangle rec);
bool IsRectCollidedOrTouched(Rectangle rec);
bool IsRectClicked(Rectangle rec, int key);
bool IsRectClickedOrTouched(Rectangle rec, int key);

GUI_STATE DrawButton(Vector2 position, float fontSize, const char *text, Color bg, Color fg);
GUI_STATE DrawRoundedButton(Vector2 position, float fontSize, float roundness, const char *text, Color bg, Color fg);
GUI_STATE DrawFixedBoundButton(Rectangle bounds, float fontSize, const char *text, Color bg, Color fg);
GUI_STATE DrawFixedBoundRoundedButton(Rectangle bounds, float fontSize, float roundness, const char *text, Color bg, Color fg);

#endif
