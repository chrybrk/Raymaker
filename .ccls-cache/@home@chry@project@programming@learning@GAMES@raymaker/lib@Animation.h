#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <pthread.h>
#include "raylib.h"

/*
 * animate_t recAnimationID = Animation(&rec, 5.0f, {
 *	rec->x += speed * dt;
 * });
 *
 * Animate(recAnimationID);
*/

typedef unsigned long long int animate_t;

typedef struct {
	void (*function)(Rectangle *rec, float duration, float dt);
	float duration;
	float elapsed_time;
} AnimationTask;

void Animate(AnimationTask *animation, Rectangle *rec, float dt);

#define Animation(DURATION, NAME, BODY) \
	({\
	 void NAME(Rectangle *rec, float duration, float dt) BODY \
	 (AnimationTask) { \
			NAME, \
			DURATION, \
			0.0f\
	 };\
	 })

#endif
