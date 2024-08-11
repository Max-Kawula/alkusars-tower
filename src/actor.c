#include "actor.h"

Vector2 update_control(void)
{
	Vector2 result;

	result.x = (float)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)); //A is +x, D is -x
	result.y = (float)(IsKeyDown(KEY_S) - IsKeyDown(KEY_W)); //S is +z, W is -z

	if(Vector2Length(result) > 1.0f)
		result = Vector2Normalize(result);

	return result;
}

void control_actor(actor_t* a)
{
	/* gutted quake movement??? */
	float delta_time = GetFrameTime();
	Vector2 intended_dir = update_control();
	float accel_speed = 0;
	float deaccel_speed = 0;
	float target_speed = Vector2Length(intended_dir) * MAX_SPEED;//ranges from [0, MAX_SPEED]
	float current_speed = Vector2DotProduct(a->vel, intended_dir);//ranges from [-vel,vel]
	float move_speed = Vector2Length(a->vel);

	float add_speed = target_speed - current_speed;

	accel_speed = MAX_ACCEL * delta_time * target_speed;
	if(accel_speed > add_speed)
		accel_speed = add_speed;

	if(move_speed > 0.01f) { //are you moving?
	
		deaccel_speed = move_speed - delta_time * move_speed * FRICTION;
	
		if(deaccel_speed < 0)
			deaccel_speed = 0;
		deaccel_speed /= move_speed;

	} else if(!target_speed) { //check for no input
		a->vel = Vector2Zero();
		return;//safe to stop character
	}

	a->vel = Vector2Scale(a->vel, deaccel_speed); 
	a->vel = Vector2Add(Vector2Scale(intended_dir, accel_speed), a->vel);
	a->pos = Vector2Add(Vector2Scale(a->vel, delta_time), a->pos);

	return;
}
