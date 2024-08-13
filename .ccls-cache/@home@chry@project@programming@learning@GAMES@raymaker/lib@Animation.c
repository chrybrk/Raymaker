#include "Animation.h"

void Animate(AnimationTask *animation, Rectangle *rec, float dt)
{
	if (animation->elapsed_time < animation->duration)
		animation->function(rec, animation->duration, dt);

	animation->elapsed_time += dt;
}
