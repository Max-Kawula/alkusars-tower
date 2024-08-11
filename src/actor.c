#include "actor.h"

Vector2 update_control(void)
{
	Vector2 result;

	result.x = IsKeyPressed(KEY_D) - IsKeyPressed(KEY_A);
	result.y = IsKeyPressed(KEY_S) - IsKeyPressed(KEY_W);

	if(Vector2Length(result) > 1.0f)
		result = Vector2Normalize(result);

	return result;
}

void control_actor(actor_t* a)
{
	float delta_time = GetFrameTime();
	Vector2 dir = Vector2Scale(update_control(), MAX_SPEED);
	Vector2 accel_dir = { 0.0f, 0.0f };
	float dot = -(Vector2DotProduct(a->vel, dir));
	dot = dot + 1.0f;
	
	if(!Vector2Equals(dir, Vector2Zero())) {
		
		if(dot > 1.0f)
			dot = 1.0f;

		accel_dir = Vector2Scale(update_control(), MAX_ACCEL*dot);
	
	} else if(Vector2Equals(a->vel, Vector2Zero())) { 
	
		return;

	} else {

		accel_dir = Vector2Negate(Vector2Scale(Vector2Normalize(a->vel), FRICTION));
	
	}	
		a->vel = Vector2Add(a->vel, Vector2Scale(accel_dir, delta_time));
		a->pos = Vector2Add(a->pos, Vector2Scale(a->vel, delta_time));

	return;
}
