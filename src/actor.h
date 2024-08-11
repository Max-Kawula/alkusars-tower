#ifndef ACTOR_H
#define ACTOR_H

#include "raylib.h"
#include "raymath.h"

#define MAX_SPEED (1.50f) //meters per second
#define MAX_ACCEL (2.50f) //meters per second squared
#define FRICTION (0.98f)

typedef struct actor_t {

	Vector2 pos;
	Vector2 vel;
	Texture2D sprite; //Texture2D is stored in GPU

} actor_t;

Vector2 update_control(void);

void control_actor(actor_t* a);

void draw_actor(actor_t* a);


#endif /* ACTOR_H */
