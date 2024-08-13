#ifndef ACTOR_H
#define ACTOR_H

#include "raylib.h"
#include "raymath.h"

/* movement based constants */
#define MAX_SPEED (5.00f)
#define MAX_ACCEL (7.00f)
#define FRICTION (9.00f) 
#define MIN_SPEED (0.01f)

typedef enum Actor_Id {
	ACTOR_PLAYER,
	NUM_ACTOR_TYPES
} Actor_Id;

#define TURN_RIGHT	1 //these are probably stupid macros
#define TURN_LEFT	2
typedef enum Animation {
	FACE_FORWARD,		// +z
	FACE_FORWARD_RIGHT,	// +z,+x
	FACE_FORWARD_LEFT,	// +z,-x
	FACE_BACKWARD,		// -z
	FACE_BACKWARD_RIGHT,	// -z,+x
	FACE_BACKWARD_LEFT	// -z,-x
} Animation;

/* stores all info pertaining to sprite sheet, to be loaded from disk i assume */
typedef struct Sprite_Data {
	
	int pixel_offset[2]; //pixel dimensions, DrawBillBoard uses floats for some damned reason.
	Vector2 size; //world dimensions

	short num_sprites;//TODO figure out a system to keep track of frames per sprite

	Texture2D tex;

} Sprite_Data;

typedef struct Actor {

	Vector2 pos;
	Vector2 vel;

	Animation animation;
	int frame;
	Sprite_Data sprite; //???

} Actor;

Vector2 update_control(void);//TODO make a separate lib for input related functions

void draw_actor(Actor a, Camera c);

void control_actor(Actor* a);

enum Animation look_at(Vector2 origin, Vector2 target);

#endif /* ACTOR_H */
