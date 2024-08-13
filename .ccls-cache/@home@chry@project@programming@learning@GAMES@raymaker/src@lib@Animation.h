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

#define Animation(REC, DURATION, NAME, BODY) \
	({\
	 void NAME(Rectangle *rec) BODY \
	 NAME(REC);\
	 })

#endif
