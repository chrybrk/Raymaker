#include "Animation.h"
#include "raymath.h"

void AnimateLinearMotion(Rectangle *rec, Vector2 direction, float duration)
{
	Vector2 newPosition = Vector2Lerp((Vector2){ rec->x, rec->y }, direction, duration);
	rec->x = newPosition.x;
	rec->y = newPosition.y;
}
