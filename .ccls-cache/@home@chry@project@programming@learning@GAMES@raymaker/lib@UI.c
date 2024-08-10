#include "UI.h"

bool IsRectTouched(Rectangle rec)
{
	for (unsigned int i = 0; i < GetTouchPointCount(); ++i)
	{
		if (CheckCollisionPointRec(GetTouchPosition(i), rec))
			return true;
	}

	return false;
}

bool IsRectHovered(Rectangle rec)
{
	return CheckCollisionPointRec(GetMousePosition(), rec);
}

bool IsRectCollidedOrTouched(Rectangle rec)
{
	return IsRectTouched(rec) || IsRectHovered(rec);
}

bool IsRectClicked(Rectangle rec, int key)
{
	return IsRectHovered(rec) && IsMouseButtonDown(key);
}

bool IsRectClickedOrTouched(Rectangle rec, int key)
{
	return IsRectClicked(rec, key) || IsRectTouched(rec);
}

GUI_STATE CheckForMouseOrTouchEvent(Rectangle bounds, int key)
{
	bool IsHovered = IsRectHovered(bounds);
	bool IsClickedOrTouched = IsRectClickedOrTouched(bounds, MOUSE_BUTTON_LEFT);

	return IsClickedOrTouched ? CLICKED : IsHovered ? FOCUSED : NONE;
}

GUI_STATE DrawButton(Vector2 position, float fontSize, const char *text, Color bg, Color fg)
{
	float textWidth = (float)MeasureText(text, fontSize);

	Rectangle bounds;
	bounds.x = position.x - textWidth / 2 - 10;
	bounds.y = position.y / 2 - fontSize / 2 - 5;
	bounds.width = textWidth + 20;
	bounds.height = fontSize + 10;

	DrawRectangleRec(bounds, bg);
	DrawText(
			text,
			bounds.x + bounds.width / 2 - textWidth / 2,
			bounds.y + bounds.height / 2 - fontSize / 2,
			fontSize,
			fg
	);

	return CheckForMouseOrTouchEvent(bounds, MOUSE_BUTTON_LEFT);
}

GUI_STATE DrawRoundedButton(Vector2 position, float fontSize, float roundness, const char *text, Color bg, Color fg)
{
	float textWidth = (float)MeasureText(text, fontSize);

	Rectangle bounds;
	bounds.x = position.x - textWidth / 2 - 10;
	bounds.y = position.y / 2 - fontSize / 2 - 5;
	bounds.width = textWidth + 20;
	bounds.height = fontSize + 10;

	DrawRectangleRounded(bounds, roundness, 10, bg);
	DrawText(
			text,
			bounds.x + bounds.width / 2 - textWidth / 2,
			bounds.y + bounds.height / 2 - fontSize / 2,
			fontSize,
			fg
	);

	return CheckForMouseOrTouchEvent(bounds, MOUSE_BUTTON_LEFT);
}

GUI_STATE DrawFixedBoundButton(Rectangle bounds, float fontSize, const char *text, Color bg, Color fg)
{
	float textWidth = (float)MeasureText(text, fontSize);

	bounds.y = bounds.y / 2.0f;

	DrawRectangleRec(bounds, bg);
	DrawText(
			text,
			bounds.x + bounds.width / 2 - textWidth / 2,
			bounds.y + bounds.height / 2 - fontSize / 2,
			fontSize,
			fg
	);

	return CheckForMouseOrTouchEvent(bounds, MOUSE_BUTTON_LEFT);
}

GUI_STATE DrawFixedBoundRoundedButton(Rectangle bounds, float fontSize, float roundness, const char *text, Color bg, Color fg)
{
	float textWidth = (float)MeasureText(text, fontSize);

	bounds.y = bounds.y / 2.0f;

	DrawRectangleRounded((Rectangle) { bounds.x, bounds.y, bounds.width, bounds.height }, roundness, 10, bg);
	DrawText(
			text,
			bounds.x + bounds.width / 2 - textWidth / 2,
			bounds.y + bounds.height / 2 - fontSize / 2,
			fontSize,
			fg
	);

	return CheckForMouseOrTouchEvent(bounds, MOUSE_BUTTON_LEFT);
}
